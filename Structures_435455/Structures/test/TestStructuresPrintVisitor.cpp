
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

TEST(TestVariantVisitors, PrintVisitor)
{
    using variantVisitors::PrintVariant;
    using variantVisitors::PrintVisitor;
    EXPECT_EQ(demangle(typeid(PrintVariant).name()), "std::variant<bool, int, float>");
    {
        testing::internal::CaptureStdout();
        PrintVariant v{true};
        std::visit(PrintVisitor{}, v);
        EXPECT_EQ(testing::internal::GetCapturedStdout(), "bool");
    }
    {
        testing::internal::CaptureStdout();
        PrintVariant v{1};
        std::visit(PrintVisitor{}, v);
        EXPECT_EQ(testing::internal::GetCapturedStdout(), "int");
    }
    {
        testing::internal::CaptureStdout();
        PrintVariant v{1.0F};
        std::visit(PrintVisitor{}, v);
        EXPECT_EQ(testing::internal::GetCapturedStdout(), "float");
    }
}
