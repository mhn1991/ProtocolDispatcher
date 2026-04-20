#pragma once

#include <string>

#include "ProtocolDispatcher/net/Endpoint.hpp"

namespace ProtocolDispatcher::net {

class TcpClient {
public:
    [[nodiscard]] std::string round_trip(const Endpoint& endpoint, const std::string& request_bytes);
};

}  // namespace ProtocolDispatcher::net
