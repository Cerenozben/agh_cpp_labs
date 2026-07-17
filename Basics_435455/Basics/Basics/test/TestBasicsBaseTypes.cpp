
#include <Basics/BaseTypes.h>
#include <gtest/gtest.h>

TEST(TestBaseTypes, boolExercise1)
{
    EXPECT_EQ(basics::boolExercise1(true, true), true);
    EXPECT_EQ(basics::boolExercise1(true, false), false);
    EXPECT_EQ(basics::boolExercise1(false, true), false);
    EXPECT_EQ(basics::boolExercise1(false, false), false);
}

TEST(TestBaseTypes, boolExercise2)
{
    EXPECT_EQ(basics::boolExercise2(true, true), false);
    EXPECT_EQ(basics::boolExercise2(true, false), true);
    EXPECT_EQ(basics::boolExercise2(false, true), true);
    EXPECT_EQ(basics::boolExercise2(false, false), false);
}

TEST(TestBaseTypes, boolExercise3)
{
    EXPECT_EQ(basics::boolExercise3(true, true), true);
    EXPECT_EQ(basics::boolExercise3(true, false), true);
    EXPECT_EQ(basics::boolExercise3(false, true), true);
    EXPECT_EQ(basics::boolExercise3(false, false), false);
}

TEST(TestBaseTypes, boolExercise4)
{
    EXPECT_EQ(basics::boolExercise4(true), false);
    EXPECT_EQ(basics::boolExercise4(false), true);
}

TEST(TestBaseTypes, shortExercise1)
{
    EXPECT_EQ(basics::shortExercise1(5), 6);
    EXPECT_EQ(basics::shortExercise1(1), 2);
}

TEST(TestBaseTypes, intExercise1)
{
    testing::internal::CaptureStdout();
    basics::intExercise1(101);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "101");

    testing::internal::CaptureStdout();
    basics::intExercise1(10);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "10");
}

TEST(TestBaseTypes, intExercise2)
{
    EXPECT_EQ(basics::intExercise2(10), true);
    EXPECT_EQ(basics::intExercise2(2), false);
    EXPECT_EQ(basics::intExercise2(11), true);
}

TEST(TestBaseTypes, uintExercise1)
{
    EXPECT_EQ(basics::uintExercise1(10, 10), 20);
    EXPECT_EQ(basics::uintExercise1(2, 3), 5);
}

TEST(TestBaseTypes, uintExercise2)
{
    EXPECT_EQ(basics::uintExercise2(10, 20), 10);
    EXPECT_EQ(basics::uintExercise2(2, 3), 2);
}

TEST(TestBaseTypes, floatExercise1)
{
    EXPECT_EQ(basics::floatExercise1(2.0, 2.0), 4.0);
    EXPECT_EQ(basics::floatExercise1(2.5, 2.5), 6.25);
}

TEST(TestBaseTypes, doubleExercise1)
{
    EXPECT_EQ(basics::doubleExercise1(-10.0, 8.0), 10.0);
    EXPECT_EQ(basics::doubleExercise1(-100.0, 200.0), 200);
}

TEST(TestBaseTypes, doubleExercise2)
{
    EXPECT_EQ(basics::doubleExercise2(2.0, 3.0, 5.0), true);
    EXPECT_EQ(basics::doubleExercise2(2.0, 3.0, 6.0), false);
    EXPECT_EQ(basics::doubleExercise2(0.1, 0.2, 0.3), true);
    EXPECT_EQ(basics::doubleExercise2(0.3 * 3, 0.1, 1.0), true);
}