
#include <Classes/Figure.h>
#include <gtest/gtest.h>

TEST(TestInheritance, TestInheritance)
{
    // NOLINTBEGIN
    EXPECT_EQ((std::is_base_of<classes::Figure, classes::Square>::value), true);
    EXPECT_EQ((std::is_base_of<classes::Figure, classes::Rectangle>::value), true);
    EXPECT_EQ((std::is_base_of<classes::Figure, classes::Triangle>::value), true);

    std::vector<classes::Figure *> figures{};
    figures.push_back(new classes::Square(2.0));
    figures.push_back(new classes::Rectangle(2.0, 3.0));
    figures.push_back(new classes::Triangle(1.0, 4.0));
    // NOLINTEND
    double areaSum{0.0};
    for (const auto &figure : figures)
    {
        areaSum += figure->area();
    }

    EXPECT_EQ(areaSum, 12.0);
}
