#include "catch2/matchers/catch_matchers.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <ftd/net/Endpoint.h>

TEST_CASE("test constructor", "[endpoint][constructor]") 
{
    SECTION("host, port")
    {
        ftd::net::Endpoint endpoint{ "127.0.0.1", 12345 };
        REQUIRE(endpoint.port() == 12345);
        REQUIRE_THAT(endpoint.host(), Catch::Matchers::Equals("127.0.0.1"));
    }

    SECTION("port only")
    {
        ftd::net::Endpoint endpoint{ 12345 };
        REQUIRE(endpoint.port() == 12345);
        REQUIRE_THAT(endpoint.host(), Catch::Matchers::Equals(""));
    }

    SECTION("default constructor")
    {
        ftd::net::Endpoint endpoint{};
        REQUIRE(endpoint.port() == 0);
        REQUIRE_THAT(endpoint.host(), Catch::Matchers::Equals(""));
    }
}

TEST_CASE("test operator", "[endpoint][operator]")
{
    SECTION("operator==")
    {
        ftd::net::Endpoint e1{ 12345 };
        ftd::net::Endpoint e2{ 12345 };

        REQUIRE(e1 == e2);

        ftd::net::Endpoint e3{ "1", 12345 };
        ftd::net::Endpoint e4{ "1", 12345 };

        REQUIRE(e3 == e4);
    }

    SECTION("operator!=")
    {
        ftd::net::Endpoint e1{ "2", 12345 };
        ftd::net::Endpoint e2{ "1", 12345 };

        REQUIRE(e1 != e2);
    }
}

TEST_CASE("test method", "[endpoint][method]")
{
    SECTION("port only", "[to_string]")
    {
        ftd::net::Endpoint e{ 12345 };
        REQUIRE_THAT(e.to_string(), Catch::Matchers::Equals("[ANY_HOST:12345]"));
    }

    SECTION("host only", "[to_string]")
    {
        ftd::net::Endpoint e{ "localhost" };
        REQUIRE_THAT(e.to_string(), Catch::Matchers::Equals("[localhost:0]"));
    }

    SECTION("all parameters constructor", "[to_string]")
    {
        ftd::net::Endpoint e{ "127.0.0.1", 21313 };
        REQUIRE_THAT(e.to_string(), Catch::Matchers::Equals("[127.0.0.1:21313]"));
    }

    SECTION("default constructor", "[to_string]")
    {
        ftd::net::Endpoint e{};
        REQUIRE_THAT(e.to_string(), Catch::Matchers::Equals("[ANY_HOST:0]"));
    }
}