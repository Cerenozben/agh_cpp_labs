
#include <Structures/Dictionary.h>
#include <gtest/gtest.h>

TEST(TestDictionary, TestConcatenation)
{
    using dictionary::Dictionary;
    const Dictionary d{{"stringKey", "stringValue"}, {"intKey", 1}, {"floatKey", 2.0F}};
    EXPECT_EQ(d.toJson(), "{\"floatKey\":2.000000,\"intKey\":1,\"stringKey\":\"stringValue\"}");
    Dictionary d2{{"stringKey", "stringValue"}, {"intKey", 1}, {"stringKey2", "stringValue1"}, {"floatKey", 2.0F}};
    EXPECT_EQ(d2.toJson(),
              "{\"floatKey\":2.000000,\"intKey\":1,\"stringKey\":\"stringValue\",\"stringKey2\":\"stringValue1\"}");
}
