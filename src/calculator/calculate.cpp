#include "calculator.hpp"

double Calculator::calculateRecursive(const std::string &str, const std::vector<std::string> *operations)
{
    size_t operatorPos = str.find_first_of(operators);
    if (operatorPos == std::string::npos)
        return calculateStrToNum(str, operations);

    double first = calculateStrToNum(str.substr(0, operatorPos), operations),
           second = calculateStrToNum(str.substr(operatorPos + 1), operations);

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

double Calculator::calculateStrToNum(std::string str, const std::vector<std::string> *operations)
{
    if (str.front() == '$')
        return calculateRecursive(operations->at(std::stoi(str.substr(1))), operations);
    else
    {
        auto cFind = constants.find(str);
        if (cFind != constants.end())
            return cFind->second;
        else
        {
            size_t parenthesesBegin = str.find_first_of('(');
            if (parenthesesBegin != std::string::npos)
            {
                auto spfFind = singleParamFunctions.find(str.substr(0, parenthesesBegin));
                if (spfFind != singleParamFunctions.end())
                    return spfFind->second(calculateRecursive(str.substr(parenthesesBegin + 1, str.find_first_of(')') - (parenthesesBegin + 1)), operations));
                else
                    throw "";
            }
            else
            {
                size_t comma = str.find(',');
                if (comma != std::string::npos)
                    str[comma] = '.';

                size_t idx;
                double out = std::stod(str, &idx);
                if (idx != str.size())
                    throw "";

                return out;
            }
        }
    }
}