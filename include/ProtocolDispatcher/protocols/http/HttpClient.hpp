#pragma once

#include "ProtocolDispatcher/protocols/http/HttpRequest.hpp"
#include "ProtocolDispatcher/protocols/http/HttpResponse.hpp"

namespace ProtocolDispatcher::protocols::http {

class HttpClient {
public:
    [[nodiscard]] HttpResponse send(const HttpRequest& request) const;
};

}  // namespace ProtocolDispatcher::protocols::http
