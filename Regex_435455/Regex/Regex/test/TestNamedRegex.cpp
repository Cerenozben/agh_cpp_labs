#include <Regex/NamedRegex.h>
#include <gtest/gtest.h>

#include <string>
#include <variant>

namespace namedRegex
{

namespace
{
template <typename T>
inline void checkValues(const std::map<std::string, T> &expectedValues, const namedRegex::NamedParameters &matches)
{
    for (const auto &[matchName, expectedValue] : expectedValues)
    {
        const bool exists = matches.contains(matchName);
        EXPECT_TRUE(exists);
        if (exists)
        {
            const bool hasValidType = std::holds_alternative<T>(matches.at(matchName));
            EXPECT_TRUE(hasValidType);
            if (hasValidType)
            {
                EXPECT_EQ(std::get<T>(matches.at(matchName)), expectedValue);
            }
        }
    }
}
}  // namespace

struct TestGetMatchesParams
{
    const std::string inputTemplate{};
    const std::string inputString{};
    const std::map<std::string, std::string> expectedStringMatches{};
    const std::map<std::string, uint64_t> expectedIntegerMatches{};
};

class TestGetMatches : public ::testing::TestWithParam<TestGetMatchesParams>
{};

TEST(ValidatePatternTest, ValidPattern)
{
    const std::string inputTemplate{
            R"(^(?<VendorName>.+)_(?<ProductType>.+)_(?<SerialNumber>\d{6})_(?<Date>\d{8})_(?<Time>\d{6})$)"};
    EXPECT_TRUE(namedRegex::NamedRegex::validateInputPattern(inputTemplate));
}

TEST(ValidatePatternTest, ValidPatternMixedNamedAndRegularGroups)
{
    const std::string inputTemplate{R"(^MixedNamedAndRegularGroups_Named_(?<ProductType>.+)_Regular_(.*)!$)"};
    EXPECT_TRUE(namedRegex::NamedRegex::validateInputPattern(inputTemplate));
}

TEST(ValidatePatternTest, InvalidPatternNoCatchGroup)
{
    const std::string inputTemplate{R"(^ThereIsNoNamedRegexPatterns!$)"};
    EXPECT_FALSE(namedRegex::NamedRegex::validateInputPattern(inputTemplate));
}

TEST(ValidatePatternTest, InvalidPatternWithCatchGroup)
{
    const std::string inputTemplate{R"(^ThereIsNoNamedRegexPatterns_(.+)!$)"};
    EXPECT_FALSE(namedRegex::NamedRegex::validateInputPattern(inputTemplate));
}

TEST(ValidatePatternTest, InvalidNameFormat)
{
    const std::string inputTemplate{R"(^.+(?:ProductType|.+).+$)"};
    EXPECT_FALSE(namedRegex::NamedRegex::validateInputPattern(inputTemplate));
}

TEST(ValidatePatternTest, InvalidNoCapturingGroup)
{
    const std::string inputTemplate{R"(^(?'ProductType'.+)!$)"};
    EXPECT_FALSE(namedRegex::NamedRegex::validateInputPattern(inputTemplate));
}

TEST_P(TestGetMatches, NamedRegexGetMatchedTesting)
{
    const auto [inputTemplate, inputString, expectedStringMatches, expectedIntegerMatches] = GetParam();

    EXPECT_TRUE(namedRegex::NamedRegex::validateInputPattern(inputTemplate));
    namedRegex::NamedRegex namedRegex{inputTemplate};
    const auto &matches = namedRegex.getMatches(inputString);

    EXPECT_EQ(matches.size(), expectedStringMatches.size() + expectedIntegerMatches.size());
    checkValues(expectedStringMatches, matches);
    checkValues(expectedIntegerMatches, matches);
}

INSTANTIATE_TEST_CASE_P(
        TestNamedRegex,
        TestGetMatches,
        ::testing::Values(
                TestGetMatchesParams{.inputTemplate = R"(^(?<VendorName>.+)_(?<ProductType>.+)$)",
                                     .inputString = "Samsung_GalaxyS24",
                                     .expectedStringMatches = {{"VendorName", "Samsung"}, {"ProductType", "GalaxyS24"}},
                                     .expectedIntegerMatches = {}},
                TestGetMatchesParams{
                        .inputTemplate = R"(^(?<SerialNumber>\d{6})_(?<Date>\d{8})_(?<Time>\d{6})$)",
                        .inputString = "765132_20250403_163412",
                        .expectedStringMatches = {},
                        .expectedIntegerMatches = {{"SerialNumber", 765132}, {"Date", 20250403}, {"Time", 163412}}},
                TestGetMatchesParams{
                        .inputTemplate =
                                R"(^(?<VendorName>.+)_(?<ProductType>.+)_(?<SerialNumber>\d{6})_(?<Date>\d{8})_(?<Time>\d{6})$)",
                        .inputString = "Samsung_GalaxyS24_765132_20250403_163412",
                        .expectedStringMatches = {{"VendorName", "Samsung"}, {"ProductType", "GalaxyS24"}},
                        .expectedIntegerMatches = {{"SerialNumber", 765132}, {"Date", 20250403}, {"Time", 163412}}},
                TestGetMatchesParams{.inputTemplate = R"(^(?<VendorName>.+)_(?<SerialNumber>\d{6})$)",
                                     .inputString = "Samsung_765132",
                                     .expectedStringMatches = {{"VendorName", "Samsung"}},
                                     .expectedIntegerMatches = {{"SerialNumber", 765132}}}));

}  // namespace namedRegex