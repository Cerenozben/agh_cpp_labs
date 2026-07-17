#include <map>
#include <regex>
#include <set>
#include <string>
#include <variant>

namespace namedRegex
{

using CatchGroupVariantNode = std::variant<std::string, uint64_t>;
using NamedParameters = std::map<std::string, CatchGroupVariantNode>;

class NamedRegex
{
public:
    /// @brief Default constructor
    /// @details Named catch group format: (?<name>pattern)
    /// Example template: ^(?<VendorName>.+)_(?<ProductType>.+)_(?<SerialNumber>\d{6})_(?<Date>\d{8})_(?<Time>\d{6})$
    /// The validity of the input template is assumed, as this class provides the static public method to check it
    /// @param regexTemplate input template defined as regex pattern with named catch-groups
    explicit NamedRegex(const std::string &regexTemplate);

    virtual ~NamedRegex() = default;                     // default dtor
    NamedRegex(const NamedRegex &) = delete;             // copy ctor
    NamedRegex(NamedRegex &&) = delete;                  // move ctor
    NamedRegex &operator=(const NamedRegex &) = delete;  // copy assignment
    NamedRegex &operator=(NamedRegex &&) = delete;       // move assignment

    /// @brief The method that checks the validity of input regex template
    /// @param regexTemplate input template defined as regex pattern with named catch-groups
    /// @return true if pattern is valid, false otherwise
    static bool validateInputPattern(const std::string &regexTemplate);

    /// @brief The method that extracts the content of named regex catch groups as a map
    /// @param inputString input string in which the named capture groups' values shall be extracted
    /// @return the values of named regex catch groups as a map
    NamedParameters getMatches(const std::string &inputString) const;

    // student code begin
private:
    std::regex standardRegex_;
    std::map<size_t, std::string> groupNames_;
    // student code end
};

}  // namespace namedRegex