#pragma once
#include <Interfaces/ProductFlags.hpp>
#include <MagicEnum/magic_enum.hpp>
#include <Products/BasicProduct.hpp>

namespace warehouse
{
class TV : public BasicProduct
{
public:
    TV(const std::string &name, const float size) :
            BasicProduct(name, size, "TV", ProductLabelFlags::FRAGILE | ProductLabelFlags::KEEP_DRY)
    {}
};
}  // namespace warehouse