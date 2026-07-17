#pragma once

#include <cstdint>

#include "AdvanceStructures/Addresses.hpp"

namespace advanceStructures
{
// student code begin
enum class FiltrationRule : uint8_t
{
    ALLOW,
    DENY,
    IGNORE
};

struct PacketFilterRule
{
    Addresses addresses{};

    FiltrationRule versionFilterRule{FiltrationRule::IGNORE};
    FiltrationRule srcIdFilterRule{FiltrationRule::IGNORE};
    FiltrationRule dstIdFilterRule{FiltrationRule::IGNORE};
    FiltrationRule portFilterRule{FiltrationRule::IGNORE};
};
// student code end
}  // namespace advanceStructures