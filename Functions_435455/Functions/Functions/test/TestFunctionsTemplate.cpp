#include <gtest/gtest.h>

#include <Functions/Template.hpp>

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

// // Exercise - templateMax
TEST(TestTemplateFunctions, templateMax)
{
    struct TestStruct
    {
        int v{};
        bool operator==(const TestStruct &rhs) const { return v == rhs.v; }
        bool operator>(const TestStruct &rhs) const { return v > rhs.v; }
        bool operator<(const TestStruct &rhs) const { return rhs.v > v; }
    };

    EXPECT_EQ(demangle(typeid(templateFunctions::max<int>).name()), "int (int, int)");
    EXPECT_EQ(demangle(typeid(templateFunctions::max<float>).name()), "float (float, float)");

    EXPECT_EQ(templateFunctions::max(double{1.0}, double{10.0}), double{10.0});
    EXPECT_EQ(templateFunctions::max(double{1.0}, double{10.0}), double{10.0});
    EXPECT_EQ(templateFunctions::max(float{1.0}, float{10.0}), float{10.0});
    EXPECT_EQ(templateFunctions::max(TestStruct{1}, TestStruct{10}), TestStruct{10});
}

// // Exercise - templateSortVector
TEST(TestTemplateFunctions, templateSortVector)
{
    struct TestStruct
    {
        int v{};
        bool operator==(const TestStruct &rhs) const { return v == rhs.v; }
        bool operator>(const TestStruct &rhs) const { return v > rhs.v; }
        bool operator<(const TestStruct &rhs) const { return rhs.v > v; }
    };

    EXPECT_EQ(demangle(typeid(templateFunctions::templateSortVector<int>).name()),
              "void (std::vector<int, std::allocator<int> >&)");
    EXPECT_EQ(demangle(typeid(templateFunctions::templateSortVector<float>).name()),
              "void (std::vector<float, std::allocator<float> >&)");

    {
        std::vector<int> values{3, 34523, 12343, 25};
        std::vector<int> retVal{3, 25, 12343, 34523};
        templateFunctions::templateSortVector(values);
        EXPECT_EQ(values, retVal);
    }
    {
        std::vector<TestStruct> values{{3}, {34523}, {12343}, {25}};
        std::vector<TestStruct> retVal{{3}, {25}, {12343}, {34523}};
        templateFunctions::templateSortVector(values);
        EXPECT_EQ(values, retVal);
    }
    {
        std::vector<float> values{3.0F, 34523.0F, 12343.0F, 25.0F};
        std::vector<float> retVal{3.0F, 25.0F, 12343.0F, 34523.0F};
        templateFunctions::templateSortVector(values);
        EXPECT_EQ(values, retVal);
    }
}
