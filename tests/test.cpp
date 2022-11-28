#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "calculator.hpp"

TEST_CASE("Testing calculator")
{
    Calculator c;

    REQUIRE(c.parse("   6 * 9 + 42.5 - 2,4"));
    REQUIRE(c.calculate() == (6 * 9 + 42.5 - 2.4));
    REQUIRE(c.parse("2*π+54-3.39/2+pi*5-PI"));
    REQUIRE(c.calculate() == (2.0 * std::numbers::pi + 54.0 - 3.39 / 2.0 + std::numbers::pi * 5.0 - std::numbers::pi));

    // REQUIRE(!c.parse("64abcd * 2"));
}