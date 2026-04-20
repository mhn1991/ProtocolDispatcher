#pragma once

#include <string>

#include "ProtocolDispatcher/protocols/http/HttpResponse.hpp"

namespace ProtocolDispatcher::protocols::http {

class HttpParser {
public:
    [[nodiscard]] HttpResponse parse(const std::string& raw_response) const;
};

}  // namespace ProtocolDispatcher::protocols::http
