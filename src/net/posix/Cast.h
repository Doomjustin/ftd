#ifndef FTD_NET_POSIX_CAST_H
#define FTD_NET_POSIX_CAST_H

#include "net/Type.h"

namespace ftd {

int as_int(Domain domain);
int as_int(Type type);
int as_int(Protocol protocol);

} // namespace ftd

#endif // FTD_NET_POSIX_CAST_H