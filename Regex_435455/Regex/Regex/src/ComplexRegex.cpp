#include <Regex/ComplexRegex.h>

#include <algorithm>
#include <cstddef>
#include <regex>
#include <sstream>

namespace complexRegex
{
// student code begin
uint32_t countMatches(const std::string &sentence, const std::vector<std::string> &words)
{
    uint32_t count = 0;
    for (const auto &word : words)
    {
        std::regex pattern(R"(\b)" + word + R"(\b)");

        auto begin = std::sregex_iterator(sentence.begin(), sentence.end(), pattern);
        auto end = std::sregex_iterator();

        while (begin != end)
        {
            count++;
            begin++;
        }
    }
    return count;
}
std::string swapCatchGroups(const std::string &sentence, const std::regex &pattern)
{
    std::smatch match;
    if (!std::regex_search(sentence, match, pattern) || match.size() != 3)
    {
        return sentence;
    }
    std::string result;
    std::string::const_iterator searchStart = sentence.cbegin();
    bool matchedAtLeastOnce = false;

    while (std::regex_search(searchStart, sentence.cend(), match, pattern))
    {
        if (match.size() != 3 || !match[1].matched || !match[2].matched)
        {
            return sentence;
        }
        matchedAtLeastOnce = true;

        result.append(searchStart, match[0].first);
        auto firstGrp = match[1];
        auto secondGrp = match[2];

        if (firstGrp.first > secondGrp.first)
        {
            std::swap(firstGrp, secondGrp);
        }

        if (firstGrp.second > secondGrp.first)
        {
            result.append(match[0].first, match[0].second);
        }
        else
        {
            result.append(match[0].first, firstGrp.first);
            result.append(secondGrp.first, secondGrp.second);
            result.append(firstGrp.second, secondGrp.first);
            result.append(firstGrp.first, firstGrp.second);
            result.append(secondGrp.second, match[0].second);
        }
        searchStart = match[0].second;
    }
    if (!matchedAtLeastOnce)
    {
        return sentence;
    }
    result.append(searchStart, sentence.cend());
    return result;
}

std::string fillTemplateString(const std::string &templateString, const std::map<std::string, std::string> &args)
{
    std::string result = templateString;

    for (const auto &pair : args)
    {
        std::regex pattern("\\{" + pair.first + "\\}");
        result = std::regex_replace(result, pattern, pair.second);
    }
    return result;
}
bool sortByCatchGroupValue(std::vector<std::string> &sentences, const std::regex &pattern)
{
    std::vector<std::pair<std::string, std::string>> extractedData;

    for (const auto &sentence : sentences)
    {
        std::smatch match;
        if (std::regex_search(sentence, match, pattern) && match.size() == 2)
        {
            extractedData.emplace_back(sentence, match[1].str());
        }
        else
        {
            return false;
        }
    }
    for (size_t i = 0; i < extractedData.size(); ++i)
    {
        for (size_t j = i + 1; j < extractedData.size(); ++j)
        {
            if (extractedData[j].second < extractedData[i].second)
            {
                std::pair<std::string, std::string> temp = extractedData[i];
                extractedData[i] = extractedData[j];
                extractedData[j] = temp;
            }
        }
    }
    for (size_t i = 0; i < sentences.size(); ++i)
    {
        sentences[i] = extractedData[i].first;
    }
    return true;
}

// student code end

}  // namespace complexRegex