#include "calculator.hpp"

void Calculator::parseRecursive(std::string *str, const size_t begin, const size_t end, std::vector<std::string> *operations)
{
    size_t pos = str->find_first_of('(', begin);
    while (pos < end)
    {
        size_t parenthesesEnd, parenthesesCount{1};
        for (size_t i = pos + 1; i < end; i++)
        {
            if (str->at(i) == '(')
                parenthesesCount++;
            else if (str->at(i) == ')')
            {
                parenthesesCount--;
                if (parenthesesCount == 0)
                {
                    parenthesesEnd = i;
                    break;
                }
            }
        }

        size_t operatorPos = str->find_first_of(operators, begin), newOperatorPos = operatorPos;
        while (newOperatorPos < pos)
        {
            operatorPos = newOperatorPos;
            newOperatorPos = str->find_first_of(operators, operatorPos + 1);
        }

        std::string spfSubstr;
        if (operatorPos >= pos)
            spfSubstr = str->substr(begin, pos - begin);
        else
            spfSubstr = str->substr(operatorPos + 1, pos - operatorPos - 1);

        bool isFunctionCall{false};
        auto spfFind = singleParamFunctions.find(spfSubstr);
        if (spfFind != singleParamFunctions.end())
            isFunctionCall = true;

        if (!isFunctionCall || str->find_first_of(operators, pos + 1) < parenthesesEnd)
        {
            parseRecursive(str, pos + 1, parenthesesEnd, operations);

            if (isFunctionCall)
            {
                pos++;
                parenthesesEnd--;
            }

            std::string replace{'$' + std::to_string(operations->size() - 1)};
            replace.resize((parenthesesEnd + 1) - pos, ' ');
            str->replace(pos, (parenthesesEnd + 1) - pos, replace);
        }

        pos = str->find_first_of('(', parenthesesEnd + 1);
    }

    std::vector<size_t> operatorPosArr;

    pos = str->find_first_of(highPriorityOperators, begin);
    while (pos < end)
    {
        operatorPosArr.push_back(pos);
        pos = str->find_first_of(highPriorityOperators, pos + 1);
    }

    pos = str->find_first_of(mediumPriorityOperators, begin);
    while (pos < end)
    {
        operatorPosArr.push_back(pos);
        pos = str->find_first_of(mediumPriorityOperators, pos + 1);
    }

    pos = str->find_first_of(lowPriorityOperators, begin);
    while (pos < end)
    {
        operatorPosArr.push_back(pos);
        pos = str->find_first_of(lowPriorityOperators, pos + 1);
    }

    if (operatorPosArr.size() <= 1)
    {
        operations->push_back(str->substr(begin, end - begin));
        operations->back().erase(std::remove_if(operations->back().begin(), operations->back().end(), isspace), operations->back().end());
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

            parseRecursive(str, opBegin, opEnd, operations);

            std::string replace{'$' + std::to_string(operations->size() - 1)};
            replace.resize(opEnd - opBegin, ' ');
            str->replace(opBegin, opEnd - opBegin, replace);

            operatorPosArr.erase(operatorPosArr.begin());
        }
    }
}