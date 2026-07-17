#include <regex>
#include <string>
#include <vector>

namespace complexRegex
{

uint32_t countMatches(const std::string &sentence, const std::vector<std::string> &words);

std::string swapCatchGroups(const std::string &sentence, const std::regex &pattern);

std::string fillTemplateString(const std::string &templateString, const std::map<std::string, std::string> &args);

bool sortByCatchGroupValue(std::vector<std::string> &sentences, const std::regex &pattern);

}  // namespace complexRegex
