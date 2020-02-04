#pragma once
#include "include/seastarkv.hh"
#include "include/reply_builder.hh"
#include <unordered_map>
#include <iterator>

using namespace std;
using namespace redis;
using namespace seastar;
using namespace v8;

struct req_args;
static const char* ToCString(const v8::String::Utf8Value& value) {
    return *value ? *value : "<string conversion failed>";
}

static void get_args(unsigned int index,
               const PropertyCallbackInfo<Value>& info);
static void set_args(unsigned int index, Local<Value> value,
               const PropertyCallbackInfo<Value>& info);

static void get_result(Local<String> property,
               const PropertyCallbackInfo<Value>& info);

static void set_result(Local<String> property, Local<Value> value,
               const PropertyCallbackInfo<void>& info);

class req_service;
extern distributed<req_service> req_server;
inline distributed<req_service>& get_req_server() {
    return req_server;
}
inline req_service& local_req_server() {
    return req_server.local();
}

inline unsigned get_cpu(const sstring& key) {
    return std::hash<sstring>()(key) % smp::count;
}
inline unsigned get_cpu(const redis_key& key) {
    return key.hash() % smp::count;
}

void db_get(const v8::FunctionCallbackInfo<v8::Value>& args);
void db_set(const v8::FunctionCallbackInfo<v8::Value>& args);
void db_del(const v8::FunctionCallbackInfo<v8::Value>& args);
void js_print(const v8::FunctionCallbackInfo<v8::Value>& args);
void init_iterator(const v8::FunctionCallbackInfo<v8::Value>& args);
void iterator_next(const v8::FunctionCallbackInfo<v8::Value>& args);
void get_hash_table(const v8::FunctionCallbackInfo<v8::Value>& args);
void load_fb_graph(const v8::FunctionCallbackInfo<v8::Value>& args);

// Args for JS function
struct req_args {
    sstring args[10];
    sstring result;
};

using message = scattered_message<char>;
class req_service {
private:
    // The tenant id tied to the currently running script.
    // The JavaScript context of the currently running script.
    Local<Context>* current_context;
    char** argv;
    Isolate::CreateParams create_params;
    // JavaScript contexts for each tenant.
    Global<Context> contexts[NUM_CONTEXTS];
    // Stores the function object of the last run JS function.
    Global<Function> prev_fun[NUM_CONTEXTS];
    // Stores the name of the last run JS function.
    sstring prev_fun_name[NUM_CONTEXTS];
    Global<ObjectTemplate> args_templ;

    // Semaphore to signal incoming requests to JS thread.
    semaphore sem{0};

    // The stucture to store an incoming request.
    struct rqst {
        args_collection& args;
        sstring key;
        sstring val;
        int tenant_id;
        bool put;
        lw_shared_ptr<promise<foreign_ptr<lw_shared_ptr<sstring>>>> p;
        rqst(args_collection& a)
            :args(a)
        {}
        ~rqst(){}
    };
   
    // The queue to put incoming requests in, the JS thread will take and
    //  run requests from the queue.
    std::queue<lw_shared_ptr<rqst>> req_q;

    MaybeLocal<String> read_file(Isolate* isolate, const string& name) {
        FILE* file = fopen(name.c_str(), "rb");
        if (file == NULL) return MaybeLocal<String>();
   
        fseek(file, 0, SEEK_END);
        size_t size = ftell(file);
        rewind(file);
   
        char* chars = new char[size + 1];
        chars[size] = '\0';
        for (size_t i = 0; i < size;) {
            i += fread(&chars[i], 1, size - i, file);
            if (ferror(file)) {
                fclose(file);
                return MaybeLocal<String>();
            }
        }
        fclose(file);
        MaybeLocal<String> result = String::NewFromUtf8(
            isolate, chars, NewStringType::kNormal, static_cast<int>(size));
        delete[] chars;
        return result;
    }

    uint64_t rdtsc() {
        uint32_t lo, hi;
        __asm volatile
        (
            "rdtsc" : "=a" (lo), "=d" (hi)
        );
        return (uint64_t)hi<<32|lo;
    }

public:
    int current_tid;
    Isolate* isolate;
    req_args rargs;
    uint64_t start_t;
    uint64_t req_t;
    uint64_t count;

