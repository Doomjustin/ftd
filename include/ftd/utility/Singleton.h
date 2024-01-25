#ifndef FTD_UTILITY_SINGLETON_H
#define FTD_UTILITY_SINGLETON_H

#include <utility>
#include <concepts>
#include <type_traits>

namespace ftd {

template<class T>
concept is_copyable = std::copy_constructible<T> &&
                      std::assignable_from<T&, T&> &&
                      std::assignable_from<T&, const T&> &&
                      std::assignable_from<T&, const T>;

template<typename T, typename... Args>
concept is_singletonizable = std::constructible_from<T, Args...> &&
                             std::movable<T> &&
                             !is_copyable<T>;

template<typename T, typename... Args>
    requires is_singletonizable<T, Args...>
T& make_singleton(Args&&... args)
{
    static T singleton { std::forward<Args>(args)... };
    return singleton;
}

} // namespace ftd

#endif // FTD_UTILITY_SINGLETON_H