#include <gtest/gtest.h>

#include "AdvanceStructures/Packet.hpp"
#include "AdvanceStructures/Trace.h"

inline std::string demangle(const char *name)
{
    int status = -4;
    std::unique_ptr<char, void (*)(void *)> res{abi::__cxa_demangle(name, nullptr, nullptr, &status), std::free};
    return (status == 0) ? res.get() : name;
}

TEST(TestTrace, TestInterface)
{
    advanceStructures::Trace trace{"MyTrace"};
    EXPECT_EQ(demangle(typeid(trace.append(advanceStructures::Packet{})).name()), "void");
    EXPECT_EQ(demangle(typeid(trace << advanceStructures::Packet{}).name()), "advanceStructures::Trace");
    EXPECT_EQ(demangle(typeid(trace.getPackets()).name()),
              "std::vector<advanceStructures::Packet, std::allocator<advanceStructures::Packet> >");
    EXPECT_EQ(demangle(typeid(trace.getUniqueTraceName()).name()),
              "std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >");
}

TEST(TestTrace, TestAppend)
{
    EXPECT_EQ(std::is_class<advanceStructures::Trace>::value, true);

    std::vector<advanceStructures::Packet> packets{{.addresses = {.version = 10, .srcId = 3}},
                                                   {.addresses = {.version = 11, .srcId = 4}},
                                                   {.addresses = {.version = 11, .srcId = 5}}};

    const std::string uniqueTraceName{"MyFirstTrace"};

    advanceStructures::Trace trace(uniqueTraceName);
    for (const auto &packet : packets)
    {
        trace.append(packet);
    }

    EXPECT_EQ(trace.getUniqueTraceName(), uniqueTraceName);
    EXPECT_EQ(trace.getTotalPacketsCounter(), packets.size());
    EXPECT_EQ(trace.getPackets(), packets);
}

TEST(TestTrace, TestInsertionOperator)
{
    EXPECT_EQ(std::is_class<advanceStructures::Trace>::value, true);

    std::vector<advanceStructures::Packet> packets{{.addresses = {.version = 10, .srcId = 3}},
                                                   {.addresses = {.version = 11, .srcId = 4}},
                                                   {.addresses = {.version = 11, .srcId = 5}}};

    advanceStructures::Trace trace("MyFirstTrace");
    for (const auto &packet : packets)
    {
        trace << packet;
    }
    trace << packets[0] << packets[1];
    trace << packets[2];
    packets.push_back(packets[0]);
    packets.push_back(packets[1]);
    packets.push_back(packets[2]);

    EXPECT_EQ(trace.getTotalPacketsCounter(), 6);
    EXPECT_EQ(trace.getPackets(), packets);
}
