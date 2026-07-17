
#include <Structures/Dictionary.h>
#include <gtest/gtest.h>

TEST(TestDictionary, TestValues)
{
    dictionary::Dictionary d{{"stringKey", "stringValue"}, {"intKey", 1}, {"floatKey", 2.0F}};

    auto v = d.values();

    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(std::get<float>(v[0]), 2.0F);
    EXPECT_EQ(std::get<int>(v[1]), 1);
    EXPECT_EQ(std::get<std::string>(v[2]), "stringValue");
}
