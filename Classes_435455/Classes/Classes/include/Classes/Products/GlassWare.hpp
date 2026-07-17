#pragma once

#include "BasicProduct.hpp"

namespace classes
{

class GlassWare : public BasicProduct
{
public:
    GlassWare(const std::string &name, const float size) :
            BasicProduct("GlassWare",
                         name,
                         size,
                         static_cast<classesInterface::ProductLabelFlags>(
                                 static_cast<int>(classesInterface::ProductLabelFlags::FRAGILE) |
                                 static_cast<int>(classesInterface::ProductLabelFlags::UPWARD)))
    {}
};

}  // namespace classes