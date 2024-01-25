#ifndef FTD_NET_ACCEPTOR_H
#define FTD_NET_ACCEPTOR_H

#include "Socket.h"

namespace ftd::net {

template<typename DomainType, typename TypeType>
    requires is_domain<DomainType> && is_type<TypeType>
class BasicAcceptor {
public:
    using Domain = DomainType;
    using Type = TypeType;

    BasicAcceptor()
      : socket_{ make_socket<Domain, Type>() }
    {}

    // not useful whatever
    constexpr int id() const noexcept { return socket_->id(); }

    void listen(int backlog) const { socket_->listen(backlog); }

    void bind(Endpoint endpoint)
    {
        socket_->bind(endpoint);
        self_endpoint_ = std::move(endpoint);
    }

    std::pair<std::unique_ptr<ISocket>, Endpoint> accept() const
    {
        return socket_->accept();
    }

    void reuse_address(bool on) const
    {
        socket_->reuse_address(on);
    }

    void reuse_port(bool on) const
    {
        socket_->reuse_port(on);
    }

protected:
    std::unique_ptr<ISocket> socket_;
    Endpoint self_endpoint_;
};

using Acceptor = BasicAcceptor<IPv4, TCP>;

} // namespace ftd::net

#endif // FTD_NET_ACCEPTOR_H