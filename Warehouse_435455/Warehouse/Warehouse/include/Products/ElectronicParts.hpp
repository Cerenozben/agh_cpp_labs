#pragma once
#include <Interfaces/ProductFlags.hpp>
#include <MagicEnum/magic_enum.hpp>
#include <Products/BasicProduct.hpp>

namespace warehouse
{
class ElectronicParts : public BasicProduct
{
public:
    ElectronicParts(const std::string &name, const float size) :
            BasicProduct(name, size, "ElectronicParts", ProductLabelFlags::KEEP_DRY | ProductLabelFlags::ESD_SENSITIVE)
    {}
};
}  // namespace warehouse