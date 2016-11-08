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

#include <map>
#include <set>
#include <string>

#include "hiredis.h"

namespace husky {

    class RedisAssigner {
    public :
        RedisAssigner();
        void master_redis_req_handler();
        void master_redis_req_end_handler();
        void master_setup_handler();
        virtual ~RedisAssigner();

        redisContext *initCtx(const char *ip, int port, const struct timeval tv);
        void dumpkeymap();
    private :
        std::string _masterredishost;
        int _masterredisport;
        redisContext* _rContext;
        std::map<std::string, std::set<std::string>> _keysetmap;

    };

} //namespace husky


#endif
