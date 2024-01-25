#include "net/Socket.h"
#include <memory>

#if defined(__unix__)
    #include "posix/PosixSocket.h"
#endif

namespace ftd::net {

ISocket::ISocket(int id, Domain domain, Type type, Protocol protocol)
  : id_{ id }, domain_{ domain }, type_{ type }, protocol_{ protocol }
{}


std::unique_ptr<ISocket> make_socket(Domain domain, Type type, Protocol protocol)
{
#if defined(__unix__)
    return std::make_unique<PosixSocket>(domain, type, protocol);
#else
    static_assert(false, "Only support posix enviroment yet");
    return nullptr;
#endif
}

std::unique_ptr<ISocket> make_socket(int id, Domain domain, Type type, Protocol protocol)
{
#if defined(__unix__)
    return std::make_unique<PosixSocket>(id, domain, type, protocol);
#else
    static_assert(false, "Only support posix enviroment yet");
    return nullptr;
#endif
}

} // namespace ftd::net