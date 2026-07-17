#pragma once

#include <iostream>
#include <sstream>
#include <variant>

namespace variantVisitors
{
// student code begin
using PrintVariant = std::variant<bool, int, float>;
struct PrintVisitor
{
    void operator()(bool b)
    {
        (void)b;
        std::cout << "bool";
    }
    void operator()(int i)
    {
        (void)i;
        std::cout << "int";
    }
    void operator()(float f)
    {
        (void)f;
        std::cout << "float";
    }
};

using ToStringVariant = std::variant<bool, int, double, float>;
struct ToStringVisitor
{
    std::string operator()(bool b) { return b ? "true" : "false"; }

    std::string operator()(int i)
    {
        std::stringstream ss;
        ss << std::hex << i;
        return ss.str();
    }

    std::string operator()(double d)
    {
        std::string str = std::to_string(d);

        str.erase(str.find_last_not_of('0') + 1, std::string::npos);

        if (str.back() == '.')
        {
            str.pop_back();
        }
        return str;
    }

    std::string operator()(float f)
    {
        std::string str = std::to_string(f);

        str.erase(str.find_last_not_of('0') + 1, std::string::npos);

        if (str.back() == '.')
        {
            str.pop_back();
        }
        return str;
    }
};

// student code end

}  // namespace variantVisitors
