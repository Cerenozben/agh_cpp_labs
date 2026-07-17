#include <Functions/Reference.h>
#include <cxxabi.h>
#include <gtest/gtest.h>

#include <cstdlib>
#include <memory>

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

// Exercise - toLowerCase
TEST(TestReference, toLowerCase)
{
    std::string str = "CREAM";
    reference::toLowerCase(str);
    EXPECT_EQ(str, "cream");
    str = "MUffINS";
    reference::toLowerCase(str);
    EXPECT_EQ(str, "muffins");
}

// Exercise - Swap
TEST(TestReference, swapValues)
{
    EXPECT_EQ(demangle(typeid(reference::swapValues).name()), "void (int&, int&)");
    auto val1 = 1;
    auto val2 = 10;
    reference::swapValues(val1, val2);
    EXPECT_EQ(val2, 1);
    EXPECT_EQ(val1, 10);
}

// Exercise - increment
TEST(TestReference, increment)
{
    EXPECT_EQ(demangle(typeid(reference::increment).name()), "int (int const&)");
    int value{3};
    EXPECT_EQ(reference::increment(value), 4);
    EXPECT_EQ(value, 3);
}

// Exercise - sortVector
TEST(TestReference, sortVector)
{
    EXPECT_EQ(demangle(typeid(reference::sortVector).name()), "void (std::vector<int, std::allocator<int> >&)");
    std::vector<int> values{3, 34523, 12343, 25};
    std::vector<int> retVal{3, 25, 12343, 34523};
    reference::sortVector(values);
    EXPECT_EQ(values, retVal);
}
