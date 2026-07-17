#include <Functions/Recursion.h>
#include <gtest/gtest.h>

// Exercise - gcd
TEST(TestRecursion, gcd)
{
    EXPECT_EQ(recursion::gcd(0, 0), 0);
    EXPECT_EQ(recursion::gcd(1, 1), 1);
    EXPECT_EQ(recursion::gcd(2, 2), 2);
    EXPECT_EQ(recursion::gcd(5, 2), 1);
    EXPECT_EQ(recursion::gcd(5, 10), 5);
    EXPECT_EQ(recursion::gcd(10, 5), 5);
    EXPECT_EQ(recursion::gcd(17, 28), 1);
    EXPECT_EQ(recursion::gcd(102, 153), 51);
}

// Exercise - power
TEST(TestRecursion, power)
{
    EXPECT_EQ(recursion::power(1, 0), 1);
    EXPECT_EQ(recursion::power(1, 1), 1);
    EXPECT_EQ(recursion::power(1, 2), 1);
    EXPECT_EQ(recursion::power(2, 0), 1);
    EXPECT_EQ(recursion::power(2, 1), 2);
    EXPECT_EQ(recursion::power(2, 4), 16);
    EXPECT_EQ(recursion::power(5, 2), 25);
    EXPECT_EQ(recursion::power(10, 5), 100000);
}

// Exercise - Factorial
TEST(TestRecursion, findFactorial)
{
    EXPECT_EQ(recursion::findFactorial(1), 1);
    EXPECT_EQ(recursion::findFactorial(2), 2);
    EXPECT_EQ(recursion::findFactorial(3), 6);
    EXPECT_EQ(recursion::findFactorial(4), 24);
    EXPECT_EQ(recursion::findFactorial(5), 120);
    EXPECT_EQ(recursion::findFactorial(6), 720);
}
