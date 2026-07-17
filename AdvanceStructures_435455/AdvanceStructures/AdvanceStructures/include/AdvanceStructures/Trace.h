#pragma once

#include <string>
#include <vector>

#include "AdvanceStructures/Packet.hpp"

namespace advanceStructures
{
// student code begin
class Trace
{
private:
    std::string traceName_{};
    std::vector<Packet> packets_{};

public:
    explicit Trace(std::string name);

    void append(const Packet &packet);

    friend Trace &operator<<(Trace &trace, const Packet &packet);

    uint32_t getTotalPacketsCounter() const noexcept;

    std::string getUniqueTraceName() const;

    const std::vector<Packet> &getPackets() const noexcept;
};
// student code end
}  // namespace advanceStructures