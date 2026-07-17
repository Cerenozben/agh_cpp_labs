#pragma once
#include <PicoJson/picojson.h>

#include <Interfaces/IProduct.hpp>
#include <MagicEnum/magic_enum.hpp>
#include <utility>

namespace warehouse
{

using magic_enum::bitwise_operators::operator|;
using warehouseInterface::ProductLabelFlags;

class BasicProduct : public warehouseInterface::IProduct
{
public:
    BasicProduct(std::string name, const float size, std::string className, ProductLabelFlags flags) :
            name_{std::move(name)}, size_{size}, className_{std::move(className)}, flags_{flags}
    {}

    std::string name() const override { return name_; }

    float itemSize() const override { return size_; }

    ProductLabelFlags itemFlags() const override { return flags_; }

    picojson::object asJson() const override
    {
        picojson::object jsonObject;
        jsonObject["name"] = picojson::value(name_);
        jsonObject["size"] = picojson::value(static_cast<double>(size_));
        jsonObject["flags"] = picojson::value(serializeFlags(itemFlags()));
        jsonObject["class"] = picojson::value(className_);
        return jsonObject;
    }

    warehouseInterface::ProductDescriptionJson serialize() const override { return picojson::value(asJson()).serialize(); }

protected:
    const std::string name_;
    const float size_;
    const std::string className_;
    const warehouseInterface::ProductLabelFlags flags_;

private:
    static picojson::array serializeFlags(const warehouseInterface::ProductLabelFlags &flag)
    {
        picojson::array jsonArray;
        for (const auto &enumValue : magic_enum::enum_values<warehouseInterface::ProductLabelFlags>())
        {
            using magic_enum::bitwise_operators::operator&;
            if ((flag & enumValue) == enumValue)
            {
                std::string strVal{magic_enum::enum_name(enumValue)};
                jsonArray.emplace_back(strVal);
            }
        }

        return jsonArray;
    }
};
}  // namespace warehouse