
#include <Structures/Dictionary.h>
#include <gtest/gtest.h>

TEST(TestDictionary, TestObjectsCounter)
{
    using dictionary::Dictionary;
    Dictionary d;
    EXPECT_EQ(Dictionary::getObjCounter(), 1);
    Dictionary d2{{"s", "s"}};
    EXPECT_EQ(Dictionary::getObjCounter(), 2);
    Dictionary d3 = d2;  // NOLINT
    EXPECT_EQ(Dictionary::getObjCounter(), 3);
    {
        Dictionary d4;
        EXPECT_EQ(Dictionary::getObjCounter(), 4);
    }
    EXPECT_EQ(Dictionary::getObjCounter(), 3);
    Dictionary d5(std::move(d));
    EXPECT_EQ(Dictionary::getObjCounter(), 4);
}
