#pragma once

#include <cstdint>
#include <functional>

namespace advanceStructures
{
// student code begin
struct Addresses
{
    uint8_t version{0};
    uint8_t srcId{0};
    uint8_t dstId{0};
    uint8_t port{0};

    bool operator==(const Addresses &other) const noexcept;
};
}  // namespace advanceStructures
namespace std
{
template <>
struct hash<advanceStructures::Addresses>
{
    uint32_t operator()(const advanceStructures::Addresses &addr) const noexcept
    {
        return (static_cast<uint32_t>(addr.version) << 24) | (static_cast<uint32_t>(addr.srcId) << 16) |
               (static_cast<uint32_t>(addr.dstId) << 8) | static_cast<uint32_t>(addr.port);
    }
};
}  // namespace std
namespace advanceStructures
{
inline bool Addresses::operator==(const Addresses &other) const noexcept
{
    return std::hash<Addresses>{}(*this) == std::hash<Addresses>{}(other);
}
// student code end
}  // namespace advanceStructures