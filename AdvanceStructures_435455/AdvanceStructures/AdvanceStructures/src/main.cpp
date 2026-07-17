#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>

#include "AdvanceStructures/Addresses.hpp"
#include "AdvanceStructures/Packet.hpp"
#include "AdvanceStructures/PacketFilterRule.hpp"
#include "AdvanceStructures/Router.h"
#include "AdvanceStructures/RouterConfig.hpp"

namespace
{

std::vector<advanceStructures::Packet> generatePakets(size_t n)
{
    std::random_device r;

    std::default_random_engine randEngine(r());
    std::uniform_int_distribution<uint8_t> uniformVersionDist(0, 20);
    std::uniform_int_distribution<uint8_t> uniformDist(0, 250);
    std::uniform_int_distribution<uint32_t> uniformTimeDist(0, std::numeric_limits<uint32_t>::max());

    std::vector<advanceStructures::Packet> packets{};
    packets.reserve(n);
    for (size_t i = 0; i < n; i++)
    {
        packets.emplace_back(advanceStructures::Packet{.addresses = {.version = uniformVersionDist(randEngine),
                                                                     .srcId = uniformDist(randEngine),
                                                                     .dstId = uniformDist(randEngine),
                                                                     .port = uniformDist(randEngine)},
                                                       .timestamp = uniformTimeDist(randEngine)});
    }
    return packets;
}

void loopRun(size_t n)
{
    advanceStructures::RouterConfig config{
            .routes = {advanceStructures::PacketRouteConfig{
                               .uniqueTraceName = "vTen",
                               .filtrationRules = {advanceStructures::PacketFilterRule{
                                       .addresses = advanceStructures::Addresses{.version = 10},
                                       .versionFilterRule = advanceStructures::FiltrationRule::ALLOW}}},
                       advanceStructures::PacketRouteConfig{
                               .uniqueTraceName = "vEleven",
                               .filtrationRules = {advanceStructures::PacketFilterRule{
                                       .addresses = advanceStructures::Addresses{.version = 11},
                                       .versionFilterRule = advanceStructures::FiltrationRule::ALLOW}}},
                       advanceStructures::PacketRouteConfig{
                               .uniqueTraceName = "vTwo",
                               .filtrationRules = {advanceStructures::PacketFilterRule{
                                       .addresses = advanceStructures::Addresses{.version = 2},
                                       .versionFilterRule = advanceStructures::FiltrationRule::ALLOW}}}}};
    advanceStructures::Router router{config};

    for (const auto &packet : generatePakets(n))
    {
        router.routePacket(packet);
    }
}

}  // namespace

int main([[maybe_unused]] int argc, [[maybe_unused]] const char *argv[])
{
    std::cout << "RouterExample" << '\n';
    std::cout << "Modes:\n"
              << "1 - shortLoopRun\n"
              << "2 - longLoopRun\n";

    if (argc != 2)
    {
        std::cout << "Select mode!\n";
        return 1;
    }

    int mode = -1;

    try
    {
        mode = std::stoi(argv[1]);
    }
    catch (...)
    {
        std::cout << "Invalid mode!\n";
        return 2;
    }

    std::cout << "Selected mode = " << mode << "\n";
    switch (mode)
    {
        case 1:
            loopRun(10);
            break;
        case 2:
            loopRun(1'000'000);
            break;
        default:
            std::cout << "Unknown mode!\n";
            break;
    }

    return 0;
}
