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

#include "io/input/redis_inputformat.hpp"

#include <string>
#include <vector>
#include <iostream>

#include "hiredis.h"

#include "base/serialization.hpp"
#include "core/constants.hpp"
#include "core/context.hpp"
#include "core/coordinator.hpp"

namespace husky {
namespace io {

RedisInputFormat::RedisInputFormat() {
    values_vector_.clear();
}

RedisInputFormat::~RedisInputFormat() {
    values_vector_.clear();
} 

bool RedisInputFormat::is_setup() const { return true; }

void RedisInputFormat::set_server(const std::string& server) {
    server_ = server;
}

void RedisInputFormat::ask_split() {
    // for redis
    BinStream question;
    question << husky::Context::get_param("hostname");

    BinStream answer = husky::Context::get_coordinator().ask_master(question, husky::TYPE_REDIS_REQ);
    answer >> split_;
    
    return;
}

void RedisInputFormat::read() {
    // for redis
    std::string readhostip = split_.get_hostip();
    int readhostport = std::stoi(split_.get_hostport())
    struct timeval timeout = {1, 500000};
    redisContext* rContext = redisConnectWithTimeout(readhostip.c_str(), readhostport, timeout);

    if(rContext == NULL || rContext->err) {
        if(rContext) {
            std::cerr<<"Connection error: "<<_rContext->errstr<<std::endl;
            redisFree(_rContext);
        } else {
            std::cerr<<"Connection error : can't allocate redis context"<<std::endl;
        }
        rContext = NULL;
    }

    redisReply *reply; 
    // read value for each key
    for(std::vector<std::string>::iterator it = split_.keyset.begin(); it != split_.keyset.end(); ++it) { 
        reply = redisCommand(rContext,"GET %s", *it); 
        values_vector_.push_back(reply->str); 
    }
   
    freeReplyObject(reply);
    redisFree(rContext);
    return;
}

/* void RedisInputFormat::send_end() { */
/*     // for redis */
/*     BinStream question; */
/*     question << split_; */
/*     husky::Context::get_coordinator().ask_master(question, husky::TYPE_REDIS_END_REQ); */
/*     return; */
/* } */

/* bool RedisInputFormat::next(RecordT& ref) { */
/*     // for redis */
    
/*     return true; */
/* } */

}  // namespace io
}  // namespace husky
