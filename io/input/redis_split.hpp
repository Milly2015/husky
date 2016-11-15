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

#include "base/serialization.hpp"

namespace husky {
namespace io {

using base::BinStream;

class RedisSplit {
   using keyType = std::string;
   
   public:
    RedisSplit();
    RedisSplit(const RedisSplit& other);

    void set_hostip(const std::string& hostip);
    void set_hostport(const std::string& hostport);
    void set_keyset(const std::vector<keyType> keyset);

    inline const std::string& get_hostip() const { return hostip_; }
    inline const std::string& get_hostport() const { return hostport_; }
    inline const std::vector<keyType> get_keyset() const { return keyset_; }

   private:
    std::string hostip_;
    std::string hostport_;
    std::vector<keyType> keyset_;
};

BinStream& operator<<(BinStream& stream, RedisSplit& split);

}  // namespace io
}  // namespace husky
