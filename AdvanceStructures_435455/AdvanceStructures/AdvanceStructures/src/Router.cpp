#include "AdvanceStructures/Router.h"

#include <utility>

namespace advanceStructures
{
// student code begin
Router::Router(const RouterConfig &config) : traces_{}, filters_{}
{
    for (const auto &route : config.routes)
    {
        traces_.emplace(route.uniqueTraceName, Trace(route.uniqueTraceName));
        filters_.emplace(route.uniqueTraceName, PacketFilter(route.filtrationRules));
    }
}

void Router::routePacket(const Packet &packet)
{
    for (auto &[traceName, filter] : filters_)
    {
        if (filter.shouldPass(packet))
        {
            traces_.at(traceName).append(packet);
        }
    }
}

const std::map<std::string, Trace> &Router::getTraces() const noexcept
{
    return traces_;
}
// student code end
}  // namespace advanceStructures