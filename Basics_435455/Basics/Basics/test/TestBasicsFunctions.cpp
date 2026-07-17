#include <Basics/Functions.h>
#include <gtest/gtest.h>

TEST(TestFunctions, mean)
{
    EXPECT_EQ(basics::mean(std::array<double, 3>{1.0, 5.0, 9.0}), 5.0);
    EXPECT_EQ(basics::mean(std::array<double, 3>{-1.0, 2.0, 5.0}), 2.0);
}

TEST(TestFunctions, celsiusToFahrenheit)
{
    EXPECT_EQ(basics::celsiusToFahrenheit(-10.0), 14.0);
    EXPECT_EQ(basics::celsiusToFahrenheit(0.0), 32.0);
    EXPECT_EQ(basics::celsiusToFahrenheit(22.0), 71.6);
    EXPECT_EQ(basics::celsiusToFahrenheit(100.0), 212.0);
}

TEST(TestFunctions, findMax)
{
    EXPECT_EQ(basics::findMax(std::array<double, 3>{1.0, 5.0, 3.0}), 5.0);
    EXPECT_EQ(basics::findMax(std::array<double, 3>{-10.0, -5.0, -20.0}), -5.0);
    EXPECT_EQ(basics::findMax(std::array<double, 3>{7.5, 7.5, 7.5}), 7.5);
}

TEST(TestFunctions, calculateCircleArea)
{
    EXPECT_NEAR(basics::calculateCircleArea(1.0), 3.14159, 0.001);
    EXPECT_NEAR(basics::calculateCircleArea(5.0), 78.53981, 0.001);
    EXPECT_NEAR(basics::calculateCircleArea(0.0), 0.0, 0.001);
}

TEST(TestFunctions, isPalindrome)
{
    EXPECT_TRUE(basics::isPalindrome(121));
    EXPECT_TRUE(basics::isPalindrome(12321));
    EXPECT_TRUE(basics::isPalindrome(1234321));
    EXPECT_TRUE(basics::isPalindrome(1));
    EXPECT_FALSE(basics::isPalindrome(123));
    EXPECT_FALSE(basics::isPalindrome(1234));
}
