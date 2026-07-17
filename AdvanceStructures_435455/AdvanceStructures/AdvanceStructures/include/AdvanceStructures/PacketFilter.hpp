#pragma once

#include <algorithm>

#include "AdvanceStructures/Packet.hpp"
#include "AdvanceStructures/PacketFilterRule.hpp"

namespace advanceStructures
{
// student code begin
class PacketFilter
{
private:
    std::vector<PacketFilterRule> rules_{};

public:
    PacketFilter() = default;

    explicit PacketFilter(const std::vector<PacketFilterRule> &filterRules) : rules_(filterRules) {}

    void addRecord(const PacketFilterRule &record) { rules_.push_back(record); }

    void clear() noexcept { rules_.clear(); }

    bool shouldPass(const Packet &packet) const noexcept
    {
        bool hasAllowMode = false;
        bool explicitlyAllowed = false;

        for (const auto &rule : rules_)
        {
            if (rule.versionFilterRule == FiltrationRule::DENY && rule.addresses.version == packet.addresses.version)
            {
                return false;
            }
            if (rule.srcIdFilterRule == FiltrationRule::DENY && rule.addresses.srcId == packet.addresses.srcId)
            {
                return false;
            }
            if (rule.dstIdFilterRule == FiltrationRule::DENY && rule.addresses.dstId == packet.addresses.dstId)
            {
                return false;
            }
            if (rule.portFilterRule == FiltrationRule::DENY && rule.addresses.port == packet.addresses.port)
            {
                return false;
            }

            bool ruleHasAllow = false;
            bool ruleAllowMatches = true;

            if (rule.versionFilterRule == FiltrationRule::ALLOW)
            {
                hasAllowMode = true;
                ruleHasAllow = true;
                if (rule.addresses.version != packet.addresses.version)
                {
                    ruleAllowMatches = false;
                }
            }
            if (rule.srcIdFilterRule == FiltrationRule::ALLOW)
            {
                hasAllowMode = true;
                ruleHasAllow = true;
                if (rule.addresses.srcId != packet.addresses.srcId)
                {
                    ruleAllowMatches = false;
                }
            }
            if (rule.dstIdFilterRule == FiltrationRule::ALLOW)
            {
                hasAllowMode = true;
                ruleHasAllow = true;
                if (rule.addresses.dstId != packet.addresses.dstId)
                {
                    ruleAllowMatches = false;
                }
            }
            if (rule.portFilterRule == FiltrationRule::ALLOW)
            {
                hasAllowMode = true;
                ruleHasAllow = true;
                if (rule.addresses.port != packet.addresses.port)
                {
                    ruleAllowMatches = false;
                }
            }

            if (ruleHasAllow && ruleAllowMatches)
            {
                explicitlyAllowed = true;
            }
        }

        if (hasAllowMode)
        {
            return explicitlyAllowed;
        }

        return true;
    }
};
// student code end
}  // namespace advanceStructures
