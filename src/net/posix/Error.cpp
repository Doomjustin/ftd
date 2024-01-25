#include "Error.h"
#include "utility/Log.h"

#include <system_error>
#include <format>
#include <cerrno>
#include <cstring>

namespace ftd {

void check_result(int result, const std::string& caller)
{
    if (result == INVALID_RESULT) {
        int error = errno;
        std::string error_msg = std::format("{} error", caller);
        LOG_ERROR("{}, {}", caller, std::strerror(error));
        throw std::system_error{ error, std::generic_category(), error_msg };
    }
}

} // namespace ftd