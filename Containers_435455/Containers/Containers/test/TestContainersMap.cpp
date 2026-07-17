
#include <Containers/ContainerMap.h>
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

TEST(TestContainerMap, mapSize)
{
    EXPECT_EQ(demangle(typeid(containersMap::mapSize).name()),
              "unsigned long (std::map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, int, "
              "std::less<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, "
              "std::allocator<std::pair<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const, "
              "int> > > const&)");
    EXPECT_EQ(containersMap::mapSize(std::map<std::string, int>{}), 0);
    EXPECT_EQ(containersMap::mapSize(std::map<std::string, int>{std::make_pair("X", 1), std::make_pair("Y", 2)}), 2);
}

TEST(TestContainerMap, mapClear)
{
    EXPECT_EQ(demangle(typeid(containersMap::mapClear<std::string, int>).name()),
              "void (std::map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, int, "
              "std::less<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, "
              "std::allocator<std::pair<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const, "
              "int> > >&)");
    std::map<std::string, float> mapOfFloats{std::make_pair("X", 4), std::make_pair("Y", 3)};
    std::map<float, float> mapOfInts{std::make_pair(2.0, 4)};
    containersMap::mapClear(mapOfFloats);
    containersMap::mapClear(mapOfInts);
    EXPECT_EQ(mapOfFloats.size(), 0);
    EXPECT_EQ(mapOfInts.size(), 0);
}

TEST(TestContainerMap, mapAdd)
{
    EXPECT_EQ(demangle(typeid(containersMap::mapAdd<std::string, int>).name()),
              "void (std::map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, int, "
              "std::less<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, "
              "std::allocator<std::pair<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const, "
              "int> > >&, std::pair<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, int>)");
    std::map<std::string, float> mapOfFloats{std::make_pair("X", 4), std::make_pair("Y", 3)};
    containersMap::mapAdd(mapOfFloats, std::make_pair(std::string("Z"), static_cast<float>(2.0)));
    EXPECT_EQ(mapOfFloats.size(), 3);
    EXPECT_EQ(mapOfFloats,
              (std::map<std::string, float>{std::make_pair("X", 4), std::make_pair("Y", 3), std::make_pair("Z", 2)}));
}

TEST(TestContainerMap, mapGet)
{
    EXPECT_EQ(demangle(typeid(containersMap::mapGet<std::string, int>).name()),
              "int (std::map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, int, "
              "std::less<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, "
              "std::allocator<std::pair<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const, "
              "int> > >&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)");
    std::map<std::string, float> mapOfFloats{std::make_pair("X", 4), std::make_pair("Y", 3)};
    EXPECT_EQ(containersMap::mapGet(mapOfFloats, std::string("X")), static_cast<float>(4.0));
    EXPECT_EQ(containersMap::mapGet(mapOfFloats, std::string("Y")), static_cast<float>(3.0));
}

TEST(TestContainerMap, mapReplace)
{
    std::map<std::string, float> mapOfFloats{std::make_pair("X", 4), std::make_pair("Y", 3)};
    containersMap::mapReplace(mapOfFloats, std::string("X"), static_cast<float>(5.0));
    EXPECT_EQ(containersMap::mapGet(mapOfFloats, std::string("X")), static_cast<float>(5.0));
    EXPECT_EQ(containersMap::mapGet(mapOfFloats, std::string("Y")), static_cast<float>(3.0));
}

TEST(TestContainerMap, mapMerge)
{
    std::map<int, double> m1{std::make_pair(4, 8.0), std::make_pair(3, 6.0)};
    std::map<int, double> m2{std::make_pair(2, 4.0), std::make_pair(1, 2.0)};
    std::map<int, double> m3{std::make_pair(4, 8.5), std::make_pair(5, 10.0)};
    EXPECT_EQ(containersMap::mapMerge(m1, m2),
              (std::map<int, double>{
                      std::make_pair(1, 2.0), std::make_pair(2, 4.0), std::make_pair(3, 6.0), std::make_pair(4, 8.0)}));
    EXPECT_EQ(containersMap::mapMerge(m1, m3),
              (std::map<int, double>{std::make_pair(3, 6.0), std::make_pair(4, 8.5), std::make_pair(5, 10.0)}));
}