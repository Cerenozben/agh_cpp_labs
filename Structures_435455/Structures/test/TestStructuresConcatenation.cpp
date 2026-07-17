
#include <Structures/Dictionary.h>
#include <gtest/gtest.h>

TEST(TestDictionary, TestConcatenation)
{
    using dictionary::Dictionary;
    Dictionary d1{{"s", "s"}};
    const Dictionary d2{{"a", "a"}};
    Dictionary d3 = d1 + d2;
    EXPECT_EQ(std::get<std::string>(d1["s"]), "s");
    EXPECT_EQ(std::get<std::string>(d2["a"]), "a");
    EXPECT_EQ(std::get<std::string>(d3["s"]), "s");
    EXPECT_EQ(std::get<std::string>(d3["a"]), "a");
    d1 += d2;
    EXPECT_EQ(std::get<std::string>(d1["s"]), "s");
    EXPECT_EQ(std::get<std::string>(d1["a"]), "a");
}
