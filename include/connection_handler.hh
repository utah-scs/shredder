#pragma once
#include "redis_protocol_parser.hh"
#include "seastarkv.hh"

using namespace seastar;
using namespace redis;

class connection_handler {
private:
    redis_protocol_parser _parser;
    args_collection _request_args;

public:
    connection_handler() {};
    void prepare_request();
    future<> handle(input_stream<char>& in, output_stream<char>& out, int& tid);
};

