#pragma once

#include <string>
#include <vector>

#include "AdvanceStructures/PacketFilterRule.hpp"

namespace advanceStructures
{
// student code begin
struct PacketRouteConfig
{
    std::string uniqueTraceName;
    std::vector<PacketFilterRule> filtrationRules;
};

struct RouterConfig
{
    std::vector<PacketRouteConfig> routes;
};
// student code end
}  // namespace advanceStructures