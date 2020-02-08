#include "include/connection_handler.hh"
#include "include/req_server.hh"

using namespace seastar;
void connection_handler::prepare_request()
{
    _request_args._command_args_count = _parser._args_count - 1;
    _request_args._command_args = std::move(_parser._args_list);
    _request_args._tmp_keys.clear();
    _request_args._tmp_key_values.clear();
    _request_args._tmp_key_scores.clear();
    _request_args._tmp_key_value_pairs.clear();
}

inline unsigned getcpu(const sstring& key) {
    return std::hash<sstring>()(key) % smp::count;
}

future<> connection_handler::handle(input_stream<char>& in, output_stream<char>& out, int& tid) {
    _parser.init();

   // NOTE: The command is handled sequentially. The parser will control the lifetime
    // of every parameters for command.
    return in.consume(_parser).then([this, &in, &out, &tid] () -> future<> {
        switch (_parser._state) {
            case redis_protocol_parser::state::eof:
                printf("eof\n");
            case redis_protocol_parser::state::error:
                printf("error\n");
                return make_ready_future<>();

            case redis_protocol_parser::state::ok:
            {
                prepare_request();
                switch (_parser._command) {
                    case redis_protocol_parser::command::set:
                    {
                        return local_req_server().set(_request_args, std::ref(out), tid);
                    }
                    case redis_protocol_parser::command::get:
                    {
                        return local_req_server().get(std::move(std::ref(_request_args)), std::ref(out));
                    }
                    case redis_protocol_parser::command::js:
                         return local_req_server().js_req(std::move(std::ref(_request_args)), std::ref(out), tid);
                    case redis_protocol_parser::command::info:
                         return out.write("$0\r\n\r\n").then([&out] () {
                              return out.flush();
                         });
                    case redis_protocol_parser::command::quit:
                        return out.write(msg_ok);

                    default:
                        //tracer.incr_number_exceptions();
                        return out.write("+Not Implemented");
                };
            }
            default:
                //tracer.incr_number_exceptions();
                return out.write("+Error\r\n");
        };
        std::abort();
    });
}
