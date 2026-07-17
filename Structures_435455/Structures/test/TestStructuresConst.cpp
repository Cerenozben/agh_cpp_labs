
#include <Structures/Dictionary.h>
#include <gtest/gtest.h>

TEST(TestDictionary, TestConst)
{
    using dictionary::Dictionary;
    const Dictionary d{{"s", "s"}};
    auto ret = d["s"];
    d.keys();
    d.values();
    EXPECT_EQ(std::get<std::string>(d["s"]), "s");
}
