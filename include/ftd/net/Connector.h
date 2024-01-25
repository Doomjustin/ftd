#ifndef FTD_NET_CONNECTOR_H
#define FTD_NET_CONNECTOR_H

#include "Socket.h"

namespace ftd::net {

template<typename DomainType, typename TypeType>
    requires is_domain<DomainType> && is_type<TypeType>
class BasicConnector {
public:
    using Domain = DomainType;
    using Type = TypeType;

    BasicConnector()
      : socket_{ make_socket<Domain, Type>() }
    {}

    constexpr int id() const noexcept { return socket_->id(); }

    std::unique_ptr<ISocket> connect(const Endpoint& target)
    {
        socket_->connect(target);
        // FIXME: I think it's not a good implemention
        return std::move(socket_);
    }

private:
    std::unique_ptr<ISocket> socket_;
};

using Connector = BasicConnector<IPv4, TCP>;

} // namespace ftd::net

#endif // FTD_NET_CONNECTOR_H