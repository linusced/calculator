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
    struct Result
    {
        double value;
        bool error{false};
        std::string errorStr;
    };

    static Result evaluate(std::string str);

private:
    static void parseRecursive(std::string *str, const size_t begin, const size_t end, std::vector<std::string> *operations);

    static double calculateRecursive(const std::string &str, const std::vector<std::string> *operations);
    static double calculateStrToNum(std::string str, const std::vector<std::string> *operations);

    static constexpr std::string_view highPriorityOperators{"^"}, mediumPriorityOperators{"/*"}, lowPriorityOperators{"+-"}, operators{"^/*+-"};

    static const std::unordered_map<std::string_view, double> constants;
    static const std::unordered_map<std::string_view, std::function<double(double)>> singleParamFunctions;

    Calculator() {}
};