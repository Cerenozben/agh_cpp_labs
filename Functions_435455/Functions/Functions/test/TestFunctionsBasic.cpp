#include <Functions/Basic.h>
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

// // Exercise - convert2Ascii
TEST(TestBasic, convert2Ascii)
{
    EXPECT_EQ(demangle(typeid(basics::convert2Ascii).name()), "unsigned int (char)");

    EXPECT_EQ(basics::convert2Ascii(' '), 32);
    EXPECT_EQ(basics::convert2Ascii('.'), 46);
    EXPECT_EQ(basics::convert2Ascii('/'), 47);
    EXPECT_EQ(basics::convert2Ascii('A'), 65);
    EXPECT_EQ(basics::convert2Ascii('a'), 97);
    EXPECT_EQ(basics::convert2Ascii(';'), 59);
    EXPECT_EQ(basics::convert2Ascii('_'), 95);
}

// // Exercise - HexPrint
TEST(TestBasic, hexPrint)
{
    testing::internal::CaptureStdout();
    basics::hexPrint("start");
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "73 74 61 72 74 ");

    testing::internal::CaptureStdout();
    basics::hexPrint("1qwdvfgu^&%$#");
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "31 71 77 64 76 66 67 75 5e 26 25 24 23 ");
}

// // Exercise - defaultValues
TEST(TestBasic, defaultValues)
{
    testing::internal::CaptureStdout();
    basics::defaultValues("start");
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "start\nempty row number 1\nempty row number 2\nempty row number 3\n");

    testing::internal::CaptureStdout();
    basics::defaultValues("zero", "one");
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "zero\none\nempty row number 2\nempty row number 3\n");

    testing::internal::CaptureStdout();
    basics::defaultValues("zero", "one", "two");
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "zero\none\ntwo\nempty row number 3\n");

    testing::internal::CaptureStdout();
    basics::defaultValues("zero", "one", "two", "3");
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "zero\none\ntwo\n3\n");
}

// // Exercise - min
TEST(TestBasic, min)
{
    EXPECT_EQ(demangle(typeid(basics::min).name()), "float (float, float)");
    EXPECT_EQ(basics::min(float{1.0}, float{10.0}), float{1.0});
    EXPECT_EQ(basics::min(float{12.0}, float{10.0}), float{10.0});
}
