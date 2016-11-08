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

/* #include "mongo/bson/bson.h" */
/* #include "mongo/client/dbclient.h" */
#include "hiredis.h"

#include "base/serialization.hpp"
#include "core/constants.hpp"
#include "core/context.hpp"
#include "core/coordinator.hpp"

namespace husky {
namespace io {

/* enum RedisInputFormatSetUp { */
/*     /1* NotSetUp = 0, *1/ */
/*     /1* NSSetUp = 1 << 1, *1/ */
/*     /1* ServerSetUp = 1 << 2, *1/ */
/*     /1* // TODO(legend): how to check if needs auth. *1/ */
/*     /1* AuthSetUp = 1 << 2, *1/ */
/*     /1* QuerySetUp = 1 << 2, *1/ */
/*     /1* AllSetUp = NSSetUp | ServerSetUp | AuthSetUp | QuerySetUp, *1/ */
/* }; */

RedisInputFormat::RedisInputFormat() {
    /* mongo::client::initialize(); */
    /* records_vector_.clear(); */
    /* is_setup_ = RedisInputFormatSetUp::NotSetUp; */
}

RedisInputFormat::~RedisInputFormat() {
    std::cout<<"Here is ~RedisInputFormat()"<<std::endl;
} 
/* { records_vector_.clear(); } */

/* void RedisInputFormat::set_ns(const std::string& database, const std::string& collection) { */
/*     /1* database_ = database; *1/ */
/*     /1* collection_ = collection; *1/ */
/*     /1* ns_ = database_ + "." + collection_; *1/ */
/*     /1* is_setup_ |= RedisInputFormatSetUp::NSSetUp; *1/ */
/* } */

/* void RedisInputFormat::set_server(const std::string& server) { */
/*     /1* server_ = server; *1/ */
/*     /1* is_setup_ |= RedisInputFormatSetUp::ServerSetUp; *1/ */
/* } */

/* void RedisInputFormat::set_auth(const std::string& username, const std::string& password) { */
/*     /1* username_ = username; *1/ */
/*     /1* password_ = password; *1/ */
/*     /1* need_auth_ = true; *1/ */
/*     /1* is_setup_ |= RedisInputFormatSetUp::AuthSetUp; *1/ */
/* } */

/* void RedisInputFormat::set_query(const mongo::Query& query) { */
/*     /1* query_ = query; *1/ */
/*     /1* is_setup_ |= RedisInputFormatSetUp::QuerySetUp; *1/ */
/* } */

/* bool RedisInputFormat::is_setup() const { return !(is_setup_ ^ RedisInputFormatSetUp::AllSetUp); } */
bool RedisInputFormat::is_setup() const { return is_setup_; }

void RedisInputFormat::test() {
    std::cout<<"test(): set = "<<is_setup_<<std::endl;
}

void RedisInputFormat::ask_split() {
    /* BinStream question; */
    /* question << need_auth_; */
    /* if (need_auth_) */
    /*     question << server_ << ns_ << username_ << password_ << husky::Context::get_param("hostname"); */
    /* else */
    /*     question << server_ << ns_ << husky::Context::get_param("hostname"); */

    /* BinStream answer = husky::Context::get_coordinator().ask_master(question, husky::TYPE_MONGODB_REQ); */
    /* answer >> split_; */
    
    /* // for redis */
    /* BinStream question; */
    /* question << server_ << ns_ << husky::Context::get_param("hostname"); */

    /* BinStream answer = husky::Context::get_coordinator().ask_master(question, husky::TYPE_REDIS_REQ); */
    /* answer >> split_; */
    
    return;
}

void RedisInputFormat::read() {
    /* if (!records_vector_.empty()) */
    /*     records_vector_.clear(); */

    /* mongo::DBClientConnection client; */
    /* client.connect(split_.get_input_uri(), error_msg_); */

    /* if (need_auth_) */
    /*     client.auth(database_, username_, password_, error_msg_); */

    /* query_.minKey(mongo::fromjson(split_.get_min())); */
    /* query_.maxKey(mongo::fromjson(split_.get_max())); */

    /* auto cursor = client.query(split_.get_ns(), query_); */
    /* while (cursor->more()) { */
    /*     mongo::BSONObj o = cursor->next(); */
    /*     records_vector_.push_back(o.jsonString()); */
    /* } */
    
    /* // for redis */
    /* if (!records_vector_.empty()) */
    /*     records_vector_.clear(); */

    return;
}

void RedisInputFormat::send_end() {
/*     /1* BinStream question; *1/ */
/*     /1* question << split_; *1/ */
/*     /1* husky::Context::get_coordinator().ask_master(question, husky::TYPE_MONGODB_END_REQ); *1/ */
/*     return; */
    /* // for redis */
    /* BinStream question; */
    /* question << split_; */
    /* husky::Context::get_coordinator().ask_master(question, husky::TYPE_REDIS_END_REQ); */
    return;
}

bool RedisInputFormat::next(RecordT& ref) {
    /* while (records_vector_.empty()) { */
    /*     ask_split(); */
    /*     if (!split_.is_valid()) */
    /*         return false; */
    /*     read(); */
    /*     if (records_vector_.empty()) */
    /*         send_end(); */
    /* } */

    /* ref = records_vector_.back(); */
    /* records_vector_.pop_back(); */
    /* if (records_vector_.empty()) */
    /*     send_end(); */

    /* // for redis */
    /* while (records_vector_.empty()) { */
    /*     ask_split(); */
    /*     if (!split_.is_valid()) */
    /*         return false; */
    /*     read(); */
    /*     if (records_vector_.empty()) */
    /*         send_end(); */
    /* } */

    /* ref = records_vector_.back(); */
    /* records_vector_.pop_back(); */
    /* if (records_vector_.empty()) */
    /*     send_end(); */
    
    return true;
}

}  // namespace io
}  // namespace husky
