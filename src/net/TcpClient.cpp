#include "ProtocolDispatcher/net/TcpClient.hpp"

#include "ProtocolDispatcher/net/Resolver.hpp"
#include "ProtocolDispatcher/net/Socket.hpp"

namespace ProtocolDispatcher::net {

std::string TcpClient::round_trip(const Endpoint& endpoint, const std::string& request_bytes) {
    const Endpoint resolved_endpoint = Resolver{}.resolve(endpoint);

    Socket socket;
    socket.connect(resolved_endpoint.host, resolved_endpoint.port);
    socket.send_all(request_bytes);
    return socket.receive();
}

}  // namespace ProtocolDispatcher::net
