// Copyright 2016 Husky Team
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <string>
#include <vector>

#include "io/input/inputformat_base.hpp"
#include "io/input/redis_split.hpp"

#include <hiredis.h>

namespace husky {
namespace io {

class RedisInputFormat final : public InputFormatBase {
   public:
    typedef std::string ValueT;
    RedisInputFormat();
    virtual ~RedisInputFormat();

    virtual bool is_setup() const;
    void set_server(const std::string& server);

    void ask_split();
    void read();
    void test();
    /* virtual bool next(keyT& ref); */
    /* void send_end(); */

   protected:
    RedisSplit split_;
    std::string server_;
    std::vector<ValueT> values_vector_;
   
};

}  // namespace io
}  // namespace husky
