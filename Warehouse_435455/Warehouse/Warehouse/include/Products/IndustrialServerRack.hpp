#pragma once
#include <Interfaces/ProductFlags.hpp>
#include <MagicEnum/magic_enum.hpp>
#include <Products/BasicProduct.hpp>

namespace warehouse
{
class IndustrialServerRack : public BasicProduct
{
public:
    IndustrialServerRack(const std::string &name, const float size) :
            BasicProduct(name,
                         size,
                         "IndustrialServerRack",
                         ProductLabelFlags::HANDLE_WITH_CARE | ProductLabelFlags::ESD_SENSITIVE | ProductLabelFlags::UPWARD |
                                 ProductLabelFlags::KEEP_DRY)
    {}
};
}  // namespace warehouse