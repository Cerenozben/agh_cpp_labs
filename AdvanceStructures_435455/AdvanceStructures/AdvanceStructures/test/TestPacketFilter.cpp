#include <gtest/gtest.h>

#include "AdvanceStructures/Addresses.hpp"
#include "AdvanceStructures/Packet.hpp"
#include "AdvanceStructures/PacketFilter.hpp"
#include "AdvanceStructures/PacketFilterRule.hpp"

inline std::string demangle(const char *name)
{
    int status = -4;
    std::unique_ptr<char, void (*)(void *)> res{abi::__cxa_demangle(name, nullptr, nullptr, &status), std::free};
    return (status == 0) ? res.get() : name;
}

TEST(TestPacketFilter, TestInterface)
{
    advanceStructures::PacketFilter filter{};
    EXPECT_EQ(demangle(typeid(filter.clear()).name()), "void");
    EXPECT_EQ(demangle(typeid(filter.shouldPass(advanceStructures::Packet{})).name()), "bool");
    EXPECT_EQ(demangle(typeid(filter.addRecord(advanceStructures::PacketFilterRule{})).name()), "void");
}

inline uint32_t countPassedPackets(const advanceStructures::PacketFilter &filter,
                                   const std::vector<advanceStructures::Packet> &packets)
{
    uint32_t counter = 0;
    for (const auto &packet : packets)
    {
        if (filter.shouldPass(packet))
        {
            counter++;
        }
    }
    return counter;
};

TEST(TestPacketFilter, TestAllow)
{
    std::vector<advanceStructures::Packet> packets{{.addresses = {.version = 10, .srcId = 3}},
                                                   {.addresses = {.version = 11, .srcId = 4}},
                                                   {.addresses = {.version = 11, .srcId = 5}}};

    advanceStructures::PacketFilter filter{};

    filter.clear();
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.version = 11},
                                                         .versionFilterRule = advanceStructures::FiltrationRule::ALLOW});
    EXPECT_EQ(countPassedPackets(filter, packets), 2);

    filter.clear();
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.srcId = 4},
                                                         .srcIdFilterRule = advanceStructures::FiltrationRule::ALLOW});
    EXPECT_EQ(countPassedPackets(filter, packets), 1);

    filter.clear();
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.version = 11, .srcId = 4},
                                                         .versionFilterRule = advanceStructures::FiltrationRule::ALLOW,
                                                         .srcIdFilterRule = advanceStructures::FiltrationRule::ALLOW});
    EXPECT_EQ(countPassedPackets(filter, packets), 1);
}

TEST(TestPacketFilter, TestDeny)
{
    std::vector<advanceStructures::Packet> packets{{.addresses = {.version = 10, .srcId = 3}},
                                                   {.addresses = {.version = 11, .srcId = 4}},
                                                   {.addresses = {.version = 11, .srcId = 5}}};

    advanceStructures::PacketFilter filter{};

    filter.clear();
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.version = 11},
                                                         .versionFilterRule = advanceStructures::FiltrationRule::DENY});
    EXPECT_EQ(countPassedPackets(filter, packets), 1);

    filter.clear();
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.srcId = 4},
                                                         .srcIdFilterRule = advanceStructures::FiltrationRule::DENY});
    EXPECT_EQ(countPassedPackets(filter, packets), 2);

    filter.clear();
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.version = 11, .srcId = 3},
                                                         .versionFilterRule = advanceStructures::FiltrationRule::DENY,
                                                         .srcIdFilterRule = advanceStructures::FiltrationRule::DENY});
    EXPECT_EQ(countPassedPackets(filter, packets), 0);
}

TEST(TestPacketFilter, TestAllowAllow)
{
    std::vector<advanceStructures::Packet> packets{{.addresses = {.version = 10, .srcId = 3}},
                                                   {.addresses = {.version = 11, .srcId = 4}},
                                                   {.addresses = {.version = 11, .srcId = 5}}};

    advanceStructures::PacketFilter filter{};

    filter.clear();
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.srcId = 3},
                                                         .srcIdFilterRule = advanceStructures::FiltrationRule::ALLOW});
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.srcId = 4},
                                                         .srcIdFilterRule = advanceStructures::FiltrationRule::ALLOW});
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.srcId = 5},
                                                         .srcIdFilterRule = advanceStructures::FiltrationRule::ALLOW});
    EXPECT_EQ(countPassedPackets(filter, packets), 3);

    filter.clear();
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.version = 11},
                                                         .versionFilterRule = advanceStructures::FiltrationRule::ALLOW});
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.srcId = 3},
                                                         .srcIdFilterRule = advanceStructures::FiltrationRule::ALLOW});
    EXPECT_EQ(countPassedPackets(filter, packets), 3);

    filter.clear();
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.srcId = 3},
                                                         .srcIdFilterRule = advanceStructures::FiltrationRule::ALLOW});
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.srcId = 5},
                                                         .srcIdFilterRule = advanceStructures::FiltrationRule::ALLOW});
    EXPECT_EQ(countPassedPackets(filter, packets), 2);
}

TEST(TestPacketFilter, TestDenyDeny)
{
    std::vector<advanceStructures::Packet> packets{{.addresses = {.dstId = 10, .port = 3}},
                                                   {.addresses = {.dstId = 11, .port = 4}},
                                                   {.addresses = {.dstId = 11, .port = 5}}};

    advanceStructures::PacketFilter filter{};

    filter.clear();
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.dstId = 10},
                                                         .dstIdFilterRule = advanceStructures::FiltrationRule::DENY});
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.port = 4},
                                                         .portFilterRule = advanceStructures::FiltrationRule::DENY});
    EXPECT_EQ(countPassedPackets(filter, packets), 1);

    filter.clear();
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.dstId = 10},
                                                         .dstIdFilterRule = advanceStructures::FiltrationRule::DENY});
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.port = 3},
                                                         .portFilterRule = advanceStructures::FiltrationRule::DENY});
    EXPECT_EQ(countPassedPackets(filter, packets), 2);
}

TEST(TestPacketFilter, TestDenyAllow)
{
    std::vector<advanceStructures::Packet> packets{{.addresses = {.dstId = 10, .port = 3}},
                                                   {.addresses = {.dstId = 11, .port = 4}},
                                                   {.addresses = {.dstId = 11, .port = 5}}};

    advanceStructures::PacketFilter filter{};

    filter.clear();
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.dstId = 10},
                                                         .dstIdFilterRule = advanceStructures::FiltrationRule::DENY});
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.port = 4},
                                                         .portFilterRule = advanceStructures::FiltrationRule::ALLOW});
    EXPECT_EQ(countPassedPackets(filter, packets), 1);

    filter.clear();
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.dstId = 10},
                                                         .dstIdFilterRule = advanceStructures::FiltrationRule::DENY});
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.port = 3},
                                                         .portFilterRule = advanceStructures::FiltrationRule::ALLOW});
    EXPECT_EQ(countPassedPackets(filter, packets), 0);

    filter.clear();
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.dstId = 11},
                                                         .dstIdFilterRule = advanceStructures::FiltrationRule::DENY});
    filter.addRecord(advanceStructures::PacketFilterRule{.addresses = {.port = 3},
                                                         .portFilterRule = advanceStructures::FiltrationRule::ALLOW});
    EXPECT_EQ(countPassedPackets(filter, packets), 1);
}