
#include <Classes/Figure.h>
#include <gtest/gtest.h>

class TestFigure : public classes::Figure
{
public:
    TestFigure() = default;
    TestFigure(const TestFigure &) = default;
    TestFigure(TestFigure &&) = delete;
    TestFigure &operator=(const TestFigure &) = default;
    TestFigure &operator=(TestFigure &&) = delete;
    double area() const override { return 0.0; }
    classes::FigureType type() const override { return classes::FigureType::UNKNOWN; }
    ~TestFigure() override = default;
};

TEST(TestInterface, TestInterface)
{
    EXPECT_EQ(std::is_class<classes::Figure>::value, true);

    TestFigure figure{};
    auto *validFigPtr = dynamic_cast<classes::Figure *>(&figure);
    EXPECT_NE(validFigPtr, nullptr);
}
