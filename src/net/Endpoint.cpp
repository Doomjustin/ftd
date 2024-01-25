#include "net/Endpoint.h"

#include <sstream>

namespace ftd::net {

// format supposed to "xxx.xxx.xxx.xxx:xxxxx" or "x:x:x:x:x:x:x:x::xxxxx"
// TODO: 从字符串解析，支持IPv4和IPv6格式
Endpoint Endpoint::parse(const std::string& endpoint)
{
    if (endpoint.empty())
        return Endpoint{};

    return Endpoint{};
}

Endpoint::Endpoint(std::string ip_address, Port port)
  : host_{ std::move(ip_address) }, port_{ port }
{}

Endpoint::Endpoint(std::string ip_address)
  : Endpoint{ std::move(ip_address), ANY_PORT }
{}

Endpoint::Endpoint(Port port)
  : port_{ port }
{}

std::string Endpoint::to_string() const noexcept
{
    std::stringstream ss{};
    ss << '[';
    if (host().empty())
        ss << "ANY_HOST:";
    else
        ss << host() << ':';
    
    ss << port() << ']';
    return ss.str();
}

bool operator==(const Endpoint& lhs, const Endpoint& rhs)
{
    return lhs.host() == rhs.host() &&
           lhs.port() == rhs.port();
}

bool operator!=(const Endpoint& lhs, const Endpoint& rhs)
{
    return !(lhs == rhs);
}

} // namespace ftd::net