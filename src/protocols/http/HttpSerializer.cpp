#include "ProtocolDispatcher/protocols/http/HttpSerializer.hpp"

#include <sstream>

namespace ProtocolDispatcher::protocols::http {

std::string HttpSerializer::serialize(const HttpRequest& request) const {
    std::ostringstream stream;
    stream << to_string(request.method) << ' ' << request.path << " HTTP/1.1\r\n";
    stream << "Host: " << request.host << "\r\n";

    for (const auto& header : request.headers) {
        stream << header.name << ": " << header.value << "\r\n";
    }

    if (!request.body.empty()) {
        stream << "Content-Length: " << request.body.size() << "\r\n";
    }

    stream << "\r\n" << request.body;
    return stream.str();
}

}  // namespace ProtocolDispatcher::protocols::http
