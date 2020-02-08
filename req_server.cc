#include "include/seastarkv.hh"
#include "include/req_server.hh"
#include "include/net_server.hh"
#include "include/db.hh"
#include "v8/src/runtime/runtime.h"
#include <iostream>
#include <cstdio>
#include <condition_variable>
#include <thread> 
#include <fstream>
#include <chrono>
#include <string>

using namespace std;
using namespace seastar;
using namespace v8;
using namespace std::chrono;

distributed<req_service> req_server;

static const char* ToCString(const v8::String::Utf8Value& value) {
    return *value ? *value : "<string conversion failed>";
}

future<> req_service::start() {
    return make_ready_future<>();
}
future<> req_service::stop() {
    return make_ready_future<>();
}

// C++ version of set()
future<> req_service::set(args_collection& args, output_stream<char>& out, int tid) {
    if (args._command_args_count < 2) {
        return out.write(msg_syntax_err);
    }

    sstring& key = args._command_args[0];
    sstring& val = args._command_args[1];

    db_val* v = (db_val*)malloc(sizeof(db_val));
    v->data = (void *)malloc(sizeof(size_t));
    *(uint32_t*)(v->data) = atoi(val.c_str());
    v->length = 1;
    uint32_t k = atoi(key.c_str());
    v->key = k;

    return get_local_database()->set_direct(k, std::ref(v), tid).then([&out] (auto&& m) {
        return out.write(std::move(*m));
    });
}

inline uint32_t get_hash(uint32_t key, uint32_t seed) {
    uint32_t hash = key;
    hash = hash ^ seed;
    hash = ~hash + (hash << 15);  // hash = (hash << 15) - hash - 1;
    hash = hash ^ (hash >> 12);
    hash = hash + (hash << 2);
    hash = hash ^ (hash >> 4);
    hash = hash * 2057;  // hash = (hash + (hash << 3)) + (hash << 11);
    hash = hash ^ (hash >> 16);
    return hash & 0x3fffffff;
}

// C++ version of get()
future<> req_service::get(args_collection& args, output_stream<char>& out) {
    if (args._command_args_count < 1) {
        cout << "syntax err\n";
        return out.write(msg_syntax_err);
    }
    sstring& key = args._command_args[0];
    auto k = atoi(key.c_str());
    auto tid = current_tid;

    auto db = get_local_database();
    db_val* val = db->ht_get(&db->ht[tid], k);

    if (!val) {
        cout << "not found" << key << "\n";
        sstring v = to_sstring(-1);
        auto result = reply_builder::build_direct(v, v.size());
        return out.write(std::move(result));
    }

    auto data = (uint32_t*)(val->data);
    sstring v = to_sstring(*data);

    auto result = reply_builder::build_direct(v, v.size());
    return out.write(std::move(result));
}

future<int> req_service::get_tid(void) {
    return make_ready_future<int>(current_tid);
}

int req_service::get_tid_direct(void) {
    return current_tid;
}

