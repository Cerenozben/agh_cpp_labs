#include <gtest/gtest.h>

#include <algorithm>

#include "AdvanceStructures/PacketFilterRule.hpp"

TEST(TestPacketFilterRule, TestMembersAndEnum)
{
    EXPECT_EQ(std::is_class<advanceStructures::PacketFilterRule>::value, true);

    advanceStructures::PacketFilterRule packetFilterRule{
            .addresses = {.version = 10, .srcId = 3, .dstId = 5, .port = 23},
            .versionFilterRule = advanceStructures::FiltrationRule::ALLOW,
            .srcIdFilterRule = advanceStructures::FiltrationRule::DENY,
            .dstIdFilterRule = advanceStructures::FiltrationRule::DENY,
            .portFilterRule = advanceStructures::FiltrationRule::IGNORE,
    };

    EXPECT_EQ(packetFilterRule.addresses, (advanceStructures::Addresses{.version = 10, .srcId = 3, .dstId = 5, .port = 23}));
    EXPECT_EQ(packetFilterRule.versionFilterRule, advanceStructures::FiltrationRule::ALLOW);
    EXPECT_EQ(packetFilterRule.srcIdFilterRule, advanceStructures::FiltrationRule::DENY);
    EXPECT_EQ(packetFilterRule.dstIdFilterRule, advanceStructures::FiltrationRule::DENY);
    EXPECT_EQ(packetFilterRule.portFilterRule, advanceStructures::FiltrationRule::IGNORE);
}

TEST(TestPacketFilterRule, TestDefaultValues)
{
    advanceStructures::PacketFilterRule packetFilterRule{};
    EXPECT_EQ(packetFilterRule.addresses.version, 0);
    EXPECT_EQ(packetFilterRule.addresses.srcId, 0);
    EXPECT_EQ(packetFilterRule.addresses.dstId, 0);
    EXPECT_EQ(packetFilterRule.addresses.port, 0);
    EXPECT_EQ(packetFilterRule.versionFilterRule, advanceStructures::FiltrationRule::IGNORE);
    EXPECT_EQ(packetFilterRule.srcIdFilterRule, advanceStructures::FiltrationRule::IGNORE);
    EXPECT_EQ(packetFilterRule.dstIdFilterRule, advanceStructures::FiltrationRule::IGNORE);
    EXPECT_EQ(packetFilterRule.portFilterRule, advanceStructures::FiltrationRule::IGNORE);
}
