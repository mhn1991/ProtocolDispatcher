#pragma once

#include "ProtocolDispatcher/net/Endpoint.hpp"

namespace ProtocolDispatcher::net {

class Resolver {
public:
    [[nodiscard]] Endpoint resolve(const Endpoint& endpoint) const;
};

}  // namespace ProtocolDispatcher::net
