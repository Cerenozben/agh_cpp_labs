#include <gtest/gtest.h>

#include <map>

#include "AdvanceStructures/Packet.hpp"
#include "AdvanceStructures/PacketFilterRule.hpp"
#include "AdvanceStructures/Router.h"
#include "AdvanceStructures/RouterConfig.hpp"
#include "AdvanceStructures/Trace.h"

inline std::string demangle(const char *name)
{
    int status = -4;
    std::unique_ptr<char, void (*)(void *)> res{abi::__cxa_demangle(name, nullptr, nullptr, &status), std::free};
    return (status == 0) ? res.get() : name;
}

using Packet = advanceStructures::Packet;
using PacketsVector = std::vector<Packet>;
using Addresses = advanceStructures::Addresses;
using FiltrationRule = advanceStructures::FiltrationRule;
using PacketFilterRule = advanceStructures::PacketFilterRule;
using PacketRouteConfig = advanceStructures::PacketRouteConfig;
using RouterConfig = advanceStructures::RouterConfig;
using Router = advanceStructures::Router;
using ExpectedValues = std::map<std::string, uint32_t>;

struct TestRouterParams
{
    PacketsVector packets{};
    RouterConfig routerConfig{};
    ExpectedValues expectedValues{};
};

namespace global
{
const PacketsVector packets{{.addresses = {.version = 10, .srcId = 3}},
                            {.addresses = {.version = 11, .srcId = 4}},
                            {.addresses = {.version = 11, .srcId = 5}},
                            {.addresses = {.dstId = 10, .port = 3}},
                            {.addresses = {.dstId = 11, .port = 4}},
                            {.addresses = {.dstId = 11, .port = 5}},
                            {.addresses = {.srcId = 23, .dstId = 24}},
                            {.addresses = {.dstId = 23, .port = 7}},
                            {.addresses = {.dstId = 24, .port = 7}},
                            {.addresses = {.version = 24, .srcId = 7, .dstId = 11, .port = 7}}};
}

class TestRouter : public ::testing::TestWithParam<TestRouterParams>
{};

TEST(TestRouter, TestInterface)
{
    RouterConfig config{
            .routes = {PacketRouteConfig{.uniqueTraceName = "MyFirstTrace",
                                         .filtrationRules = {PacketFilterRule{.addresses = Addresses{.version = 10, .dstId = 4},
                                                                              .versionFilterRule = FiltrationRule::ALLOW,
                                                                              .dstIdFilterRule = FiltrationRule::DENY}}}}};
    Router router{config};
    EXPECT_EQ(demangle(typeid(router.routePacket(advanceStructures::Packet{})).name()), "void");
    EXPECT_EQ(demangle(typeid(router.getTraces()).name()),
              "std::map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, "
              "advanceStructures::Trace, std::less<std::__cxx11::basic_string<char, std::char_traits<char>, "
              "std::allocator<char> > >, std::allocator<std::pair<std::__cxx11::basic_string<char, std::char_traits<char>, "
              "std::allocator<char> > const, advanceStructures::Trace> > >");
}

TEST_P(TestRouter, TestRouting)
{
    const auto [packets, routerConfig, expectedValues] = GetParam();

    Router router(routerConfig);
    for (const auto &packet : packets)
    {
        router.routePacket(packet);
    }

    const auto traces = router.getTraces();
    for (const auto &[expectedTraceName, expectedPacketsSize] : expectedValues)
    {
        const bool traceExists = traces.find(expectedTraceName) != traces.end();
        ASSERT_TRUE(traceExists);
        if (traceExists)
        {
            const auto tracePackets = traces.at(expectedTraceName).getPackets();
            EXPECT_EQ(expectedPacketsSize, tracePackets.size());
        }
    }
}

