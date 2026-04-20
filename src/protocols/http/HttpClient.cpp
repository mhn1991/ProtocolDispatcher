#include "ProtocolDispatcher/protocols/http/HttpClient.hpp"

#include "ProtocolDispatcher/net/TcpClient.hpp"
#include "ProtocolDispatcher/protocols/http/HttpParser.hpp"
#include "ProtocolDispatcher/protocols/http/HttpSerializer.hpp"
#include "ProtocolDispatcher/protocols/http/HttpValidator.hpp"

namespace ProtocolDispatcher::protocols::http {

HttpResponse HttpClient::send(const HttpRequest& request) const {
    if (!HttpValidator{}.is_valid(request)) {
        return {};
    }

    const std::string request_bytes = HttpSerializer{}.serialize(request);
    const std::string response_bytes =
        net::TcpClient{}.round_trip(net::Endpoint{request.host, request.port}, request_bytes);
    return HttpParser{}.parse(response_bytes);
}

}  // namespace ProtocolDispatcher::protocols::http
