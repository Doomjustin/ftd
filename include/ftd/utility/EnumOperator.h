#ifndef FTD_UTILITY_ENUM_OPERATOR_H
#define FTD_UTILITY_ENUM_OPERATOR_H

#include <concepts>
#include <type_traits>

namespace ftd {

template<typename E>
struct is_scoped_enum: std::bool_constant<requires
    {
        requires std::is_enum_v<E>;
        requires !std::is_convertible_v<E, std::underlying_type_t<E>>;
    }>
{};

template< class T >
inline constexpr bool is_scoped_enum_v = is_scoped_enum<T>::value;


namespace enum_operator {

template<typename Enum>
    requires is_scoped_enum_v<Enum>
constexpr std::underlying_type_t<Enum> to_underlying(Enum e) noexcept
{
    return static_cast<std::underlying_type_t<Enum>>(e);
}

template<typename Enum>
    requires is_scoped_enum_v<Enum>
constexpr bool enum_any(Enum e) noexcept
{
    return static_cast<bool>(e);
}

template<typename Enum>
    requires is_scoped_enum_v<Enum>
constexpr Enum operator|(Enum lhs, Enum rhs) noexcept
{
    return static_cast<Enum>(to_underlying(lhs) | to_underlying(rhs));
}

template<typename Enum>
    requires is_scoped_enum_v<Enum>
constexpr Enum operator&(Enum lhs, Enum rhs) noexcept
{
    return static_cast<Enum>(to_underlying(lhs) & to_underlying(rhs));
}

template<typename Enum>
    requires is_scoped_enum_v<Enum>
constexpr Enum operator^(Enum lhs, Enum rhs) noexcept
{
    return static_cast<Enum>(to_underlying(lhs) ^ to_underlying(rhs));
}

template<typename Enum>
    requires is_scoped_enum_v<Enum>
constexpr Enum operator~(Enum e) noexcept
{
    return static_cast<Enum>(~to_underlying(e));
}

template<typename Enum>
    requires is_scoped_enum_v<Enum>
constexpr Enum& operator|=(Enum& lhs, Enum rhs) noexcept
{
    return static_cast<Enum&>(static_cast<std::underlying_type_t<Enum>&>(lhs) |= to_underlying(rhs));
}

template<typename Enum>
    requires is_scoped_enum_v<Enum>
constexpr Enum& operator&=(Enum& lhs, Enum rhs) noexcept
{
    return static_cast<Enum&>(static_cast<std::underlying_type_t<Enum>&>(lhs) &= to_underlying(rhs));
}

template<typename Enum>
    requires is_scoped_enum_v<Enum>
constexpr Enum& operator^=(Enum& lhs, Enum rhs) noexcept
{
    return static_cast<Enum&>(static_cast<std::underlying_type_t<Enum>&>(lhs) ^= to_underlying(rhs));
}

} // namespace ftd::enum_operator

} // namespace ftd

#endif // FTD_UTILITY_ENUM_OPERATOR_H