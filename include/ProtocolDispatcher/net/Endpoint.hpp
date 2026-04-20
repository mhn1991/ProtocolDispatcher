#pragma once

#include <string>

namespace ProtocolDispatcher::net {

struct Endpoint {
    std::string host;
    std::string port;
};

}  // namespace ProtocolDispatcher::net
