#include <string>

namespace basicRegex
{

bool validateEmail(const std::string &email);

std::string removeWhitespace(const std::string &str);

std::string extractDomain(const std::string &email);

}  // namespace basicRegex
