#pragma once
#include <Interfaces/ProductFlags.hpp>
#include <MagicEnum/magic_enum.hpp>
#include <Products/BasicProduct.hpp>

namespace warehouse
{
class AstronautsIceCream : public BasicProduct
{
public:
    AstronautsIceCream(const std::string &name, const float size) :
            BasicProduct(name, size, "AstronautsIceCream", ProductLabelFlags::KEEP_FROZEN | ProductLabelFlags::KEEP_DRY)
    {}
};
}  // namespace warehouse