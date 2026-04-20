#include "ProtocolDispatcher/protocols/http/HttpValidator.hpp"

namespace ProtocolDispatcher::protocols::http {

bool HttpValidator::is_valid(const HttpRequest& request) const {
    return !request.host.empty() && !request.path.empty();
}

}  // namespace ProtocolDispatcher::protocols::http
