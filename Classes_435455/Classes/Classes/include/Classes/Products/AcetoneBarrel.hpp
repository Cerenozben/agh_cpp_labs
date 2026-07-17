#pragma once

#include "BasicProduct.hpp"

namespace classes {

class AcetoneBarrel : public BasicProduct {
public:
    AcetoneBarrel(const std::string& name, const float size)
        : BasicProduct("AcetoneBarrel", name, size, 
            static_cast<classesInterface::ProductLabelFlags>(
                static_cast<int>(classesInterface::ProductLabelFlags::FIRE_HAZARDOUS) | 
                static_cast<int>(classesInterface::ProductLabelFlags::ESD_SENSITIVE)
            )) {}
};

} // namespace classes