#pragma once

#include "/home/mhn70/Projects/ProtocolDispatcher/include/ProtocolDispatcher/protocols/http/HttpRequest.hpp"
#include "/home/mhn70/Projects/ProtocolDispatcher/include/ProtocolDispatcher/protocols/http/HttpResponse.hpp"

namespace ProtocolDispatcher::protocols::http {

class HttpClient {
public:
    [[nodiscard]] HttpResponse send(const HttpRequest& request) const;
};

}  // namespace ProtocolDispatcher::protocols::http
