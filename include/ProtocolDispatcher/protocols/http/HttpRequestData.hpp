#pragma once
#include<string>
#include<vector>

namespace ProtocolDispatcher::protocols::http {

  enum class HttpMethod{
    Get,
    Post,
    Put,
    Del
  };

struct HttpRequestData {
  HttpMethod method;
  std::string host;
  std::string path;
  std::vector<std::pair<std::string, std::string>> params;
  std::vector<std::pair<std::string, std::string>> headers;
  std::string body;
};

}  
