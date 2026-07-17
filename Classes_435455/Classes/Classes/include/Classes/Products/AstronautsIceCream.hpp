#pragma once

#include "BasicProduct.hpp"

namespace classes
{

class AstronautsIceCream : public BasicProduct
{
public:
    AstronautsIceCream(const std::string &name, const float size) :
            BasicProduct("AstronautsIceCream",
                         name,
                         size,
                         static_cast<classesInterface::ProductLabelFlags>(
                                 static_cast<int>(classesInterface::ProductLabelFlags::KEEP_DRY) |
                                 static_cast<int>(classesInterface::ProductLabelFlags::KEEP_FROZEN)))
    {}
};

}  // namespace classes