#ifndef FTD_NET_POSIX_SOCKET_H
#define FTD_NET_POSIX_SOCKET_H

#include "net/Socket.h"
#include "Error.h"

namespace ftd::net {

class PosixSocket: public ISocket {
public:
    PosixSocket(int fd, Domain domain, Type type, Protocol protocol);
    PosixSocket(Domain domain, Type type, Protocol protocol);

    ~PosixSocket();

    void close() override;
    constexpr bool closable() const noexcept override
    {
        return id_ != INVALID_FD;
    }
    
    void listen(int backlog) const override;
    void bind(const Endpoint& endpoint) const override;
    std::pair<std::unique_ptr<ISocket>, Endpoint> accept() const override;

    void connect(const Endpoint& endpoint) override;

    std::uint64_t read(void* buffer, std::size_t count) const override;
    std::uint64_t write(const void* buffer, std::size_t count) const override;

    void reuse_address(bool on) const override;
    void reuse_port(bool on) const override;

private:
    static int open(Domain domain, Type type, Protocol protocol);

    void bind_ipv4(const Endpoint& endpoint) const;
    void bind_ipv6(const Endpoint& endpoint) const;

    std::pair<std::unique_ptr<ISocket>, Endpoint> accept_ipv4() const;
    std::pair<std::unique_ptr<ISocket>, Endpoint> accept_ipv6() const;

    void connect_ipv4(const Endpoint& endpoint) const;
    void connect_ipv6(const Endpoint& endpoint) const; 
};

} // namespace ftd::net

#endif // FTD_NET_POSIX_SOCKET_H