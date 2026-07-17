#include <gtest/gtest.h>

#include <algorithm>

#include "AdvanceStructures/Packet.hpp"

TEST(TestPacket, TestMembers)
{
    EXPECT_EQ(std::is_class<advanceStructures::Packet>::value, true);

    advanceStructures::Packet packet{.addresses = {.version = 10, .srcId = 3, .dstId = 5, .port = 23},
                                     .timestamp = 100,
                                     .payload = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

    packet.addresses.port = 50;
    packet.timestamp += 100;
    packet.payload.emplace_back(11);

    EXPECT_EQ(packet.addresses, (advanceStructures::Addresses{.version = 10, .srcId = 3, .dstId = 5, .port = 50}));
    EXPECT_EQ(packet.timestamp, 200);
    EXPECT_EQ(packet.payload.size(), 11);
}

TEST(TestPacket, TestFind)
{
    const advanceStructures::Packet packet1{.addresses = {.version = 10, .srcId = 3, .dstId = 5, .port = 23},
                                            .timestamp = 100,
                                            .payload = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
    const advanceStructures::Packet packet2{.addresses = {.version = 11, .srcId = 3, .dstId = 5, .port = 45},
                                            .timestamp = 200,
                                            .payload = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

    std::vector<advanceStructures::Packet> packets{packet1, packet2};

    const advanceStructures::Packet existingPacket{.addresses = {.version = 10, .srcId = 3, .dstId = 5, .port = 23},
                                                   .timestamp = 100};
    EXPECT_TRUE(std::find(packets.begin(), packets.end(), existingPacket) != packets.end());

    const advanceStructures::Packet nonExistingPacket{.addresses = {.version = 10, .srcId = 33, .dstId = 5, .port = 23},
                                                      .timestamp = 100};
    EXPECT_TRUE(std::find(packets.begin(), packets.end(), nonExistingPacket) == packets.end());
}

TEST(TestPacket, TestSort)
{
    const advanceStructures::Packet packet1{.addresses = {.version = 10, .srcId = 3, .dstId = 5, .port = 23},
                                            .timestamp = 100,
                                            .payload = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
    const advanceStructures::Packet packet2{.addresses = {.version = 12, .srcId = 3, .dstId = 34, .port = 23},
                                            .timestamp = 300,
                                            .payload = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
    const advanceStructures::Packet packet3{.addresses = {.version = 11, .srcId = 3, .dstId = 5, .port = 45},
                                            .timestamp = 200,
                                            .payload = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
    const advanceStructures::Packet packet4{.addresses = {.version = 11, .srcId = 3, .dstId = 5, .port = 45},
                                            .timestamp = 200,
                                            .payload = {1, 2, 3, 4, 5, 6, 7}};

    std::vector<advanceStructures::Packet> packets{packet1, packet2, packet3, packet4};
    std::sort(packets.begin(), packets.end());

    EXPECT_EQ(packets, (std::vector<advanceStructures::Packet>{packet1, packet4, packet3, packet2}));
}