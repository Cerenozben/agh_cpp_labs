
#include <Basics/FlowControl.h>
#include <gtest/gtest.h>

TEST(TestFlowControl, ifExercise1)
{
    {
        testing::internal::CaptureStdout();
        basics::ifExercise1(101);
        EXPECT_EQ(testing::internal::GetCapturedStdout(), "101");

        testing::internal::CaptureStdout();
        basics::ifExercise1(10);
        EXPECT_EQ(testing::internal::GetCapturedStdout(), "");
    }
}

TEST(TestFlowControl, ifElseExercise1)
{
    EXPECT_EQ(basics::ifElseExercise1(101), true);
    EXPECT_EQ(basics::ifElseExercise1(100), false);
    EXPECT_EQ(basics::ifElseExercise1(10), false);
}

TEST(TestFlowControl, ifElseIfElseExercise1)
{
    EXPECT_EQ(basics::ifElseIfElseExercise1(100), 1);
    EXPECT_EQ(basics::ifElseIfElseExercise1(-100), -1);
    EXPECT_EQ(basics::ifElseIfElseExercise1(0), 0);
}

TEST(TestFlowControl, switchCaseExercise1)
{
    EXPECT_EQ(basics::switchCaseExercise1(2.0, '*', 5.0), 10.0);
    EXPECT_EQ(basics::switchCaseExercise1(2.0, '-', 5.0), -3.0);
    EXPECT_EQ(basics::switchCaseExercise1(2.0, '+', 5.0), 7.0);
    EXPECT_EQ(basics::switchCaseExercise1(2.0, '/', 4.0), 0.5);
    EXPECT_EQ(basics::switchCaseExercise1(2.0, '?', 4.0), 0.0);
}

TEST(TestFlowControl, ternaryOperatorExercise1)
{
    EXPECT_EQ(basics::ternaryOperatorExercise1(0), 1);
    EXPECT_EQ(basics::ternaryOperatorExercise1(1), -1);
    EXPECT_EQ(basics::ternaryOperatorExercise1(2), 1);
    EXPECT_EQ(basics::ternaryOperatorExercise1(3), -1);
}