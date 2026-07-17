
#include <Containers/ContainerVector.h>
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

struct Point
{
    float x{0.0};
    float y{0.0};
    bool operator==(const Point &rhs) const { return x == rhs.x && y == rhs.y; }
};

TEST(TestContainerVector, vectorSize)
{
    EXPECT_EQ(demangle(typeid(containersVector::vectorSize).name()),
              "unsigned long (std::vector<int, std::allocator<int> > const&)");
    EXPECT_EQ(containersVector::vectorSize(std::vector<int>{}), 0);
    EXPECT_EQ(containersVector::vectorSize(std::vector<int>(100)), 100);
}

TEST(TestContainerVector, createVector)
{
    EXPECT_EQ(demangle(typeid(containersVector::createVector<int>).name()),
              "std::vector<int, std::allocator<int> > (unsigned long, int)");
    EXPECT_EQ(demangle(typeid(containersVector::createVector<float>).name()),
              "std::vector<float, std::allocator<float> > (unsigned long, float)");
    EXPECT_EQ(containersVector::createVector<int>(3, 1), (std::vector<int>{1, 1, 1}));
    EXPECT_EQ(containersVector::createVector<std::string>(2, "X"), (std::vector<std::string>{"X", "X"}));
}

TEST(TestContainerVector, mergeVectors)
{
    EXPECT_EQ(demangle(typeid(containersVector::mergeVectors<int>).name()),
              "std::vector<int, std::allocator<int> > (std::vector<int, std::allocator<int> > const&, std::vector<int, "
              "std::allocator<int> > const&)");

    EXPECT_EQ(containersVector::mergeVectors<int>(std::vector<int>{1, 2}, std::vector<int>{3, 4, 5}),
              (std::vector<int>{1, 2, 3, 4, 5}));
    const auto p1 = Point{.x = 0.0, .y = 1.0};
    const auto p2 = Point{.x = 1.0, .y = 1.0};
    EXPECT_EQ(containersVector::mergeVectors<Point>(std::vector<Point>{p1}, std::vector<Point>{p2}),
              (std::vector<Point>{p1, p2}));
}

TEST(TestContainerVector, vectorReverse)
{
    std::vector<int> v{1, 2, 3};
    containersVector::vectorReverse(v);
    EXPECT_EQ(v, (std::vector<int>{3, 2, 1}));
}

TEST(TestContainerVector, vectorFilter)
{
    std::vector<int> v{1, 2, 3, 4, 5};
    containersVector::vectorFilter(v);
    EXPECT_EQ(v, (std::vector<int>{2, 4}));
}

TEST(TestContainerVector, vectorRemoveThirdElement)
{
    std::vector<int> v{1, 2, 3, 4, 5};
    containersVector::vectorRemoveThirdElement(v);
    EXPECT_EQ(v, (std::vector<int>{1, 2, 4, 5}));
}

TEST(TestContainerVector, vectorInsertAfterThirdElement)
{
    std::vector<int> v{1, 2, 3, 4, 5};
    containersVector::vectorInsertAfterThirdElement(v, 6);
    EXPECT_EQ(v, (std::vector<int>{1, 2, 3, 6, 4, 5}));
}

TEST(TestContainerVector, vectorCountOccurrences)
{
    EXPECT_EQ(containersVector::vectorCountOccurrences(std::vector<int>{1, 2, 3, 6, 2, 5}, 2), 2);
    EXPECT_EQ(containersVector::vectorCountOccurrences(std::vector<std::string>{"X", "XY", "X", "XZ"}, std::string("XY")), 1);
    const auto p1 = Point{.x = 0.0, .y = 1.0};
    const auto p2 = Point{.x = 1.0, .y = 1.0};
    EXPECT_EQ(containersVector::vectorCountOccurrences(std::vector<Point>{p1, p2}, p1), 1);
}

TEST(TestContainerVector, vectorMean)
{
    std::vector<double> v1{1.0, 2.0, 3.0};
    std::vector<double> v2{2.0, 4.0, 6.0};
    EXPECT_EQ(containersVector::vectorMean(std::vector<std::vector<double>>{v1, v2}), 3.0);
}