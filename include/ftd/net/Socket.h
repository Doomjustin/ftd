#ifndef FTD_NET_SOCKET_H
#define FTD_NET_SOCKET_H

#include "ftd/utility/Noncopyable.h"
#include "Type.h"
#include "Endpoint.h"

#include <memory>

namespace ftd::net {

class ISocket: public Noncopyable {
public:
    ISocket(int id, Domain domain, Type type, Protocol protocol);

    virtual ~ISocket() = default;

    constexpr int id() const noexcept { return id_; }
    constexpr Domain domain() const noexcept { return domain_; }
    constexpr Type type() const noexcept { return type_; }
    constexpr Protocol protocol() const noexcept { return protocol_; }

    virtual void close() = 0;
    virtual constexpr bool closable() const noexcept = 0;

    virtual void listen(int backlog) const = 0;

    virtual void bind(const Endpoint& endpoint) const = 0;

    virtual std::pair<std::unique_ptr<ISocket>, Endpoint> accept() const = 0;

    virtual void connect(const Endpoint& endpoint) = 0;

    virtual std::uint64_t read(void* buffer, std::size_t count) const = 0;

    virtual std::uint64_t write(const void* buffer, std::size_t count) const = 0;

    virtual void reuse_address(bool on) const = 0;
    virtual void reuse_port(bool on) const = 0;

protected:
    int id_;
    const Domain domain_;
    const Type type_;
    const Protocol protocol_;
};

std::unique_ptr<ISocket> make_socket(Domain domain, Type type, Protocol protocol);
std::unique_ptr<ISocket> make_socket(int id, Domain domain, Type type, Protocol protocol);

template<typename DomainType, typename TypeType>
std::unique_ptr<ISocket> make_socket()
{
    return make_socket(DomainTraits<DomainType>::value, 
                       TypeTraits<TypeType>::value, 
                       Protocol::Undefined);
}

template<typename DomainType, typename TypeType>
std::unique_ptr<ISocket> make_socket(int id)
{
    return make_socket(id,
                       DomainTraits<DomainType>::value, 
                       TypeTraits<TypeType>::value, 
                       Protocol::Undefined);
}

} // namespace ftd::net

#endif // FTD_NET_SOCKET_H