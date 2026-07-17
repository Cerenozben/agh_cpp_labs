
#include <Classes/Figure.h>
#include <Classes/PrimitiveFactory.h>
#include <gtest/gtest.h>

namespace
{
std::string demangle(const char *name);
std::string demangle(const char *name)
{
    int status = -4;
    std::unique_ptr<char, void (*)(void *)> res{abi::__cxa_demangle(name, nullptr, nullptr, &status), std::free};
    return (status == 0) ? res.get() : name;
}
}  // namespace

TEST(TestPrimitiveFactory, TestPrimitiveFactory)
{
    classes::PrimitiveFactory figuresPrimitiveFactory{};
    EXPECT_EQ(demangle(typeid(figuresPrimitiveFactory.createFigure(classes::FigureType::RECTANGLE)).name()),
              "classes::Figure*");
    EXPECT_EQ(demangle(typeid(figuresPrimitiveFactory.createFigure(classes::FigureType::RECTANGLE, 0.0)).name()),
              "classes::Figure*");
    EXPECT_EQ(demangle(typeid(figuresPrimitiveFactory.createFigure(classes::FigureType::RECTANGLE, 0.0, 1.0)).name()),
              "classes::Figure*");

    std::vector<classes::Figure *> figures{};
    figures.push_back(figuresPrimitiveFactory.createFigure(classes::FigureType::SQUARE, 2.0));
    figures.push_back(figuresPrimitiveFactory.createFigure(classes::FigureType::RECTANGLE, 2.0, 3.0));
    figures.push_back(figuresPrimitiveFactory.createFigure(classes::FigureType::TRIANGLE, 1.0, 4.0));

    double areaSum{0.0};
    for (const auto &figure : figures)
    {
        areaSum += figure->area();
    }
    EXPECT_EQ(areaSum, 12.0);

    EXPECT_EQ(figuresPrimitiveFactory.createFigure(classes::FigureType::UNKNOWN), nullptr);
}
