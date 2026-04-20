#pragma once

#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace ProtocolDispatcher::protocols::http {

enum class HttpMethod {
    Get,
    Post,
    Put,
    Delete
};

struct HttpHeader {
    std::string name;
    std::string value;
};

struct HttpQueryParam {
    std::string name;
    std::string value;
};

struct HttpRequest {
    HttpMethod method{HttpMethod::Get};
    std::string scheme{"http"};
    std::string host;
    std::string path{"/"};
    std::string port{"80"};
    std::vector<HttpQueryParam> query_params;
    std::vector<HttpHeader> headers;
    std::string body;
};

inline std::string_view to_string(HttpMethod method) {
    switch (method) {
    case HttpMethod::Get:
        return "GET";
    case HttpMethod::Post:
        return "POST";
    case HttpMethod::Put:
        return "PUT";
    case HttpMethod::Delete:
        return "DELETE";
    }

    return "GET";
}

}  // namespace ProtocolDispatcher::protocols::http
