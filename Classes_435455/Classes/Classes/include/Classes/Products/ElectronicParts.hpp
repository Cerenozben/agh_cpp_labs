#pragma once

#include "BasicProduct.hpp"

namespace classes
{

class ElectronicParts : public BasicProduct
{
public:
    ElectronicParts(const std::string &name, const float size) :
            BasicProduct("ElectronicParts",
                         name,
                         size,
                         static_cast<classesInterface::ProductLabelFlags>(
                                 static_cast<int>(classesInterface::ProductLabelFlags::KEEP_DRY) |
                                 static_cast<int>(classesInterface::ProductLabelFlags::ESD_SENSITIVE)))
    {}
};

}  // namespace classes