#pragma once
#include <Interfaces/ProductFlags.hpp>
#include <MagicEnum/magic_enum.hpp>
#include <Products/BasicProduct.hpp>

namespace warehouse
{
class GlassWare : public BasicProduct
{
public:
    GlassWare(const std::string &name, const float size) :
            BasicProduct(name, size, "GlassWare", ProductLabelFlags::FRAGILE | ProductLabelFlags::UPWARD)
    {}
};
}  // namespace warehouse