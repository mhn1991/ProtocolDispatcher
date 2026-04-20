#pragma once

#include <string>

namespace ProtocolDispatcher::net {

class Socket {
public:
    void connect(const std::string& host, const std::string& port);
    void send_all(const std::string& data);
    [[nodiscard]] std::string receive();
};

}  // namespace ProtocolDispatcher::net
