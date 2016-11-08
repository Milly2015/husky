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

RedisInputFormat::~RedisInputFormat() {} 
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

/* void RedisInputFormat::ask_split() { */
/*     /1* BinStream question; *1/ */
/*     /1* question << need_auth_; *1/ */
/*     /1* if (need_auth_) *1/ */
/*     /1*     question << server_ << ns_ << username_ << password_ << husky::Context::get_param("hostname"); *1/ */
/*     /1* else *1/ */
/*     /1*     question << server_ << ns_ << husky::Context::get_param("hostname"); *1/ */

/*     /1* BinStream answer = husky::Context::get_coordinator().ask_master(question, husky::TYPE_MONGODB_REQ); *1/ */
/*     /1* answer >> split_; *1/ */
/*     return; */
/* } */

/* void RedisInputFormat::read() { */
/*     /1* if (!records_vector_.empty()) *1/ */
/*     /1*     records_vector_.clear(); *1/ */

/*     /1* mongo::DBClientConnection client; *1/ */
/*     /1* client.connect(split_.get_input_uri(), error_msg_); *1/ */

/*     /1* if (need_auth_) *1/ */
/*     /1*     client.auth(database_, username_, password_, error_msg_); *1/ */

/*     /1* query_.minKey(mongo::fromjson(split_.get_min())); *1/ */
/*     /1* query_.maxKey(mongo::fromjson(split_.get_max())); *1/ */

/*     /1* auto cursor = client.query(split_.get_ns(), query_); *1/ */
/*     /1* while (cursor->more()) { *1/ */
/*     /1*     mongo::BSONObj o = cursor->next(); *1/ */
/*     /1*     records_vector_.push_back(o.jsonString()); *1/ */
/*     /1* } *1/ */

/*     return; */
/* } */

/* void RedisInputFormat::send_end() { */
/*     /1* BinStream question; *1/ */
/*     /1* question << split_; *1/ */
/*     /1* husky::Context::get_coordinator().ask_master(question, husky::TYPE_MONGODB_END_REQ); *1/ */
/*     return; */
/* } */

/* bool RedisInputFormat::next(RecordT& ref) { */
/*     /1* while (records_vector_.empty()) { *1/ */
/*     /1*     ask_split(); *1/ */
/*     /1*     if (!split_.is_valid()) *1/ */
/*     /1*         return false; *1/ */
/*     /1*     read(); *1/ */
/*     /1*     if (records_vector_.empty()) *1/ */
/*     /1*         send_end(); *1/ */
/*     /1* } *1/ */

/*     /1* ref = records_vector_.back(); *1/ */
/*     /1* records_vector_.pop_back(); *1/ */
/*     /1* if (records_vector_.empty()) *1/ */
/*     /1*     send_end(); *1/ */
/*     return true; */
/* } */

}  // namespace io
}  // namespace husky
