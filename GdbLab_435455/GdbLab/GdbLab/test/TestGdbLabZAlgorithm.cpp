
#include <GdbLab/ZAlgorithm.h>
#include <gtest/gtest.h>

#include <Watchdog.hpp>

namespace gdbLab
{
TEST(ZAlgorithmTest, GEEK)
{
    auto watchdog = std::make_unique<Watchdog>(500);
    std::string text = "GEEKS FOR GEEKS";
    std::string pattern = "GEEK";
    auto ret = search(text, pattern);
    EXPECT_EQ(ret, (std::vector<size_t>{0, 10}));
}

TEST(ZAlgorithmTest, Random)
{
    auto watchdog = std::make_unique<Watchdog>(500);
    std::string text = "wvtm34mpugt4v0c9yqg0[cuy,4u fg= 34y5]b6=,1tu3y54q4v0c9mj6yq459=uv   4   ` 4 3yq46ikq464v0c92h";
    std::string pattern = "4v0c9";
    auto ret = search(text, pattern);
    EXPECT_EQ(ret, (std::vector<size_t>{11, 49, 86}));
}

}  // namespace gdbLab