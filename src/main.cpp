#include "config.hpp"
#include "calculator.hpp"

int main(int argc, char const *argv[])
{
    Calculator c;
    if (!c.parse("42.5 - 6 * 9^2 + sqrt(2,4)"))
    {
        std::cout << c.getParseError() << '\n';
        return 1;
    }

    std::cout << c.calculate() << '\n';
    return 0;
}