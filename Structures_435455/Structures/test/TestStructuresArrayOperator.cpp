
#include <Structures/Dictionary.h>
#include <gtest/gtest.h>

namespace
{

}  // namespace
TEST(TestDictionary, TestArrayOperator)
{
    dictionary::Dictionary d{{"stringKey", "stringValue"}, {"intKey", 1}, {"floatKey", 2.0F}};

    EXPECT_EQ(std::get<std::string>(d["stringKey"]), "stringValue");
    EXPECT_EQ(std::get<int>(d["intKey"]), 1);
    EXPECT_EQ(std::get<float>(d["floatKey"]), 2.0F);

    d["newKey"] = "newValue";
    d["intKey"] = 2;
    d["floatKey"] = 40.0F;

    EXPECT_EQ(std::get<std::string>(d["newKey"]), "newValue");
    EXPECT_EQ(std::get<int>(d["intKey"]), 2);
    EXPECT_EQ(std::get<float>(d["floatKey"]), 40.0F);
}
