#pragma once

#include <map>

#include "AdvanceStructures/Packet.hpp"
#include "AdvanceStructures/PacketFilter.hpp"
#include "AdvanceStructures/RouterConfig.hpp"
#include "AdvanceStructures/Trace.h"

namespace advanceStructures
{
// student code begin
class Router
{
private:
    std::map<std::string, Trace> traces_{};
    std::map<std::string, PacketFilter> filters_{};

public:
    explicit Router(const RouterConfig &config);

    void routePacket(const Packet &packet);

    const std::map<std::string, Trace> &getTraces() const noexcept;
};
// student code end
}  // namespace advanceStructures