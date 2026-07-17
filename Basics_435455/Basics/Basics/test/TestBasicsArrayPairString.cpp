#include <Basics/ArrayPairString.h>
#include <gtest/gtest.h>

TEST(TestArrayPairString, pairExercise1)
{
    EXPECT_EQ(basics::pairExercise1(10.0, true), std::make_pair(10.0, true));
    EXPECT_EQ(basics::pairExercise1(-1.0, false), std::make_pair(-1.0, false));
}

TEST(TestArrayPairString, pairExercise2)
{
    EXPECT_EQ(basics::pairExercise2(1), std::make_pair(true, false));
    EXPECT_EQ(basics::pairExercise2(2), std::make_pair(true, true));
    EXPECT_EQ(basics::pairExercise2(-3), std::make_pair(false, false));
    EXPECT_EQ(basics::pairExercise2(-4), std::make_pair(false, true));
}

TEST(TestArrayPairString, pairExercise3)
{
    EXPECT_EQ(basics::pairExercise3(std::make_pair(10, 5.0)), std::make_pair(5.0, 10));
}

TEST(TestArrayPairString, arrayExercise1)
{
    const auto expValue = std::array<int, 3>{1, 2, 3};
    EXPECT_EQ(basics::arrayExercise1(), expValue);
}

TEST(TestArrayPairString, arrayExercise2)
{
    const auto arr = std::array<int, 3>{4, 7, 11};
    EXPECT_EQ(basics::arrayExercise2(arr), 7);
}

TEST(TestArrayPairString, arrayExercise3)
{
    const auto arr = std::array<int, 3>{4, 7, 11};
    EXPECT_EQ(basics::arrayExercise3(arr), 15);
}

TEST(TestArrayPairString, arrayExercise4)
{
    EXPECT_TRUE(basics::arrayExercise4({0, 1, 2}, {0, 1, 2, 3, 4}));
    EXPECT_TRUE(basics::arrayExercise4({1, 2, 3}, {0, 1, 2, 3, 4}));
    EXPECT_TRUE(basics::arrayExercise4({2, 3, 4}, {0, 1, 2, 3, 4}));
    EXPECT_FALSE(basics::arrayExercise4({1, 3, 4}, {0, 1, 2, 3, 4}));
    EXPECT_FALSE(basics::arrayExercise4({5, 6, 7}, {0, 1, 2, 3, 4}));
    EXPECT_FALSE(basics::arrayExercise4({3, 2, 1}, {0, 1, 2, 3, 4}));
}

TEST(TestArrayPairString, stringExercise1)
{
    EXPECT_EQ(basics::stringExercise1(std::string("Hello")), 5);
}

TEST(TestArrayPairString, stringExercise2)
{
    EXPECT_EQ(basics::stringExercise2(std::string("Hello"), std::string(" world!")), std::string("Hello world!"));
}

TEST(TestArrayPairString, stringExercise3)
{
    EXPECT_EQ(basics::stringExercise3(std::string("  world!")), std::string("Hello world!"));
}

TEST(TestArrayPairString, stringExercise4)
{
    EXPECT_TRUE(basics::stringExercise4("Hello world", "Hello"));
    EXPECT_TRUE(basics::stringExercise4("Hello world", "lo wo"));
    EXPECT_TRUE(basics::stringExercise4("Hello world", "world"));
    EXPECT_TRUE(basics::stringExercise4("Hello world", "Hello world"));
    EXPECT_FALSE(basics::stringExercise4("Hello world", "word"));
    EXPECT_TRUE(basics::stringExercise4("Hello world", ""));
    EXPECT_FALSE(basics::stringExercise4("Hello world", "hello"));
}

TEST(TestArrayPairString, stringExercise5)
{
    EXPECT_EQ(basics::stringExercise5("hello"), "HELLO");
    EXPECT_EQ(basics::stringExercise5("Hello World"), "HELLO WORLD");
    EXPECT_EQ(basics::stringExercise5("123abc"), "123ABC");
    EXPECT_EQ(basics::stringExercise5(""), "");
}

TEST(TestArrayPairString, stringExercise6)
{
    EXPECT_EQ(basics::stringExercise6("hello", 'l'), 2);
    EXPECT_EQ(basics::stringExercise6("hello", 'o'), 1);
    EXPECT_EQ(basics::stringExercise6("hello", 'x'), 0);
    EXPECT_EQ(basics::stringExercise6("", 'a'), 0);
    EXPECT_EQ(basics::stringExercise6("aaaaaa", 'a'), 6);
}

TEST(TestArrayPairString, stringExercise7)
{
    EXPECT_EQ(basics::stringExercise7("Hello world", 0, 5), "Hello");
    EXPECT_EQ(basics::stringExercise7("Hello world", 6, 5), "world");
    EXPECT_EQ(basics::stringExercise7("Hello world", 3, 4), "lo w");
    EXPECT_EQ(basics::stringExercise7("Hello world", 0, 11), "Hello world");
    EXPECT_EQ(basics::stringExercise7("Hello world", 6, 100), "world");
}

TEST(TestArrayPairString, stringExercise8)
{
    EXPECT_TRUE(basics::stringExercise8("Hello world", "Hello"));
    EXPECT_TRUE(basics::stringExercise8("Hello world", "H"));
    EXPECT_TRUE(basics::stringExercise8("Hello world", "Hello world"));
    EXPECT_TRUE(basics::stringExercise8("Hello world", ""));
    EXPECT_FALSE(basics::stringExercise8("Hello world", "world"));
    EXPECT_FALSE(basics::stringExercise8("Hello world", "hello"));
    EXPECT_FALSE(basics::stringExercise8("Hi", "Hello"));
}