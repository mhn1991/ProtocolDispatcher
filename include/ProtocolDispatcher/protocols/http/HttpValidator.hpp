#pragma once

#include "ProtocolDispatcher/protocols/http/HttpRequest.hpp"

namespace ProtocolDispatcher::protocols::http {

class HttpValidator {
public:
    [[nodiscard]] bool is_valid(const HttpRequest& request) const;
};

}  // namespace ProtocolDispatcher::protocols::http
