#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <cmath>
#include <numbers>
#include <unordered_map>
#include <iostream>

class Calculator
{
public:
    typedef double num;

    bool parse(const std::string &str);
    num calculate();

    const std::string &getParseError() const noexcept { return parseError; }

private:
    std::string parseStr, parseError;
    std::vector<std::string> operations;

    static constexpr std::string_view highPriorityOperators{"^"}, mediumPriorityOperators{"/*"}, lowPriorityOperators{"+-"},
        operators{"^/*+-"};

    static const std::unordered_map<std::string_view, num> constants;
    static const std::unordered_map<std::string_view, std::function<num(num)>> singleParamFunctions;

    void parseRecursive(size_t begin, size_t end);
    num calculateRecursive(const std::string &str);
    num calculateStrToNum(std::string str);
};