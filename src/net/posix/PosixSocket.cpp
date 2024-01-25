#include "PosixSocket.h"
#include "Cast.h"
#include "Error.h"
#include "utility/Log.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


namespace ftd::net {

sockaddr_in ipv4_cast(const Endpoint& endpoint)
{
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_port = ::htons(endpoint.port());

    if (endpoint.host().empty()) {
        address.sin_addr.s_addr = INADDR_ANY;
    }
    else {
        auto res = ::inet_pton(AF_INET, endpoint.host().c_str(), &address.sin_addr);
        check_result(res);
    }
    return address;
}

sockaddr_in6 ipv6_cast(const Endpoint& endpoint)
{
    sockaddr_in6 address{};
    address.sin6_family = AF_INET6;
    address.sin6_port = ::htons(endpoint.port());

    if (endpoint.host().empty()) {
        address.sin6_addr = in6addr_any;
    }
    else {
        auto res = ::inet_pton(AF_INET6, endpoint.host().c_str(), &address.sin6_addr);
        check_result(res);
    }

    return address;
}

Endpoint address_cast(const sockaddr_in& sock_addr)
{
    auto port = ::ntohs(sock_addr.sin_port);
    char host[INET_ADDRSTRLEN];
    auto res = ::inet_ntop(AF_INET, &sock_addr.sin_addr, host, INET_ADDRSTRLEN);
    check_result(res);

    return { host, port };
}

Endpoint address_cast(const sockaddr_in6& sock_addr)
{
    auto port = ::ntohs(sock_addr.sin6_port);
    char host[INET6_ADDRSTRLEN];
    auto res = ::inet_ntop(AF_INET6, &sock_addr.sin6_addr, host, INET6_ADDRSTRLEN);
    check_result(res);

    return { host, port };
}


int PosixSocket::open(Domain domain, Type type, Protocol protocol)
{
    auto fd = ::socket(as_int(domain), as_int(type), as_int(protocol));
    check_result(fd);
    LOG_INFO("socket opened: {}", fd);
    return fd;
}

PosixSocket::PosixSocket(int fd, Domain domain, Type type, Protocol protocol)
  : ISocket(fd, domain, type, protocol)
{}

PosixSocket::PosixSocket(Domain domain, Type type, Protocol protocol)
  : ISocket{ open(domain, type, protocol), domain, type, protocol }
{}

PosixSocket::~PosixSocket()
{
    if (closable())
        close();
}

void PosixSocket::close()
{
    auto res = ::close(id_);
    check_result(res);
    LOG_INFO("socket[{}] closed", id_);
    id_ = INVALID_FD;
}

void PosixSocket::listen(int backlog) const
{
    auto res = ::listen(id_, backlog);
    check_result(res);
    LOG_INFO("Socket({}) listening with backlog = {}", id_, backlog);
}

void PosixSocket::bind(const Endpoint& endpoint) const
{
    switch (domain_) {
    case Domain::IPv4:
        bind_ipv4(endpoint);
        break;
    case Domain::IPv6:
        bind_ipv6(endpoint);
        break;
    }
}

std::pair<std::unique_ptr<ISocket>, Endpoint> PosixSocket::accept() const
{
    switch (domain_) {
    case Domain::IPv4:
        return accept_ipv4();
    case Domain::IPv6:
        return accept_ipv6();
    }

    return {};
}

void PosixSocket::connect(const Endpoint& endpoint)
{
    switch (domain_) {
    case Domain::IPv4:
        connect_ipv4(endpoint);
        break;
    case Domain::IPv6:
        connect_ipv6(endpoint);
        break;
    }
}

std::uint64_t PosixSocket::read(void* buffer, std::size_t count) const
{
    auto read_bytes = ::read(id_, buffer, count);
    check_result(read_bytes);
    return read_bytes;
}

std::uint64_t PosixSocket::write(const void* buffer, std::size_t count) const
{
    auto write_bytes = ::write(id_, buffer, count);
    check_result(write_bytes);
    return write_bytes;
}

void PosixSocket::reuse_address(bool on) const
{
    int val = on ? 1 : 0;
    auto res = ::setsockopt(id_, SOL_SOCKET, SO_REUSEADDR,
                            &val, sizeof(val));
    check_result(res);
}

void PosixSocket::reuse_port(bool on) const
{
    int val = on ? 1 : 0;
    auto res = ::setsockopt(id_, SOL_SOCKET, SO_REUSEPORT,
                            &val, sizeof(val));
    check_result(res);
}

void PosixSocket::bind_ipv4(const Endpoint& endpoint) const
{
    auto address = ipv4_cast(endpoint);
    auto res = ::bind(id_, reinterpret_cast<sockaddr*>(&address), sizeof(address));
    check_result(res);
    LOG_INFO("Socket({}) bind to {}:{}", id_, endpoint.host(), endpoint.port());
}

void PosixSocket::bind_ipv6(const Endpoint& endpoint) const
{
    auto address = ipv6_cast(endpoint);
    auto res = ::bind(id_, reinterpret_cast<sockaddr*>(&address), sizeof(address));
    check_result(res);
    LOG_INFO("Socket({}) bind to {}:{}", id_, endpoint.host(), endpoint.port());
}

std::pair<std::unique_ptr<ISocket>, Endpoint> PosixSocket::accept_ipv4() const
{
    sockaddr_in address{};
    socklen_t len{};
    auto res = ::accept(id_, reinterpret_cast<sockaddr*>(&address), &len);
    check_result(res);

    auto socket = std::make_unique<PosixSocket>(res, domain(), type(), protocol());
    auto endpoint = address_cast(address);
    return std::make_pair<std::unique_ptr<ISocket>, Endpoint>(std::move(socket), std::move(endpoint));
}

std::pair<std::unique_ptr<ISocket>, Endpoint> PosixSocket::accept_ipv6() const
{
    sockaddr_in6 address{};
    socklen_t len{};
    auto res = ::accept(id_, reinterpret_cast<sockaddr*>(&address), &len);
    check_result(res);

    auto socket = std::make_unique<PosixSocket>(res, domain(), type(), protocol());
    auto endpoint = address_cast(address);
    return std::make_pair<std::unique_ptr<ISocket>, Endpoint>(std::move(socket), std::move(endpoint));
}

void PosixSocket::connect_ipv4(const Endpoint& endpoint) const
{
    auto target_address = ipv4_cast(endpoint);
    auto res = ::connect(id_, reinterpret_cast<sockaddr*>(&target_address), sizeof(target_address));
    check_result(res);
}

void PosixSocket::connect_ipv6(const Endpoint& endpoint) const
{
    auto target_address = ipv6_cast(endpoint);
    auto res = ::connect(id_, reinterpret_cast<sockaddr*>(&target_address), sizeof(target_address));
    check_result(res);
}

} // namespace ftd::net