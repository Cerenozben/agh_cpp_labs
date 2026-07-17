#include "AdvanceStructures/Trace.h"

#include <utility>

namespace advanceStructures
{
// student code begin
Trace::Trace(std::string name) : traceName_(std::move(name)), packets_{} {}

void Trace::append(const Packet &packet)
{
    packets_.push_back(packet);
}

Trace &operator<<(Trace &trace, const Packet &packet)
{
    trace.append(packet);
    return trace;
}

uint32_t Trace::getTotalPacketsCounter() const noexcept
{
    return static_cast<uint32_t>(packets_.size());
}

std::string Trace::getUniqueTraceName() const
{
    return traceName_;
}

const std::vector<Packet> &Trace::getPackets() const noexcept
{
    return packets_;
}
// student code end
}  // namespace advanceStructures