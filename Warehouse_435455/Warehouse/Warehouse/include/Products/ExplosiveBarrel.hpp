#pragma once
#include <Interfaces/ProductFlags.hpp>
#include <MagicEnum/magic_enum.hpp>
#include <Products/BasicProduct.hpp>

namespace warehouse
{
class ExplosiveBarrel : public BasicProduct
{
public:
    ExplosiveBarrel(const std::string &name, const float size) :
            BasicProduct(name, size, "ExplosiveBarrel", ProductLabelFlags::EXPLOSIVES | ProductLabelFlags::HANDLE_WITH_CARE)
    {}
};
}  // namespace warehouse