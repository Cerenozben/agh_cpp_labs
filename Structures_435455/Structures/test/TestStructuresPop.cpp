
#include <Structures/Dictionary.h>
#include <gtest/gtest.h>

TEST(TestDictionary, TestPop)
{
    dictionary::Dictionary d{{"stringKey", "stringValue"}, {"intKey", 1}, {"floatKey", 2.0F}};

    EXPECT_EQ(std::get<std::string>(d["stringKey"]), "stringValue");
    EXPECT_EQ(std::get<int>(d["intKey"]), 1);
    EXPECT_EQ(std::get<float>(d["floatKey"]), 2.0F);

    d.pop("intKey");

    EXPECT_EQ(d["intKey"], dictionary::CustomVariant{});
    EXPECT_EQ(std::get<float>(d["floatKey"]), 2.0F);
}
