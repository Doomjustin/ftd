#include "utility/Log.h"
#include "logger/SpdLogger.h"

#include <memory>

namespace ftd {

std::unique_ptr<Logger> make_logger(std::string_view name)
{
    return std::make_unique<SpdLogger>(name);
}


namespace log {

Logger& default_logger()
{
    static std::unique_ptr<Logger> default_logger_ = make_logger("ftd logger");

    return *default_logger_;
}

void pattern(const std::string& fmt)
{
    default_logger().pattern(fmt);
}

void level(LogLevel level)
{
    default_logger().level(level);
}

} // namespace ftd::log

} // namespace ftd