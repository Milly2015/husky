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

#include "io/input/redis_split.hpp"

#include <string>

#include "base/serialization.hpp"

namespace husky {
namespace io {

RedisSplit::RedisSplit() {}

RedisSplit::RedisSplit(const RedisSplit& other) {
    hostip_ = other.hostip_;
    hostport_ = other.hostport_;
    keyset_ = other.keyset_;
}

void RedisSplit::set_hostip(const std::string& hostip) {
    hostip_ = hostip;
}

void RedisSplit::set_hostport(const std::string& hostport) {
    hostport_ = hostport; 
}

void RedisSplit::set_keyset(const std::vector<keyType> keyset) {
    std::copy (keyset.begin(), keyset.end(), keyset_.begin());    
}

BinStream& operator<<(BinStream& stream, RedisSplit& split) {
    stream << split.get_hostip() << split.get_hostport() << split.get_keyset();
    return stream;
}

}  // namespace io
}  // namespace husky
