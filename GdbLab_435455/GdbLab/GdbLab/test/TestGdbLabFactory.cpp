
#include <GdbLab/Factory.h>
#include <gtest/gtest.h>

#include <Watchdog.hpp>

namespace gdbLab
{
TEST(TestFactory, first)
{
    auto watchdog = std::make_unique<Watchdog>(500);
    testing::internal::CaptureStdout();
    Comedy::playFirstAct({1, 2, 3, 4});
    auto consoleOut = testing::internal::GetCapturedStdout();

    EXPECT_EQ(consoleOut,
              "The Three Stooges present: A Day at the Office!\n\nBoss: (angrily) What do you three think you're doing?! Get "
              "to work!\nMoe: slap head\nCurly: suffer abuse\nRandomGuy: is silent\nRandomGuy: is silent\nBoss: (frustrated) "
              "That's it, you're all fired!\nMoe: slap head\nCurly: suffer abuse\nRandomGuy: is silent\nRandomGuy: is "
              "silent\nThe End.\n");
}

TEST(TestFactory, second)
{
    auto watchdog = std::make_unique<Watchdog>(500);
    testing::internal::CaptureStdout();
    Comedy::playSecondAct({1, 2, 4, 3});
    auto consoleOut = testing::internal::GetCapturedStdout();
    EXPECT_EQ(consoleOut,
              "The Three Stooges present:  A Day at the Circus!\n\nMoe: juggling\nCurly: magic trick\nRandomGuy: no "
              "trick\nRandomGuy: no trick\nThe End.\n");
}

}  // namespace gdbLab