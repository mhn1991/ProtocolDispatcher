#include "ProtocolDispatcher/net/Socket.hpp"

namespace ProtocolDispatcher::net {

void Socket::connect(const std::string&, const std::string&) {}

void Socket::send_all(const std::string&) {}

std::string Socket::receive() {
    return {};
}

}  // namespace ProtocolDispatcher::net
