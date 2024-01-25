#include <ftd/utility/Log.h>

#include <cstdlib>


int main()
{
    ftd::log::level(ftd::LogLevel::Trace);
    ftd::log::trace("TEST LOG");
    ftd::log::info("TEST LOG, {}", "info");
    ftd::log::debug("TEST LOG, {} {}", 1, "main");

    LOG_ERROR("error {}", "test");

    return EXIT_SUCCESS;
}