#pragma once
#include "include/seastarkv.hh"
#include "include/reply_builder.hh"
#include <unordered_map>
#include <iterator>

using namespace std;
using namespace redis;
using namespace seastar;
using namespace v8;

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

public:
    int current_tid;
    Isolate* isolate;

    req_service(char** a)
        : argv(a)
    {
        create_params.array_buffer_allocator =
            v8::ArrayBuffer::Allocator::NewDefaultAllocator();
        isolate = Isolate::New(create_params);
        Isolate::Scope isolate_scope(isolate);
        {
            HandleScope handle_scope(isolate);
           
            // Setup the JS contexts for every tenant..
            for (int i = 0; i < NUM_CONTEXTS; i++) {
                v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);
		// Set C++ bindings
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
