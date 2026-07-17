#pragma once

#include <Classes/PicoJson/picojson.h>

#include <Classes/Interfaces/IProduct.hpp>
#include <Classes/MagicEnum/magic_enum.hpp>
#include <string>
#include <utility>

namespace classes
{

class BasicProduct : public classesInterface::IProduct
{
protected:
    std::string className_;
    std::string name_;
    float size_;
    classesInterface::ProductLabelFlags flags_;

public:
    BasicProduct(std::string className, std::string name, float size, classesInterface::ProductLabelFlags flags) :
            className_(std::move(className)), name_(std::move(name)), size_(size), flags_(flags)
    {}

    std::string name() const override { return name_; }
    float itemSize() const override { return size_; }
    classesInterface::ProductLabelFlags itemFlags() const override { return flags_; }

    picojson::object asJson() const override
    {
        picojson::object obj;
        obj["class"] = picojson::value(className_);
        obj["name"] = picojson::value(name_);
        obj["size"] = picojson::value(static_cast<double>(size_));

        picojson::array flagsArray;

        constexpr auto values = magic_enum::enum_values<classesInterface::ProductLabelFlags>();
        for (auto val : values)
        {
            int intVal = static_cast<int>(val);
            int intFlags = static_cast<int>(flags_);

            if (intVal != 0 && (intFlags & intVal) == intVal)
            {
                flagsArray.emplace_back(std::string(magic_enum::enum_name(val)));
            }
        }

        obj["flags"] = picojson::value(flagsArray);
        return obj;
    }

    classesInterface::ProductDescriptionJson serialize() const override
    {
        picojson::value val(asJson());
        return val.serialize();
    }
};

}  // namespace classes
