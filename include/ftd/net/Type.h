#ifndef FTD_NET_TYPE_H
#define FTD_NET_TYPE_H

#include <type_traits>
#include <cstdint>

namespace ftd {

enum class Domain {
    IPv4,
    IPv6
};

enum class Type {
    TCP,
    UDP,
};

enum class Protocol {
    Undefined
};

struct IPv4 {};
struct IPv6 {};

struct TCP {};
struct UDP {};

template<typename Domain>
concept is_domain = std::is_same_v<Domain, IPv4> ||
                    std::is_same_v<Domain, IPv6>;

template<typename Type>
concept is_type = std::is_same_v<Type, TCP> ||
                  std::is_same_v<Type, UDP>;



template<typename T>
struct DomainTraits;

template<>
struct DomainTraits<IPv4> {
    static constexpr Domain value = Domain::IPv4;
};

template<>
struct DomainTraits<IPv6> {
    static constexpr Domain value = Domain::IPv6;
};

template<typename T>
struct TypeTraits;

template<>
struct TypeTraits<TCP> {
    static constexpr Type value = Type::TCP;
};

template<>
struct TypeTraits<UDP> {
    static constexpr Type value = Type::UDP;
};


using Port = std::uint16_t;

static constexpr Port ANY_PORT = 0;
static constexpr const char* ANY_HOST = "";
static constexpr const char* LOCAL_HOST = "localhost";
static constexpr const char* LOCAL_HOST_IPV4 = "127.0.0.1";
static constexpr const char* LOCAL_HOST_IPv6 = "::1";
static constexpr int IPV4_LENGTH = 32;
static constexpr int IPv6_LENGTH = 128;

} // namespace ftd

#endif // FTD_NET_TYPE_H