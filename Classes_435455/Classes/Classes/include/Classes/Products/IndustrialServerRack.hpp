#pragma once

#include "BasicProduct.hpp"

namespace classes
{

class IndustrialServerRack : public BasicProduct
{
public:
    IndustrialServerRack(const std::string &name, const float size) :
            BasicProduct("IndustrialServerRack",
                         name,
                         size,
                         static_cast<classesInterface::ProductLabelFlags>(
                                 static_cast<int>(classesInterface::ProductLabelFlags::UPWARD) |
                                 static_cast<int>(classesInterface::ProductLabelFlags::KEEP_DRY) |
                                 static_cast<int>(classesInterface::ProductLabelFlags::HANDLE_WITH_CARE) |
                                 static_cast<int>(classesInterface::ProductLabelFlags::ESD_SENSITIVE)))
    {}
};

}  // namespace classes