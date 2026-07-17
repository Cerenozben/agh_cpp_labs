#include <Functions/Overload.h>
#include <gtest/gtest.h>

// // Exercise - add
TEST(TestOverload, add)
{
    EXPECT_EQ(overload::add(1242, 4326, 876), 6444);
    EXPECT_EQ(overload::add(7649, 968), 8617);
}

// // Exercise - roundOverload
TEST(TestOverload, round)
{
    testing::internal::CaptureStdout();
    double dVal{111111.0};
    overload::round(dVal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "111100");
    testing::internal::CaptureStdout();
    float fVal{111111.0};
    overload::round(fVal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "111000");
    testing::internal::CaptureStdout();
    int iVal{111111};
    overload::round(iVal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "110000");
}

// // Exercise - precisionPrint
TEST(TestOverload, precisionPrint)
{
    testing::internal::CaptureStdout();
    float fVal{0.11111111F};
    overload::precisionPrint(fVal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "0.11");

    testing::internal::CaptureStdout();
    double dVal{0.11111111};
    overload::precisionPrint(dVal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "0.1111");

    testing::internal::CaptureStdout();
    long double dlVal{0.11111111L};
    overload::precisionPrint(dlVal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "0.111111");
}

// // Exercise - polynomialPrint
TEST(TestOverload, polynomialPrint)
{
    testing::internal::CaptureStdout();
    overload::polynomialPrint(12.43F);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "f(x) = 12.43");

    testing::internal::CaptureStdout();
    overload::polynomialPrint(12.43F, 2345.34F);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "f(x) = 12.43 + 2345.34*x^1");

    testing::internal::CaptureStdout();
    overload::polynomialPrint(12424.44F, 23.235F, 7667.76F);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "f(x) = 12424.4 + 23.235*x^1 + 7667.76*x^2");
}
