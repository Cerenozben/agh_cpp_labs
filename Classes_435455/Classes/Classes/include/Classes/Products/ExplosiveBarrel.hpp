#pragma once

#include "BasicProduct.hpp"

namespace classes
{

class ExplosiveBarrel : public BasicProduct
{
public:
    ExplosiveBarrel(const std::string &name, const float size) :
            BasicProduct("ExplosiveBarrel",
                         name,
                         size,
                         static_cast<classesInterface::ProductLabelFlags>(
                                 static_cast<int>(classesInterface::ProductLabelFlags::EXPLOSIVES) |
                                 static_cast<int>(classesInterface::ProductLabelFlags::HANDLE_WITH_CARE)))
    {}
};

}  // namespace classes