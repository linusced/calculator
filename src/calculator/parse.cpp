#include "calculator.hpp"

bool Calculator::parse(const std::string &str)
{
    parseStr = str;
    parseError.clear();
    operations.clear();

    parseStr.erase(std::remove_if(parseStr.begin(), parseStr.end(), isspace), parseStr.end());

    parseRecursive(0, parseStr.size());

    bool b{false};
    std::cout << str << '\n';
    std::cout << '[';
    for (auto &o : operations)
    {
        if (b)
            std::cout << "    ";

        std::cout << o;
        b = true;
    }
    std::cout << "]\n";

    return !operations.empty();
}

void Calculator::parseRecursive(size_t begin, size_t end)
{
    std::vector<size_t> operatorPosArr;

    size_t pos = parseStr.find_first_of(highPriorityOperators, begin);
    while (pos < end)
    {
        operatorPosArr.push_back(pos);
        pos = parseStr.find_first_of(highPriorityOperators, pos + 1);
    }

    pos = parseStr.find_first_of(mediumPriorityOperators, begin);
    while (pos < end)
    {
        operatorPosArr.push_back(pos);
        pos = parseStr.find_first_of(mediumPriorityOperators, pos + 1);
    }

    pos = parseStr.find_first_of(lowPriorityOperators, begin);
    while (pos < end)
    {
        operatorPosArr.push_back(pos);
        pos = parseStr.find_first_of(lowPriorityOperators, pos + 1);
    }

    if (operatorPosArr.size() == 1)
    {
        operations.push_back(parseStr.substr(begin, end - begin));
        operations.back().erase(std::remove_if(operations.back().begin(), operations.back().end(), isspace), operations.back().end());
    }
    else
    {
        while (!operatorPosArr.empty())
        {
            size_t opBegin{begin}, opEnd{end};

            for (size_t j = 1; j < operatorPosArr.size(); j++)
            {
                if (operatorPosArr[j] + 1 < operatorPosArr.front() && operatorPosArr[j] + 1 > opBegin)
                    opBegin = operatorPosArr[j] + 1;
                else if (operatorPosArr[j] > operatorPosArr.front() && operatorPosArr[j] < opEnd)
                    opEnd = operatorPosArr[j];
            }

            parseRecursive(opBegin, opEnd);

            std::string replace{'$' + std::to_string(operations.size() - 1)};
            replace.resize(opEnd - opBegin, ' ');
            parseStr.replace(opBegin, opEnd - opBegin, replace);

            operatorPosArr.erase(operatorPosArr.begin());
        }
    }
}