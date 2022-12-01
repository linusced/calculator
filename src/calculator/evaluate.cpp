#include "calculator.hpp"

const std::unordered_map<std::string_view, double> Calculator::constants{
    {"pi", std::numbers::pi}, {"PI", std::numbers::pi}, {"π", std::numbers::pi}};

const std::unordered_map<std::string_view, std::function<double(double)>> Calculator::singleParamFunctions{
    {"sqrt", [](double x)
     { return std::sqrt(x); }},
    {"sin", [](double x)
     { return std::sin(x); }},
    {"cos", [](double x)
     { return std::cos(x); }},
    {"tan", [](double x)
     { return std::tan(x); }},
    {"asin", [](double x)
     { return std::asin(x); }},
    {"acos", [](double x)
     { return std::acos(x); }},
    {"atan", [](double x)
     { return std::atan(x); }}};

Calculator::Result Calculator::evaluate(std::string str)
{
    Result r;
    try
    {
        str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());

        std::vector<std::string> operations;
        parseRecursive(&str, 0, str.size(), &operations);

        r.value = calculateRecursive(operations.back(), &operations);
        r.error = false;
    }
    catch (...)
    {
        r.error = true;
        r.errorStr = "Syntax error!";
    }
    return r;
}