#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "calculator.hpp"

TEST_CASE("Calculator")
{
        auto c1 = Calculator::evaluate("   \t6 * 9 + 42.5 - 2,4");

        REQUIRE(!c1.error);
        REQUIRE(c1.value == 6.0 * 9.0 + 42.5 - 2.4);

        REQUIRE(Calculator::evaluate("2*π+  54- 3.39/ 2+pi* 5- PI").value ==
                2.0 * std::numbers::pi + 54.0 - 3.39 / 2.0 + std::numbers::pi * 5.0 - std::numbers::pi);

        REQUIRE(Calculator::evaluate("((((42.5 - 6) * 9)^(2 * 0.3)) + 5) * sqrt(23.54)").value ==
                (std::pow(((42.5 - 6) * 9), (2 * 0.3)) + 5) * std::sqrt(23.54));

        REQUIRE(Calculator::evaluate("(sqrt(69.420) + 4) * 20.0 - sin(pi/2) * (cos(32.4 + sin(2)) - 2)").value ==
                (std::sqrt(69.420) + 4) * 20.0 - std::sin(std::numbers::pi / 2) * (std::cos(32.4 + std::sin(2)) - 2));

        REQUIRE(Calculator::evaluate("6.592*(1-1)").value == 0);
        REQUIRE(Calculator::evaluate("69.420").value == 69.420);
        REQUIRE(Calculator::evaluate("π").value == std::numbers::pi);

        REQUIRE(Calculator::evaluate("64abcd * 2").error);
}