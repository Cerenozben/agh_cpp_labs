
#include <gtest/gtest.h>

#include <Structures/VariantVisitors.hpp>

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

TEST(TestVariantVisitors, ToStringVisitor)
{
    using variantVisitors::ToStringVariant;
    using variantVisitors::ToStringVisitor;
    EXPECT_EQ(demangle(typeid(ToStringVariant).name()), "std::variant<bool, int, double, float>");
    {
        ToStringVariant v{true};
        EXPECT_EQ(std::visit(ToStringVisitor{}, v), "true");
    }
    {
        ToStringVariant v{255};
        EXPECT_EQ(std::visit(ToStringVisitor{}, v), "ff");
    }
    {
        ToStringVariant v{1.0F};
        EXPECT_EQ(std::visit(ToStringVisitor{}, v), "1");
    }
    {
        ToStringVariant v{1.0};
        EXPECT_EQ(std::visit(ToStringVisitor{}, v), "1");
    }
}
