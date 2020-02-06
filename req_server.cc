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
    v->data = (void *)malloc(strlen(val.c_str()));
    strcpy((char *)(v->data), val.c_str());
    v->length = strlen(val.c_str());
    uint32_t k = atoi(key.c_str());
    v->key = k;

//    redis_key rk { std::ref(key) };
//    auto cpu = get_cpu(rk);
//    return get_database().invoke_on_all(&database::set_all, rk, val).then([&out] () {
//    return get_database().invoke_on(cpu, &database::set, std::move(rk), std::ref(val)).then([&out] (auto&& m) {
    return get_local_database()->set_direct(k, std::ref(v), tid).then([&out] (auto&& m) {
//    return get_local_database()->set_direct(std::move(rk), std::ref(val), tid).then([&out] (auto&& m) {
//        return out.write(msg_ok);
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
    count++;
/*    auto now = rdtsc();
    if (count == 10000) {
        count = 0;
        cout << (float)req_t / (float)(now - start_t) << "\n";
//        cout << "100" << "\n";
        cout.flush();
        start_t = rdtsc();
        req_t = 0;
    }
*/
    if (args._command_args_count < 1) {
        cout << "syntax err\n";
        return out.write(msg_syntax_err);
    }
    sstring& key = args._command_args[0];
//    redis_key rk { std::ref(key) };
//    auto cpu = get_cpu(rk);
//    int tid = atoi(args._command_args[1].c_str());
    auto tid = current_tid;

//    cout << key << " before \n";
    auto db = get_local_database();
//    cout << key << "\n";
    db_val* val = db->ht_get(&db->ht[tid], atoi(key.c_str()));
    if (!val) {
        //cout << "not found" << key << "\n";
 //       val = (db_val*)malloc(sizeof(db_val));
//        val->length = 0;
        //sstring v = to_sstring(-1);
        //auto result = reply_builder::build_direct(v, v.size());
        //return out.write(std::move(result));
        //return make_ready_future<>();
        return out.write("0000", 4);
    }

//    auto data = (uint32_t*)(val->data);
    auto str = (char*)(val->data);
//    auto str_end = str + val->length - 1;
//    *str_end = '\0';
//    sstring v;
//    v = v + basic_string<char>(str, val->length);

/*    for (unsigned i = 0; i < val->length/4; i++) {
        v = v + to_sstring(*data);
        data++;
    }
*/
//    auto result = reply_builder::build_direct(v, v.size());
    /*auto current = this->rdtsc();
    req_t += (current - now);*/

    out.write(str, val->length);
    //return out.write(std::move(result));
//    return get_local_database()->get(std::move(rk), tid).then([&out] (auto&& m) {
/*    return get_local_database()->get(std::move(rk), tid).then([this, &out, &now] (auto&& m) {
        auto current = this->rdtsc();
        req_t += (current - now);
//    return get_database().invoke_on(cpu, &database::get, std::move(rk)).then([&out] (auto&& m) {
        return out.write(std::move(*m));
    });*/
    return make_ready_future<>();
}

future<bool> req_service::remove_impl(sstring& key) {
    redis_key rk { std::ref(key) };
    auto cpu = get_cpu(rk);
    return get_database().invoke_on(cpu, &database::del, std::move(rk));
}

future<int> req_service::get_tid(void) {
    return make_ready_future<int>(current_tid);
}

int req_service::get_tid_direct(void) {
    return current_tid;
}

// TO DO: obsolete code from Pedis
future<> req_service::del(args_collection& args, output_stream<char>& out) {
    if (args._command_args_count <= 0 || args._command_args.empty()) {
        return out.write(msg_syntax_err);
    }
    if (args._command_args.size() == 1) {
        sstring& key = args._command_args[0];
        return remove_impl(key).then([&out] (auto r) {
            return out.write( r ? msg_one : msg_zero);
        });
    }
    else {
        struct mdel_state {
            std::vector<sstring>& keys;
            size_t success_count;
        };
        for (size_t i = 0; i < args._command_args_count; ++i) {
            args._tmp_keys.emplace_back(args._command_args[i]);
        }
        return do_with(mdel_state{args._tmp_keys, 0}, [this, &out] (auto& state) {
            return parallel_for_each(std::begin(state.keys), std::end(state.keys), [this, &state] (auto& key) {
                return this->remove_impl(key).then([&state] (auto r) {
                    if (r) state.success_count++;
                });
            }).then([&state, &out] {
                return reply_builder::build_local(out, state.success_count);
            });
        });
    }
}

// Put a request into the queue and signal the JS thread
future<> req_service::js_req(args_collection& args, output_stream<char>& out, int tid) {
    auto start = rdtsc();
/*    count++;

    auto now = rdtsc();
    if (count == 10000) {
        count = 0;
        //if (engine().cpu_id() == 0)
            cout << (float)req_t / (float)(now - start_t) << "\n";
        cout.flush();
        start_t = rdtsc();
        req_t = 0;

    }
*/
    v8::Locker locker{isolate};              
    Isolate::Scope isolate_scope(isolate);
    HandleScope handle_scope(isolate);

    //int tid = req->tenant_id;
    current_tid = tid;
//    sstring& tid = req->args._command_args[req->args._command_args_count - 1];
//    current_tid = atoi(tid.c_str());
    
    Local<Context> context = Local<Context>::New(isolate, contexts[current_tid]);
    Context::Scope context_scope(context);
    current_context = &context;

//           cout.flush();


    auto req = make_lw_shared<rqst>(args);
    if (req->args._command_args_count < 1) {
        sstring tmp = to_sstring(msg_syntax_err);
        auto result = reply_builder::build_direct(tmp, tmp.size());
        return out.write(std::move(result));
        //return make_ready_future<sstring>(tmp);
    }      
//    get_count++;
    sstring& name = req->args._command_args[0];
    sstring& key = req->args._command_args[1];
//    sstring null = to_sstring("null/n");

/*    if (name == to_sstring("optstatus")) {
        using namespace v8::internal;
        v8::Local<v8::String> opt_source =
            v8::String::NewFromUtf8(isolate, "%OptimizeFunctionOnNextCall(q2)",
                                    v8::NewStringType::kNormal)
                .ToLocalChecked();

        v8::Local<v8::Script> opt_script =
            v8::Script::Compile(context, opt_source).ToLocalChecked();
        opt_script->Run(context);

        v8::Local<v8::String> source =
            v8::String::NewFromUtf8(isolate, "%GetOptimizationStatus(q2)",
                                    v8::NewStringType::kNormal)
                .ToLocalChecked();
    
        // Compile the source code.
        v8::Local<v8::Script> script =
            v8::Script::Compile(context, source).ToLocalChecked();
        auto res = script->Run(context).ToLocalChecked()->Int32Value(context).FromJust();
        if (res & static_cast<int>(OptimizationStatus::kNeverOptimize))
            printf("never optimized\n");
    
        if (res & static_cast<int>(OptimizationStatus::kAlwaysOptimize))
            printf("kAlwaysOptimize\n");
        if (res & static_cast<int>(OptimizationStatus::kOptimized))
            printf("kOptimized\n");
        if (res & static_cast<int>(OptimizationStatus::kTurboFanned))
            printf("kTurboFanned\n");
        auto tmp = to_sstring("ok\n");
        auto result = reply_builder::build_direct(tmp, tmp.size());
        return out.write(std::move(result));
        //return make_ready_future<sstring>(to_sstring("ok\n"));
    }
 */
    for (unsigned int i = 0; i < req->args._command_args_count -1; i++) {
        rargs.args[i] = req->args._command_args[i+1];
    }

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
//    const char* cstr = "ok\n";
    sstring tmp;

    const int argc = req->args._command_args_count -1;
    Local<Value> argv[argc];
    for (int i = 0; i < argc; i++) {
        argv[i] = Number::New(isolate, atoi(req->args._command_args[i+1].c_str()));
    }

    //Local<Value> argv[argc] = {Number::New(isolate, atoi(key.c_str()))};
    if (!process_fun->Call(context, context->Global(), argc, argv).ToLocal(&result)) {
         auto cstr = "error\n";
         out.write(cstr, strlen(cstr));
//         tmp = to_sstring(cstr);
    } else {
//        auto end = rdtsc();
 //       if (engine().cpu_id() == 0)
//           cout << tid << " " <<(end - start) << "\n";

         if (result->IsArrayBuffer()) {
             auto res = Local<ArrayBuffer>::Cast(result);
             auto cont = res->GetContents();
             //auto cont = res->Externalize();
             auto cstr = (char*)cont.Data();
             //v8::String::Utf8Value str(isolate, result);
             //tmp = to_sstring(ToCString(str));
             //cstr = ToCString(str);

             /*auto current = this->rdtsc();
             req_t += (current - now);*/
             auto end = rdtsc();
             if (engine().cpu_id() == 0) 
                 cout <<(end - start) << "\n";

             out.write(cstr, cont.ByteLength());
         } else {
             v8::String::Utf8Value str(isolate, result);
             tmp = to_sstring(ToCString(str));
             auto cstr = ToCString(str);
//printf("%s \n", cstr);
             /*auto current = this->rdtsc();
             req_t += (current - now);*/
	     auto res = reply_builder::build_direct(tmp, tmp.size());

             out.write(std::move(res));
             //out.write(cstr, strlen(cstr));
         }
         //out.write("^", 1);
         //tmp = rargs.result;
    }

 //   if (strlen(cstr) == 0)
//         cstr = "zero\n";
 
//    auto res = reply_builder::build_direct(tmp, tmp.size());

//    return out.write(std::move(res));
//    return out.write(cstr, strlen(cstr));

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

/*    local_req_server().get_tid().then([&key, &args, &ret_p] (auto&& t) {
        return get_local_database()->get_direct(std::move(key), std::move(t)).then([&args, &ret_p] (auto&& m) {
          *ret_p = *m;
        });
    }).get();
    Local<v8::ArrayBuffer> ab = v8::ArrayBuffer::New(args.GetIsolate(), ret_p->data, ret_p->length);
*/
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

/*    local_req_server().get_tid().then([&key, &args, &val](auto&& t) {
        return get_local_database()->set_direct(std::move(key), val, std::move(t)).then([&args] (auto&& m) {
            args.GetReturnValue().Set(
                v8::String::NewFromUtf8(args.GetIsolate(), "ok\n",
                                        v8::NewStringType::kNormal).ToLocalChecked());
        });
    }).get();*/
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
/*
    local_req_server().get_tid().then([&args](auto&& t) {
        return get_local_database()->get_table(std::move(t)).then([&args] (auto&& m) {
            void* p = (void*)*m;
            Local<v8::ArrayBuffer> ab = v8::ArrayBuffer::New(args.GetIsolate(), p, 1024*1024);
            args.GetReturnValue().Set(ab);
        });
    }).get();*/
}

// TO DO: obsolete code for btree version
void iterator_next(const v8::FunctionCallbackInfo<v8::Value>& args) {
    Isolate * isolate = args.GetIsolate();
    HandleScope handle_scope(isolate);
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
