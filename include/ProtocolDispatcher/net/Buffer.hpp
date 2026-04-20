#pragma once

#include <cstddef>
#include <string>

namespace ProtocolDispatcher::net {

class Buffer {
public:
    void append(const std::string& chunk);
    [[nodiscard]] bool empty() const;
    [[nodiscard]] std::size_t size() const;
    [[nodiscard]] const std::string& str() const;
    void clear();

private:
    std::string data_;
};

}  // namespace ProtocolDispatcher::net
