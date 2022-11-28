#include "calculator.hpp"

const std::unordered_map<std::string_view, Calculator::num> Calculator::constants{
    {"pi", std::numbers::pi}, {"PI", std::numbers::pi}, {"π", std::numbers::pi}};

const std::unordered_map<std::string_view, std::function<Calculator::num(Calculator::num)>> Calculator::singleParamFunctions{
    {"sqrt", [](Calculator::num x)
     { return std::sqrt(x); }},
    {"sin", [](Calculator::num x)
     { return std::sin(x); }},
    {"cos", [](Calculator::num x)
     { return std::cos(x); }},
    {"tan", [](Calculator::num x)
     { return std::tan(x); }},
    {"asin", [](Calculator::num x)
     { return std::asin(x); }},
    {"acos", [](Calculator::num x)
     { return std::acos(x); }},
    {"atan", [](Calculator::num x)
     { return std::atan(x); }}};

Calculator::num Calculator::calculate()
{
    return calculateRecursive(operations.back());
}

Calculator::num Calculator::calculateRecursive(const std::string &str)
{
    size_t operatorPos = str.find_first_of(operators);
    if (operatorPos == std::string::npos)
        return calculateStrToNum(str);

    num first = calculateStrToNum(str.substr(0, operatorPos)),
        second = calculateStrToNum(str.substr(operatorPos + 1));

    switch (str[operatorPos])
    {
    case '^':
        return std::pow(first, second);
    case '/':
        return first / second;
    case '*':
        return first * second;
    case '+':
        return first + second;
    case '-':
        return first - second;
    }
    return 0.0; // prevent warning
}

Calculator::num Calculator::calculateStrToNum(std::string str)
{
    if (str.front() == '$')
        return calculateRecursive(operations[std::stoi(str.substr(1))]);
    else
    {
        auto cFind = constants.find(str);
        if (cFind != constants.end())
            return cFind->second;
        else
        {
            size_t parenthesesBegin = str.find_first_of('(');
            auto spfFind = singleParamFunctions.find(str.substr(0, parenthesesBegin));
            if (spfFind != singleParamFunctions.end())
                return spfFind->second(calculateRecursive(str.substr(parenthesesBegin + 1, str.find_first_of(')') - (parenthesesBegin + 1))));
            else
            {
                size_t comma = str.find(',');
                if (comma != std::string::npos)
                    str[comma] = '.';

                return std::stold(str);
            }
        }
    }
}