    req_service(char** a)
        : argv(a)
    {
        create_params.array_buffer_allocator =
            v8::ArrayBuffer::Allocator::NewDefaultAllocator();
        isolate = Isolate::New(create_params);
        Isolate::Scope isolate_scope(isolate);
        {
            HandleScope handle_scope(isolate);
            Local<ObjectTemplate> args = ObjectTemplate::New(isolate);
           
            args->SetInternalFieldCount(1);
            // Set C++ binding for getting args.
            args->SetHandler(IndexedPropertyHandlerConfiguration(get_args, set_args));
            args->SetAccessor(String::NewFromUtf8(isolate, "result").ToLocalChecked(), get_result, set_result);
            args_templ.Reset(isolate, args);
 
            // Setup the JS contexts for every tenant..
            for (int i = 0; i < NUM_CONTEXTS; i++) {
                v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);
                global->Set(
                    v8::String::NewFromUtf8(isolate, "DBGet", v8::NewStringType::kNormal)
                        .ToLocalChecked(),
                    v8::FunctionTemplate::New(isolate, db_get)
                );
                global->Set(
                    v8::String::NewFromUtf8(isolate, "DBSet", v8::NewStringType::kNormal)
                        .ToLocalChecked(),
                    v8::FunctionTemplate::New(isolate, db_set)
                );
                global->Set(
                    v8::String::NewFromUtf8(isolate, "DBDel", v8::NewStringType::kNormal)
                        .ToLocalChecked(),
                    v8::FunctionTemplate::New(isolate, db_del)
                );
                global->Set(
                    v8::String::NewFromUtf8(isolate, "print", v8::NewStringType::kNormal)
                        .ToLocalChecked(),
                    v8::FunctionTemplate::New(isolate, js_print)
                );

                global->Set(
                    v8::String::NewFromUtf8(isolate, "Next", v8::NewStringType::kNormal)
                        .ToLocalChecked(),
                    v8::FunctionTemplate::New(isolate, iterator_next)
                );
                
                global->Set(
                    v8::String::NewFromUtf8(isolate, "GetHashTable", v8::NewStringType::kNormal)
                        .ToLocalChecked(),
                    v8::FunctionTemplate::New(isolate, get_hash_table)
                );

                 global->Set(
                    v8::String::NewFromUtf8(isolate, "LoadFBGraph", v8::NewStringType::kNormal)
                        .ToLocalChecked(),
                    v8::FunctionTemplate::New(isolate, load_fb_graph)
                );
                
                // JS script can get the current tenant id by this global variable.
                global->Set(
                    v8::String::NewFromUtf8(isolate, "TID", v8::NewStringType::kNormal)
                        .ToLocalChecked(),
                    v8::Number::New(isolate, i)
                );

                Local<Context> c = Context::New(isolate, NULL, global);
             
                Context::Scope contextScope(c);
                Local<ObjectTemplate> templ =
                    Local<ObjectTemplate>::New(isolate, args_templ);
             
                Local<Object> obj = templ->NewInstance(c).ToLocalChecked();

                // Bind rargs to global JS variable "args".
                obj->SetInternalField(0, External::New(isolate, &rargs));
                c->Global()
                    ->Set(c,
                          String::NewFromUtf8(isolate, "args", NewStringType::kNormal)
                              .ToLocalChecked(),
                          obj)
                    .FromJust();
             
                contexts[i].Reset(isolate, c);
            }

            for (int i = 0; i < NUM_CONTEXTS; i++) {
                Local<Context> c = Local<Context>::New(isolate, contexts[i]);
                Context::Scope contextScope(c);

                Local<String> source;
                // Read the JS script file.
                if (!read_file(isolate, "scripts.js").ToLocal(&source)) {
                    fprintf(stderr, "Error reading file\n");
                }

                Local<Script> s =
                  Script::Compile(c, source).ToLocalChecked();
  
                Local<Value> result;
                if (!s->Run(c).ToLocal(&result)) {
                  printf("run script error\n");
                }
                contexts[i].Reset(isolate, c);
            }
        }
    }
    future<> start();
    future<> stop();
    future<> js();
    future<bool> remove_impl(sstring& key);
    future<> set(args_collection& args, output_stream<char>& out, int tid);
    future<> get(args_collection& args, output_stream<char>& out);
    future<> del(args_collection& args, output_stream<char>& out);
    future<> js_req(args_collection& args, output_stream<char>& out, int tid);
    future<int> get_tid(void);
    int get_tid_direct(void);
};

void get_args(unsigned int index,
              const PropertyCallbackInfo<Value>& info) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    sstring& value = static_cast<req_args*>(ptr)->args[index];
    info.GetReturnValue().Set(
        String::NewFromUtf8(local_req_server().isolate,
                            value.c_str(),
                            NewStringType::kNormal,
                            (int)value.length()).ToLocalChecked()
    );
}

void set_args(unsigned int index, Local<Value> value,
               const PropertyCallbackInfo<Value>& info) {
}

void get_result(Local<String> property,
               const PropertyCallbackInfo<Value>& info) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    sstring& value = static_cast<req_args*>(ptr)->result;
 
    Local<v8::ArrayBuffer> ab = ArrayBuffer::New(local_req_server().isolate, 4);
    uint32_t* tmp = (uint32_t*)ab->GetContents().Data();
    *tmp = 42;
    info.GetReturnValue().Set(ab);
}

void set_result(Local<String> property, Local<Value> value,
               const PropertyCallbackInfo<void>& info) {
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();
    String::Utf8Value str(info.GetIsolate(), value);
    static_cast<req_args*>(ptr)->result = to_sstring(ToCString(str));
}