// Put a request into the queue and signal the JS thread
future<> req_service::js_req(args_collection& args, output_stream<char>& out, int tid) {
    v8::Locker locker{isolate};              
    Isolate::Scope isolate_scope(isolate);
    HandleScope handle_scope(isolate);

    current_tid = tid;
    
    Local<Context> context = Local<Context>::New(isolate, contexts[current_tid]);
    Context::Scope context_scope(context);
    current_context = &context;

    auto req = make_lw_shared<rqst>(args);
    if (req->args._command_args_count < 1) {
        sstring tmp = to_sstring(msg_syntax_err);
        auto result = reply_builder::build_direct(tmp, tmp.size());
        return out.write(std::move(result));
    }      
    sstring& name = req->args._command_args[0];
    sstring& key = req->args._command_args[1];

    Local<Function> process_fun;
    if (prev_fun_name[current_tid] != name) {
        Local<String> process_name =
            String::NewFromUtf8(isolate, name.c_str(), NewStringType::kNormal)
                .ToLocalChecked();
        Local<Value> process_val;
        if (!context->Global()->Get(context, process_name).ToLocal(&process_val) ||
            !process_val->IsFunction()) {
             printf("get function %s fail\n", name.c_str());
        }
        process_fun = Local<Function>::Cast(process_val);
        prev_fun_name[current_tid] = name;
        prev_fun[current_tid].Reset(isolate, process_fun);
    } else {
         process_fun = Local<Function>::New(isolate, prev_fun[current_tid]);
    }
 
    Local<Value> result;
    sstring tmp;

    const int argc = req->args._command_args_count -1;
    Local<Value> argv[argc];
    for (int i = 0; i < argc; i++) {
        argv[i] = Number::New(isolate, atoi(req->args._command_args[i+1].c_str()));
    }

    if (!process_fun->Call(context, context->Global(), argc, argv).ToLocal(&result)) {
         auto cstr = "error\n";
         out.write(cstr, strlen(cstr));
    } else {
         if (result->IsArrayBuffer()) {
             auto res = Local<ArrayBuffer>::Cast(result);
             auto cont = res->GetContents();
             auto cstr = (char*)cont.Data();
             auto end = rdtsc();
             out.write(cstr, cont.ByteLength());
         } else {
             v8::String::Utf8Value str(isolate, result);
             tmp = to_sstring(ToCString(str));
             auto cstr = ToCString(str);
	     auto res = reply_builder::build_direct(tmp, tmp.size());

             out.write(std::move(res));
         }
    }
    return make_ready_future<>();
}

enum AllocationSpace {
  NEW_SPACE,   // Semispaces collected with copying collector.
  OLD_SPACE,   // May contain pointers to new space.
  CODE_SPACE,  // No pointers to new space, marked executable.
  MAP_SPACE,   // Only and all map objects.
  LO_SPACE,    // Promoted large objects.

  FIRST_SPACE = NEW_SPACE,
  LAST_SPACE = LO_SPACE,
  FIRST_PAGED_SPACE = OLD_SPACE,
  LAST_PAGED_SPACE = MAP_SPACE
};

// The JS thread. Keep this thread although it's doing nothing, because 
// performance is better with this thread around, maybe because it keeps
// some V8 states from garbage collectioned or something.
future<> req_service::js() {
    async([this] 
    {
        v8::Locker locker{isolate};              
        Isolate::Scope isolate_scope(isolate);

        while (true) {
            HandleScope handle_scope(isolate);

            sem.wait(1).get();
            auto req = req_q.front();
            req_q.pop();

        }
    });
    return make_ready_future<>();
}

void db_get(const v8::FunctionCallbackInfo<v8::Value>& args) {
    db_val ret;
    db_val* ret_p = &ret;
    uint32_t key = args[0]->Uint32Value(args.GetIsolate()->GetCurrentContext()).ToChecked();

    auto db = get_local_database();
    auto tid = local_req_server().get_tid_direct();
    db_val* val = db->ht_get(&db->ht[tid], key);
    if (!val) {
        val = (db_val*)malloc(sizeof(db_val));
        val->length = 0;
    }
    
    Local<v8::ArrayBuffer> ab = v8::ArrayBuffer::New(args.GetIsolate(), val->data, val->length);

    args.GetReturnValue().Set(ab);
}
void db_set(const v8::FunctionCallbackInfo<v8::Value>& args) {
    auto content = args[1].As<v8::ArrayBuffer>()->Externalize();
    db_val* val = (db_val*)malloc(sizeof(db_val));
    val->data = content.Data();
    val->length = content.ByteLength();
    uint32_t key = args[0]->Uint32Value(args.GetIsolate()->GetCurrentContext()).ToChecked();
    val->key = key;

    auto tid = local_req_server().get_tid_direct();
    auto db = get_local_database();
    if (db->ht[tid].table == NULL)
        db->hashtable_init(&db->ht[tid], 1000*1000);
    db->ht_set(&db->ht[tid], val);

    args.GetReturnValue().Set(
        v8::String::NewFromUtf8(args.GetIsolate(), "ok\n",
                                v8::NewStringType::kNormal).ToLocalChecked());

}