INSTANTIATE_TEST_CASE_P(
        TestRouting,
        TestRouter,
        ::testing::Values(
                TestRouterParams{.packets = global::packets,
                                 .routerConfig = RouterConfig{},
                                 .expectedValues = ExpectedValues{}},
                TestRouterParams{.packets = global::packets,
                                 .routerConfig = RouterConfig{.routes = {PacketRouteConfig{.uniqueTraceName = "MyFirstTrace",
                                                                                           .filtrationRules = {}}}},
                                 .expectedValues = ExpectedValues{{"MyFirstTrace", 10}}},
                TestRouterParams{
                        .packets = global::packets,
                        .routerConfig =
                                RouterConfig{.routes = {PacketRouteConfig{
                                                                .uniqueTraceName = "MyFirstTrace",
                                                                .filtrationRules = {PacketFilterRule{
                                                                        .addresses = Addresses{.version = 10, .port = 7},
                                                                        .versionFilterRule = FiltrationRule::ALLOW,
                                                                        .portFilterRule = FiltrationRule::ALLOW}}},
                                                        PacketRouteConfig{
                                                                .uniqueTraceName = "MySecondTrace",
                                                                .filtrationRules = {PacketFilterRule{.addresses = Addresses{.version = 10},
                                                                                                     .versionFilterRule = FiltrationRule::ALLOW},
                                                                                    PacketFilterRule{.addresses =
                                                                                                             Addresses{.port = 7},
                                                                                                     .portFilterRule = FiltrationRule::ALLOW}}}}},
                        .expectedValues = ExpectedValues{{"MyFirstTrace", 0}, {"MySecondTrace", 4}}},
                TestRouterParams{
                        .packets = global::packets,
                        .routerConfig =
                                RouterConfig{.routes = {PacketRouteConfig{
                                                                .uniqueTraceName = "MyFirstTrace",
                                                                .filtrationRules = {PacketFilterRule{
                                                                        .addresses = Addresses{.version = 11, .dstId = 11},
                                                                        .versionFilterRule = FiltrationRule::DENY,
                                                                        .dstIdFilterRule = FiltrationRule::DENY}}},
                                                        PacketRouteConfig{
                                                                .uniqueTraceName = "MySecondTrace",
                                                                .filtrationRules = {PacketFilterRule{
                                                                        .addresses = Addresses{.version = 11, .dstId = 11},
                                                                        .versionFilterRule = FiltrationRule::DENY,
                                                                        .dstIdFilterRule = FiltrationRule::DENY}}}}},
                        .expectedValues = ExpectedValues{{"MyFirstTrace", 5}, {"MySecondTrace", 5}}},
                TestRouterParams{
                        .packets = global::packets,
                        .routerConfig =
                                RouterConfig{.routes = {PacketRouteConfig{.uniqueTraceName = "MyFirstTrace",
                                                                          .filtrationRules = {PacketFilterRule{
                                                                                  .addresses = Addresses{.version = 10},
                                                                                  .versionFilterRule = FiltrationRule::ALLOW}}},
                                                        PacketRouteConfig{.uniqueTraceName = "MySecondTrace",
                                                                          .filtrationRules = {PacketFilterRule{
                                                                                  .addresses = Addresses{.version = 10},
                                                                                  .versionFilterRule = FiltrationRule::DENY}}},
                                                        PacketRouteConfig{.uniqueTraceName = "MyThirdTrace",
                                                                          .filtrationRules = {PacketFilterRule{
                                                                                  .addresses = Addresses{.version = 24,
                                                                                                         .srcId = 7,
                                                                                                         .dstId = 11,
                                                                                                         .port = 7},
                                                                                  .versionFilterRule = FiltrationRule::ALLOW,
                                                                                  .srcIdFilterRule = FiltrationRule::ALLOW,
                                                                                  .dstIdFilterRule = FiltrationRule::ALLOW,
                                                                                  .portFilterRule = FiltrationRule::ALLOW}}}}},
                        .expectedValues = ExpectedValues{{"MyFirstTrace", 1}, {"MySecondTrace", 9}, {"MyThirdTrace", 1}}}));