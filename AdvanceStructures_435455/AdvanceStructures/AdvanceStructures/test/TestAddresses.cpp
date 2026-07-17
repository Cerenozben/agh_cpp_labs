#include <gtest/gtest.h>

#include "AdvanceStructures/Addresses.hpp"

TEST(TestAddresses, TestMembers)
{
    EXPECT_EQ(std::is_class<advanceStructures::Addresses>::value, true);

    advanceStructures::Addresses addresses{.version = 10, .srcId = 3, .dstId = 5, .port = 23};
    EXPECT_EQ(addresses.version, 10);
    EXPECT_EQ(addresses.srcId, 3);
    EXPECT_EQ(addresses.dstId, 5);
    EXPECT_EQ(addresses.port, 23);
}

TEST(TestAddresses, TestHash)
{
    advanceStructures::Addresses addresses{.version = 0x10, .srcId = 0x23, .dstId = 0xAA, .port = 0xFE};
    const std::hash<advanceStructures::Addresses> h;
    EXPECT_EQ(h(addresses), 0x1023AAFE);
}

TEST(TestAddresses, TestEqualityOperator)
{
    advanceStructures::Addresses addressesX{.version = 10, .srcId = 3, .dstId = 5, .port = 23};
    advanceStructures::Addresses addressesY{.version = 0x10, .srcId = 0x23, .dstId = 0xAA, .port = 0xFE};
    advanceStructures::Addresses addressesZ{.version = 10, .srcId = 3, .dstId = 5, .port = 23};

    EXPECT_TRUE(addressesX == addressesZ);
    EXPECT_FALSE(addressesX == addressesY);
}