void db_del(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::String::Utf8Value str(args.GetIsolate(), args[0]);
    const char* cstr = ToCString(str);
    sstring key = to_sstring(cstr);
    sstring& k = key;
    redis_key rk{std::ref(k)};
    auto cpu = rk.get_cpu();
    local_req_server().get_tid().then([&rk, &args, &cpu](auto&& t) {
        return get_database().invoke_on(cpu, &database::del_direct, std::move(rk), std::move(t)).then([&args] (auto&& m) {
            auto val = std::move(*m).c_str();
            args.GetReturnValue().Set(
                v8::String::NewFromUtf8(args.GetIsolate(), val,
                                        v8::NewStringType::kNormal).ToLocalChecked());
        });
    }).get();
}

void js_print(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Isolate * isolate = args.GetIsolate();
    HandleScope handle_scope(isolate);

    v8::String::Utf8Value str(args.GetIsolate(), args[0]);
    const char* cstr = ToCString(str);
    std::cout << cstr << '\n';
}

void get_hash_table(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Isolate * isolate = args.GetIsolate();
    HandleScope handle_scope(isolate);

    auto tid = local_req_server().get_tid_direct();
    auto table = get_local_database()->get_table_direct(tid); 
    Local<v8::ArrayBuffer> ab = v8::ArrayBuffer::New(args.GetIsolate(), table, 1024*1024);
    args.GetReturnValue().Set(ab);
}

//Load SNAP ego network into hashtable
void load_fb_graph(const v8::FunctionCallbackInfo<v8::Value>& args) {
    string line;
    ifstream fb_file("facebook_combined.txt");
    if (fb_file) {
        uint32_t prev_key = 0;
        vector<uint32_t> arr;
        while (getline(fb_file, line))
        {
            string delimiter = " ";
            auto pos = line.find(delimiter);
            string k = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());
            uint32_t key = atoi(k.c_str());
            uint32_t value = atoi(line.c_str());
            if (key == prev_key) {
                arr.push_back(value);
                continue;
            }

            db_val* val = (db_val*)malloc(sizeof(db_val));
            val->data = malloc(sizeof(uint32_t) * arr.size());
            val->length = arr.size() * 4;
            val->key = prev_key;

            auto cur = (uint32_t*)(val->data);
            for (auto it = arr.begin(); it != arr.end(); ++it) {
               auto v = *it;
               *cur = v;
               cur++;
            } 

            auto vk = val->key;

            auto tid = local_req_server().get_tid_direct();
            auto db = get_local_database();
            if (db->ht[tid].table == NULL)
                db->hashtable_init(&db->ht[tid], 1000*1000);
            db->ht_set(&db->ht[tid], val);

            prev_key = key;
            arr.clear();
            arr.push_back(value);
        }
        db_val* val = (db_val*)malloc(sizeof(db_val));
        val->data = malloc(sizeof(uint32_t) * arr.size());
        val->length = arr.size() * 4;
        val->key = prev_key;

        auto cur = (uint32_t*)(val->data);
        for (auto it = arr.begin(); it != arr.end(); ++it) {
           auto v = *it;
           *cur = v;
           cur++;
        } 

        auto vk = val->key;

        auto tid = local_req_server().get_tid_direct();
        auto db = get_local_database();
        if (db->ht[tid].table == NULL)
            db->hashtable_init(&db->ht[tid], 1000*1000);
        db->ht_set(&db->ht[tid], val);

        fb_file.close();
    } else
        cout << "Open file error.\n";
}
