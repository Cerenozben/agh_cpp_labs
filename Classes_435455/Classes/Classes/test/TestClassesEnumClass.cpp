
#include <Classes/Figure.h>
#include <gtest/gtest.h>

TEST(TestEnumClass, TestEnumClass)
{
    using IsEnum = std::is_enum<classes::FigureType>;
    EXPECT_EQ(IsEnum::value, true);
    EXPECT_EQ(static_cast<uint8_t>(classes::FigureType::SQUARE), static_cast<uint8_t>(0));
    EXPECT_EQ(static_cast<uint8_t>(classes::FigureType::RECTANGLE), static_cast<uint8_t>(1));
    EXPECT_EQ(static_cast<uint8_t>(classes::FigureType::TRIANGLE), static_cast<uint8_t>(2));
    EXPECT_EQ(static_cast<uint8_t>(classes::FigureType::UNKNOWN), static_cast<uint8_t>(255));
}
