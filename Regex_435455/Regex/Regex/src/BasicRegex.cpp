#include <Regex/BasicRegex.h>

#include <regex>

namespace basicRegex
{
// student code begin
bool validateEmail(const std::string &email)
{
    std::regex pattern(R"([a-z A-Z 0-9._%+-]+@[a-z A-Z 0-9.-]+\.[a-z A-Z]{2,})");
    return std::regex_match(email, pattern);
}
std::string removeWhitespace(const std::string &str)
{
    std::regex pattern(R"(\s+)");
    return std::regex_replace(str, pattern, "");
}
std::string extractDomain(const std::string &email)
{
    std::regex pattern(R"(@([a-z A-Z 0-9.-]+\.[a-z A-Z]{2,}))");
    std::smatch match;

    if (std::regex_search(email, match, pattern))
    {
        if (match.size() > 1)
        {
            return match[1].str();
        }
    }
    return "";
}

// student code end

}  // namespace basicRegex