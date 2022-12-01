#include "config.hpp"
#include "calculator.hpp"

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid argument(s)!\n"
                  << "Usage example: calc \"623.2 ^ 5 * sqrt(5-2) - (3-sin(pi)) * 2\"\n";
        return 1;
    }

    auto c = Calculator::evaluate(argv[1]);
    if (c.error)
    {
        std::cout << c.errorStr << '\n';
        return 1;
    }

    std::cout << c.value << '\n';
    return 0;
}