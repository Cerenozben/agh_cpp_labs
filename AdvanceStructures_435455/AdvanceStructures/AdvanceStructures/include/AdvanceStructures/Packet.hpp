#pragma once

#include <vector>

#include "AdvanceStructures/Addresses.hpp"

namespace advanceStructures
{
// student code begin
struct Packet
{
    Addresses addresses{};
    uint64_t timestamp{0};
    std::vector<uint8_t> payload{};

    bool operator==(const Packet &other) const { return (addresses == other.addresses) && (timestamp == other.timestamp); }

    bool operator<(const Packet &other) const noexcept
    {
        if (timestamp == other.timestamp)
        {
            return payload.size() < other.payload.size();
        }

        return timestamp < other.timestamp;
    }
};
// student code end
}  // namespace advanceStructures