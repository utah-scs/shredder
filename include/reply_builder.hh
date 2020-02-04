/*
* Pedis is free software: you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* You may obtain a copy of the License at
*
*     http://www.gnu.org/licenses
*
* Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
* KIND, either express or implied.  See the License for the
* specific language governing permissions and limitations
* under the License.
*
*  Copyright (c) 2016-2026, Peng Jian, pstack@163.com. All rights reserved.
*
*/
#pragma once
#include "core/app-template.hh"
#include "core/future-util.hh"
#include "core/timer-set.hh"
#include "core/shared_ptr.hh"
#include "core/stream.hh"
#include "core/memory.hh"
#include "core/units.hh"
#include "core/distributed.hh"
#include "core/vector-data-sink.hh"
#include "core/bitops.hh"
#include "core/slab.hh"
#include "core/align.hh"
#include "net/api.hh"
#include "net/packet-data-source.hh"

namespace redis {
using scattered_message_ptr = foreign_ptr<lw_shared_ptr<scattered_message<char>>>;

class reply_builder final {
public:
static future<scattered_message_ptr> build(size_t size)
{
    auto m = make_lw_shared<scattered_message<char>>();
    m->append_static(msg_num_tag);
    m->append(to_sstring(size));
    m->append_static(msg_crlf);
    return make_ready_future<scattered_message_ptr>(foreign_ptr<lw_shared_ptr<scattered_message<char>>>(m));
}

static future<scattered_message_ptr> build(double number)
{
    auto m = make_lw_shared<scattered_message<char>>();
    auto&& n = to_sstring(number);
    m->append_static(msg_batch_tag);
    m->append(to_sstring(n.size()));
    m->append_static(msg_crlf);
    m->append(std::move(n));
    m->append_static(msg_crlf);
    return make_ready_future<scattered_message_ptr>(foreign_ptr<lw_shared_ptr<scattered_message<char>>>(m));
}

static future<scattered_message_ptr> build(const sstring& message)
{
   auto m = make_lw_shared<scattered_message<char>>();
   m->append(message);
   return make_ready_future<scattered_message_ptr>(foreign_ptr<lw_shared_ptr<scattered_message<char>>>(m));
}

static future<scattered_message_ptr> build(const sstring& message, size_t size)
{
   auto m = make_lw_shared<scattered_message<char>>();
   m->append_static(msg_batch_tag);
   m->append(to_sstring(size));
   m->append_static(msg_crlf);
   m->append(message);
   m->append_static(msg_crlf);
   return make_ready_future<scattered_message_ptr>(foreign_ptr<lw_shared_ptr<scattered_message<char>>>(m));
}

static future<> build_local(output_stream<char>& out, size_t size)
{
    auto m = make_lw_shared<scattered_message<char>>();
    m->append_static(msg_num_tag);
    m->append(to_sstring(size));
    m->append_static(msg_crlf);
    return out.write(std::move(*m));
}

static scattered_message<char> build_direct(const sstring& message, size_t size)
{
   auto m = scattered_message<char>();
   m.append_static(msg_batch_tag);
   m.append(to_sstring(size));
   m.append_static(msg_crlf);
   m.append(message);
   m.append_static(msg_crlf);
   return m;
}

inline static future<> build_local(output_stream<char>& out, const sstring& message)
{
   return out.write(message);
}

}; // end of class
}
