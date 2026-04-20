#include "ProtocolDispatcher/protocols/http/HttpClient.hpp"
#include "ProtocolDispatcher/protocols/http/HttpRequest.hpp"

int main() {
    ProtocolDispatcher::protocols::http::HttpRequest request;
    request.host = "example.com";
    request.path = "/";

    ProtocolDispatcher::protocols::http::HttpClient client;
    const auto response = client.send(request);
    (void)response;
    return 0;
}
