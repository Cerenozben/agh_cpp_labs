#pragma once

#include "BasicProduct.hpp"

namespace classes
{

class TV : public BasicProduct
{
public:
    TV(const std::string &name, const float size) :
            BasicProduct("TV",
                         name,
                         size,
                         static_cast<classesInterface::ProductLabelFlags>(
                                 static_cast<int>(classesInterface::ProductLabelFlags::FRAGILE) |
                                 static_cast<int>(classesInterface::ProductLabelFlags::KEEP_DRY)))
    {}
};

}  // namespace classes