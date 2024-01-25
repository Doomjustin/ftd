#include "Cast.h"
#include "Error.h"

#include <sys/types.h>
#include <sys/socket.h>

namespace ftd {

int as_int(Domain domain)
{
    switch (domain) {
    case Domain::IPv4:
        return AF_INET;
    case Domain::IPv6:
        return AF_INET6;
    default:
        return INVALID_RESULT;
    }
}

int as_int(Type type)
{
    switch (type) {
    case Type::TCP:
        return SOCK_STREAM;
    case Type::UDP:
        return SOCK_DGRAM;
    default:
        return INVALID_RESULT;
    }
}

int as_int(Protocol protocol)
{
    switch (protocol) {
    case Protocol::Undefined:
    default:
        return 0;
    }
}

} // namespace ftd