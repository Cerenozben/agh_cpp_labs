
#include <Structures/Dictionary.h>
#include <gtest/gtest.h>

TEST(TestDictionary, TestKeys)
{
    dictionary::Dictionary d{{"stringKey", "stringValue"}, {"intKey", 1}, {"floatKey", 2.0F}};

    auto v = d.keys();

    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], "floatKey");
    EXPECT_EQ(v[1], "intKey");
    EXPECT_EQ(v[2], "stringKey");
}
