#pragma once

#include <string>

#include "ProtocolDispatcher/protocols/http/HttpRequest.hpp"

namespace ProtocolDispatcher::protocols::http {

class HttpSerializer {
public:
    [[nodiscard]] std::string serialize(const HttpRequest& request) const;
};

}  // namespace ProtocolDispatcher::protocols::http
