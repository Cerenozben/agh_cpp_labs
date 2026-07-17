#pragma once
#include <Interfaces/ProductFlags.hpp>
#include <MagicEnum/magic_enum.hpp>
#include <Products/BasicProduct.hpp>

namespace warehouse
{
class AcetoneBarrel : public BasicProduct
{
public:
    AcetoneBarrel(const std::string &name, const float size) :
            BasicProduct(name, size, "AcetoneBarrel", ProductLabelFlags::FIRE_HAZARDOUS | ProductLabelFlags::ESD_SENSITIVE)
    {}
};
}  // namespace warehouse