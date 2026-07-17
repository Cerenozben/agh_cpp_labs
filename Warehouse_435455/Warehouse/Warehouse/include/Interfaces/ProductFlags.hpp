#pragma once

namespace warehouseInterface
{
enum class ProductLabelFlags
{
    FIRE_HAZARDOUS = 1 << 0,
    EXPLOSIVES = 1 << 1,
    FRAGILE = 1 << 2,
    UPWARD = 1 << 3,
    KEEP_DRY = 1 << 4,
    HANDLE_WITH_CARE = 1 << 5,
    KEEP_FROZEN = 1 << 6,
    ESD_SENSITIVE = 1 << 7
};

}  // namespace warehouseInterface