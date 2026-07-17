
#include <Containers/ContainerSet.h>
#include <gtest/gtest.h>

#include <cmath>

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
    bool operator<(const Point &rhs) const
    {
        return std::pow(std::pow(x, 2) + std::pow(y, 2), 0.5) < std::pow(std::pow(rhs.x, 2) + std::pow(rhs.y, 2), 0.5);
    }
};

TEST(TestContainerSet, setSize)
{
    EXPECT_EQ(demangle(typeid(containersSet::setSize).name()),
              "unsigned long (std::set<int, std::less<int>, std::allocator<int> > const&)");
    EXPECT_EQ(containersSet::setSize(std::set<int>{}), 0);
    EXPECT_EQ(containersSet::setSize(std::set<int>{1, 2, 2}), 2);
}

TEST(TestContainerSet, setClear)
{
    EXPECT_EQ(demangle(typeid(containersSet::setClear<int>).name()),
              "void (std::set<int, std::less<int>, std::allocator<int> >&)");
    const auto p1 = Point{.x = 0.0, .y = 1.0};
    const auto p2 = Point{.x = 1.0, .y = 1.0};
    std::set<Point> setOfPoints{p1, p2};
    std::set<int> setOfInts{1, 2, 3, 4};
    containersSet::setClear(setOfPoints);
    containersSet::setClear(setOfInts);
    EXPECT_EQ(setOfPoints.size(), 0);
    EXPECT_EQ(setOfInts.size(), 0);
}

TEST(TestContainerSet, setAdd)
{
    EXPECT_EQ(demangle(typeid(containersSet::setAdd<int>).name()),
              "void (std::set<int, std::less<int>, std::allocator<int> >&, int)");
    const auto p1 = Point{.x = 0.0, .y = 1.0};
    const auto p2 = Point{.x = 1.0, .y = 1.0};
    const auto p3 = Point{.x = 1.0, .y = 1.0};
    const auto p4 = Point{.x = 2.0, .y = 1.0};
    std::set<Point> setOfPoints{p1, p2};
    containersSet::setAdd(setOfPoints, p3);
    EXPECT_EQ(setOfPoints, (std::set<Point>{p1, p2}));
    containersSet::setAdd(setOfPoints, p4);
    EXPECT_EQ(setOfPoints, (std::set<Point>{p1, p2, p4}));
}

TEST(TestContainerSet, setSwap)
{
    EXPECT_EQ(demangle(typeid(containersSet::setSwap<int>).name()),
              "void (std::set<int, std::less<int>, std::allocator<int> >&, std::set<int, std::less<int>, std::allocator<int> "
              ">&)");
    std::set<int> s1{1, 2};
    std::set<int> s2{3, 4};
    containersSet::setSwap(s1, s2);
    EXPECT_EQ(s1, (std::set<int>{3, 4}));
    EXPECT_EQ(s2, (std::set<int>{1, 2}));
}

TEST(TestContainerSet, toSet)
{
    EXPECT_EQ(demangle(typeid(containersSet::toSet<int>).name()),
              "std::set<int, std::less<int>, std::allocator<int> > (std::vector<int, std::allocator<int> > const&)");
    EXPECT_EQ(containersSet::toSet(std::vector<int>{1, 2, 2, 3, 4, 4}), (std::set<int>{1, 2, 3, 4}));
    EXPECT_EQ(containersSet::toSet(std::vector<std::string>{"X", "Y", "Z", "Y", "Z"}), (std::set<std::string>{"X", "Y", "Z"}));
    const auto p1 = Point{.x = 0.0, .y = 1.0};
    const auto p2 = Point{.x = 1.0, .y = 1.0};
    const auto p3 = Point{.x = 1.0, .y = 1.0};
    EXPECT_EQ(containersSet::toSet(std::vector<Point>{p1, p2, p3}), (std::set<Point>{p1, p2}));
}

TEST(TestContainerSet, countSumOfUniqueElements)
{
    EXPECT_EQ(demangle(typeid(containersSet::countSumOfUniqueElements).name()),
              "double (std::vector<double, std::allocator<double> > const&)");
    EXPECT_EQ(containersSet::countSumOfUniqueElements(std::vector<double>{}), 0);
    EXPECT_EQ(containersSet::countSumOfUniqueElements(std::vector<double>{1, 2, 2}), 3);
    EXPECT_EQ(containersSet::countSumOfUniqueElements(std::vector<double>{0.5, 1.0, 1.5, 1.5}), 3.0);
}

TEST(TestContainerSet, set)
{
    EXPECT_EQ(demangle(typeid(containersSet::setIntersection<int>).name()),
              "std::set<int, std::less<int>, std::allocator<int> > (std::set<int, std::less<int>, std::allocator<int> > "
              "const&, std::set<int, std::less<int>, std::allocator<int> > const&)");
    std::set<int> s1{1, 2, 3};
    std::set<int> s2{3, 4};
    std::set<int> s3{3, 4};
    EXPECT_EQ(containersSet::setIntersection(s1, s2), (std::set<int>{3}));
    EXPECT_EQ(containersSet::setIntersection(s2, s3), (std::set<int>{3, 4}));
}
