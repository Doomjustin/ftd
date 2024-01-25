#ifndef FTD_NET_POSIX_ERROR_H
#define FTD_NET_POSIX_ERROR_H

#include <string>
#include <source_location>

namespace ftd {

static constexpr int INVALID_RESULT = -1;
static constexpr int INVALID_FD = -1;

void check_result(int result, const std::string& caller);

template<typename T>
void check_result(T result, std::source_location location = std::source_location::current())
{
    check_result(result, location.function_name());
}

template<typename T>
void check_result(T* ptr, std::source_location location = std::source_location::current())
{
    if (ptr == nullptr)
        check_result(INVALID_RESULT, location.function_name());
    else
        check_result(0, location.function_name());
}

} // namespace ftd

#endif // FTD_NET_POSIX_ERROR_H