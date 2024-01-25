#include <ftd/net/Socket.h>

#include <cstdlib>

int main()
{
    auto socket = ftd::net::make_socket(ftd::Domain::IPv4, ftd::Type::TCP, ftd::Protocol::Undefined);

    return EXIT_SUCCESS;
}