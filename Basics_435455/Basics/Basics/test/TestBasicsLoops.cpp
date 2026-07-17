
#include <Basics/Loops.h>
#include <gtest/gtest.h>

#include <bit>
#include <cstdint>

TEST(TestLoops, forExercise1)
{
    EXPECT_EQ(basics::forExercise1(), 625);
}

TEST(TestLoops, forExercise2)
{
    const auto arr = std::array<std::pair<std::string, std::string>, 2>{std::make_pair("John", "Smith"),
                                                                        std::make_pair("Jack", "Sparrow")};
    EXPECT_EQ(basics::forExercise2(std::array<std::string, 2>{arr[0].first, arr[1].first},
                                   std::array<std::string, 2>{arr[0].second, arr[1].second}),
              arr);
}

TEST(TestLoops, forExercise3)
{
    EXPECT_EQ(basics::forExercise3(1), 1);
    EXPECT_EQ(basics::forExercise3(2), 2);
    EXPECT_EQ(basics::forExercise3(3), 6);
    EXPECT_EQ(basics::forExercise3(4), 24);
    EXPECT_EQ(basics::forExercise3(5), 120);
    EXPECT_EQ(basics::forExercise3(6), 720);
    EXPECT_EQ(basics::forExercise3(7), 5040);
    EXPECT_EQ(basics::forExercise3(8), 40320);
    EXPECT_EQ(basics::forExercise3(9), 362880);
    EXPECT_EQ(basics::forExercise3(10), 3628800);
}

TEST(TestLoops, forExercise4)
{
    for (const uint8_t value : std::array<uint8_t, 5>{0b00001010U, 0b10000000U, 0b00000000U, 0b00000001U, 0b00010000U})
    {
        EXPECT_LE(basics::forExercise4(value), std::countl_zero(value));
    }
}

TEST(TestLoops, whileExercise1)
{
    const auto numbers = std::array<int, 10>{10, 10, 10, 55, 16, 4, 5, 6, 7, 54};
    EXPECT_EQ(basics::whileExercise1(numbers), 5);
}

TEST(TestLoops, whileExercise2)
{
    EXPECT_EQ(basics::whileExercise2(2, 5), 3);
    EXPECT_EQ(basics::whileExercise2(2, 1000), 10);
    EXPECT_EQ(basics::whileExercise2(4, 1000), 5);
    EXPECT_EQ(basics::whileExercise2(7, 45000), 6);
}
