#ifndef FTD_UTILITY_LOG_H
#define FTD_UTILITY_LOG_H

#include <memory>
#include <string_view>
#include <format>

namespace ftd {

enum class LogLevel: char {
    Off,
    Error,
    Warning,
    Debug,
    Info,
    Trace
};

class Logger {
public:
    virtual ~Logger() = default;

    virtual void error(std::string_view message) noexcept = 0;
    virtual void warning(std::string_view message) noexcept = 0;
    virtual void debug(std::string_view message) noexcept = 0;
    virtual void info(std::string_view message) noexcept = 0;
    virtual void trace(std::string_view message) noexcept = 0;

    constexpr LogLevel level() const noexcept { return level_; }
    virtual void level(LogLevel level) noexcept = 0;

    virtual void pattern(const std::string& fmt) noexcept = 0;

protected:
    LogLevel level_ = LogLevel::Debug;
};

std::unique_ptr<Logger> make_logger(std::string_view name);


namespace log {

Logger& default_logger();

void pattern(const std::string& fmt);
void level(LogLevel level);

template<typename... T>
void error(std::format_string<T...> fmt, T&&... args)
{
    default_logger().error(std::format(fmt, std::forward<T>(args)...));
}

template<typename... T>
void warning(std::format_string<T...> fmt, T&&... args)
{
    default_logger().warning(std::format(fmt, std::forward<T>(args)...));
}

template<typename... T>
void debug(std::format_string<T...> fmt, T&&... args)
{
    default_logger().debug(std::format(fmt, std::forward<T>(args)...));
}

template<typename... T>
void info(std::format_string<T...> fmt, T&&... args)
{
    default_logger().info(std::format(fmt, std::forward<T>(args)...));
}

template<typename... T>
void trace(std::format_string<T...> fmt, T&&... args)
{
    default_logger().trace(std::format(fmt, std::forward<T>(args)...));
}

} // namespace ftd::log

} // namespace ftd


#if defined (FTD_DEBUG)
    #define LOG_ERROR(...) ftd::log::error(__VA_ARGS__)
    #define LOG_WARN(...)  ftd::log::warning(__VA_ARGS__)
    #define LOG_DEBUG(...) ftd::log::debug(__VA_ARGS__)
    #define LOG_INFO(...)  ftd::log::info(__VA_ARGS__)
    #define LOG_TRACE(...) ftd::log::trace(__VA_ARGS__)
#else
    #define LOG_ERROR(...)
    #define LOG_WARN(...)
    #define LOG_DEBUG(...)
    #define LOG_INFO(...) 
    #define LOG_TRACE(...)
#endif

#endif // FTD_UTILITY_LOG_H