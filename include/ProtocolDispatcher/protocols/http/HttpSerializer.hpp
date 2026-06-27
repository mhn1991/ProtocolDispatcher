#pragma once

#include <string>

#include "/home/mhn70/Projects/ProtocolDispatcher/include/ProtocolDispatcher/protocols/http/HttpRequest.hpp"

namespace ProtocolDispatcher::protocols::http {

class HttpSerializer {
public:
    [[nodiscard]] std::string serialize(const HttpRequest& request) const;
};

}  // namespace ProtocolDispatcher::protocols::http
