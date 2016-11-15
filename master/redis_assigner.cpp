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

#ifdef WITH_REDIS

#include "master/redis_assigner.hpp"

#include <cstring>
#include <iostream>
#include <sstream>

#include "hiredis.h"

#include "core/constants.hpp"
#include "core/zmq_helpers.hpp"
#include "master/master.hpp"

namespace husky {

static RedisAssigner redis_assigner;

RedisAssigner::RedisAssigner() {
    std::cout<<"RedisAssigner initialization"<<std::endl;

    // TODO: here should read from config file and initialize redis cluster
    // now hardcode
    _masterredishost="192.168.50.10";
    _masterredisport=6379;
    struct timeval timeout = {1, 500000};
    _rContext = initCtx(_masterredishost.c_str(), _masterredisport, timeout);

    if(_rContext == NULL || _rContext->err) {
        if(_rContext) {
            std::cerr<<"Connection error: "<<_rContext->errstr<<std::endl;
            redisFree(_rContext);
        } else {
            std::cerr<<"Connection error : can't allocate redis context"<<std::endl;
        }
        _rContext = NULL;
    }
    
    // TODO: here should read from config file and initialize the keyset
    // now hardcode 4 keys: "afile" "bfile" "cfile" "dfile"
    std::string tempkey;
    char *tempckey;
    tempkey = std::string("afile");
    tempckey = strdup(tempkey.c_str());
    redisReply * rReply;
    rReply = (redisReply *)redisCommand(_rContext, "exists %s", tempckey);
    std::cout<<rReply->str<<std::endl;
    if(rReply->str == NULL) {
        char* cmaddr = strdup(_masterredishost.c_str());
        _keysetmap[_masterredishost].insert(tempkey);
    } else {
        std::string res(rReply->str);
        if(res.find("MOVED")==0) {
            std::stringstream ss(res);
            std::string buf;
            while(ss>>buf) {
            }
            std::string netaddr = buf;
            std::string temphost=netaddr.substr(0, netaddr.find(":"));
            std::cout<<"ip = "<<temphost<<std::endl;
            _keysetmap[temphost].insert(tempkey);
        }
    } 
    dumpkeymap();

    Master::get_instance().register_main_handler(TYPE_REDIS_REQ,
            std::bind(&RedisAssigner::master_redis_req_handler, this));
    Master::get_instance().register_main_handler(TYPE_REDIS_END_REQ,
            std::bind(&RedisAssigner::master_redis_req_end_handler, this));
    Master::get_instance().register_setup_handler(std::bind(&RedisAssigner::master_setup_handler, this));
}

redisContext * RedisAssigner::initCtx(const char *ip, int port, const struct timeval tv) {
    return redisConnectWithTimeout(ip, port, tv);
}

RedisAssigner::~RedisAssigner() {
    _keysetmap.clear();
}

void RedisAssigner::master_setup_handler() {}

void RedisAssigner::master_redis_req_handler() {
    auto& master = Master::get_instance();
    auto master_socket = master.get_socket();
    std::string hostname;
    BinStream stream = zmq_recv_binstream(master_socket.get());
    stream >> hostname;
    RedisSplit ret = answer(hostname);
    stream.clear();
    stream << ret;

    zmq_sendmore_string(master_socket.get(), master.get_cur_client());
    zmq_sendmore_dummy(master_socket.get());
    zmq_send_binstream(master_socket.get(), stream);
    /* base::log_msg(host + " => " + ret.get_hostip()); */
}

RedisSplit RedisAssigner::answer(const std::string& hostname) {
    RedisSplit ret;
    ret.set_hostip(_masterredishost);
    ret.set_hostport(_masterredisport);
    ret.set_keyset(_keysetmap.pop_back());
    return ret;

} 

void RedisAssigner::dumpkeymap() {
    for(auto iterator = _keysetmap.begin(); iterator != _keysetmap.end(); iterator++){
        std::cout<<"host: "<<iterator->first<<"  ";
        std::set<std::string> tempset = iterator->second;
        for ( auto it = tempset.begin(); it != tempset.end(); it++ ){
            std::cout<<*it<<"  ";
        }
        std::cout<<std::endl;
    }
}

} //namespace husky
#endif
