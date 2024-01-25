#ifndef FTD_NET_ENDPOINT_H
#define FTD_NET_ENDPOINT_H

#include "Type.h"

#include <string>

namespace ftd::net {

class Endpoint {
public:
    static Endpoint parse(const std::string& endpoint);

    Endpoint() = default;
    Endpoint(std::string ip_address, Port port);
    explicit Endpoint(std::string ip_address);
    explicit Endpoint(Port port);

    void host(const std::string& value) noexcept { host_ = value; }
    std::string host() const noexcept { return host_; }

    void port(Port value) noexcept { port_ = value; }
    constexpr Port port() const noexcept { return port_; }

    std::string to_string() const noexcept;

private:
    std::string host_ = ANY_HOST;
    Port port_ = ANY_PORT;
};

bool operator==(const Endpoint& lhs, const Endpoint& rhs);
bool operator!=(const Endpoint& lhs, const Endpoint& rhs);

} // namespace ftd::net

#endif // FTD_NET_ENDPOINT_H