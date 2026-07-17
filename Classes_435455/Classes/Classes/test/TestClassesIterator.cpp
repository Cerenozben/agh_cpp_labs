
#include <Classes/FiguresIterator.h>
#include <gtest/gtest.h>

#include <algorithm>

TEST(TestIterator, TestIterator)
{
    classes::FiguresIterator figuresIterator{};
    figuresIterator.addFigure(new classes::Square(1.0), "First square");              // NOLINT
    figuresIterator.addFigure(new classes::Square(2.0), "First square");              // NOLINT
    figuresIterator.addFigure(new classes::Square(3.0), "Third square");              // NOLINT
    figuresIterator.addFigure(new classes::Rectangle(1.0, 2.0), "First rectangle");   // NOLINT
    figuresIterator.addFigure(new classes::Rectangle(2.0, 3.0), "Second rectangle");  // NOLINT

    double areaSum = 0.0;
    for (const auto &[fig, desc] : figuresIterator)
    {
        std::cout << desc << " area is: " << fig->area() << '\n';
        areaSum += fig->area();
    }
    EXPECT_EQ(areaSum, 22.0);

    auto numberOfSquares = std::count_if(
            figuresIterator.begin(), figuresIterator.end(), [](const classes::FigureWithDescription &figWithDesc) {
                return figWithDesc.first->type() == classes::FigureType::SQUARE;
            });

    EXPECT_EQ(numberOfSquares, 3);
}
