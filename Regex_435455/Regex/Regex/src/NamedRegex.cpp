#include <Regex/NamedRegex.h>

#include <regex>
#include <string>

namespace namedRegex
{

// student code begin
bool NamedRegex::validateInputPattern(const std::string &regexTemplate)
{
    std::regex namePattern(R"(\(\?<[a-zA-Z_][a-zA-Z0-9_]*>)");
    return std::regex_search(regexTemplate, namePattern);
}
NamedRegex::NamedRegex(const std::string &regexTemplate) : standardRegex_(), groupNames_()
{
    size_t groupIndex = 1;
    std::string transformed;

    for (size_t i = 0; i < regexTemplate.length(); ++i)
    {
        if (regexTemplate[i] == '\\')
        {
            transformed.push_back(regexTemplate[i]);
            if (i + 1 < regexTemplate.length())
            {
                transformed.push_back(regexTemplate[i + 1]);
                i++;
            }
        }
        else if (regexTemplate[i] == '(')
        {
            transformed.push_back(regexTemplate[i]);

            if (i + 1 < regexTemplate.length() && regexTemplate[i + 1] == '?')
            {
                if (i + 2 < regexTemplate.length() && regexTemplate[i + 2] == '<')
                {
                    size_t endBracket = regexTemplate.find('>', i + 3);
                    if (endBracket != std::string::npos)
                    {
                        std::string name = regexTemplate.substr(i + 3, endBracket - (i + 3));
                        groupNames_[groupIndex] = name;
                        groupIndex++;
                        i = endBracket;
                    }
                }
            }
            else
            {
                groupIndex++;
            }
        }
        else
        {
            transformed.push_back(regexTemplate[i]);
        }
    }

    standardRegex_ = std::regex(transformed);
}

NamedParameters NamedRegex::getMatches(const std::string &inputString) const
{
    NamedParameters result;
    std::smatch match;

    if (std::regex_search(inputString, match, standardRegex_))
    {
        for (const auto &pair : groupNames_)
        {
            size_t index = pair.first;
            const std::string &name = pair.second;

            if (index < match.size() && match[index].matched)
            {
                std::string val = match[index].str();

                bool isNumeric = !val.empty();
                for (char c : val)
                {
                    if (c < '0' || c > '9')
                    {
                        isNumeric = false;
                        break;
                    }
                }

                if (isNumeric)
                {
                    try
                    {
                        uint64_t intVal = std::stoull(val);
                        result[name] = intVal;
                    }
                    catch (...)
                    {
                        result[name] = val;
                    }
                }
                else
                {
                    result[name] = val;
                }
            }
        }
    }

    return result;
}
// student code end

}  // namespace namedRegex