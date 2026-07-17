#include "Departments/SpecialDepartment.h"

#include <limits>

#include "Interfaces/Aliases.hpp"
#include "Interfaces/IProduct.hpp"
#include "Interfaces/ProductFlags.hpp"

namespace warehouseInterface
{
SpecialDepartment::SpecialDepartment(float maxOccupancy) : items_()
{
    this->maxOccupancy_ = maxOccupancy;
    this->occupancy_ = 0.0;
    this->maxItemSize_ = std::numeric_limits<float>::max();
}

bool SpecialDepartment::addItem(IProductPtr item)
{
    if (item == nullptr)
    {
        return false;
    }

    if (this->occupancy_ + item->itemSize() > this->maxOccupancy_)
    {
        return false;
    }

    this->occupancy_ += item->itemSize();
    items_.push_back(std::move(item));
    return true;
}

IProductPtr SpecialDepartment::getItem(const ProductDescriptionJson &desc)
{
    if (items_.empty())
    {
        return nullptr;
    }

    picojson::value descVal;
    std::string err = picojson::parse(descVal, desc);

    if (!err.empty() || !descVal.is<picojson::object>())
    {
        return nullptr;
    }

    picojson::object descObj = descVal.get<picojson::object>();

    bool match = true;
    const auto &backItem = items_.back();

    if (descObj.contains("name"))
    {
        if (backItem->name() != descObj["name"].get<std::string>())
        {
            match = false;
        }
    }

    if (match && descObj.contains("class"))
    {
        picojson::object itemJson = backItem->asJson();
        if (!itemJson.contains("class") || itemJson["class"].get<std::string>() != descObj["class"].get<std::string>())
        {
            match = false;
        }
    }

    if (match)
    {
        IProductPtr foundItem = std::move(items_.back());
        this->occupancy_ -= foundItem->itemSize();
        items_.pop_back();
        return foundItem;
    }

    return nullptr;
}

float SpecialDepartment::getOccupancy() const
{
    return this->occupancy_;
}

float SpecialDepartment::getMaxOccupancy() const
{
    return this->maxOccupancy_;
}

float SpecialDepartment::getMaxItemSize() const
{
    return this->maxItemSize_;
}

ProductLabelFlags SpecialDepartment::getSupportedFlags() const
{
    return static_cast<ProductLabelFlags>(
            static_cast<int>(ProductLabelFlags::FRAGILE) | static_cast<int>(ProductLabelFlags::UPWARD) |
            static_cast<int>(ProductLabelFlags::KEEP_DRY) | static_cast<int>(ProductLabelFlags::HANDLE_WITH_CARE));
}

picojson::object SpecialDepartment::asJson() const
{
    picojson::object obj;
    obj["class"] = picojson::value(departmentName());
    obj["maxOccupancy"] = picojson::value(static_cast<double>(maxOccupancy_));
    obj["occupancy"] = picojson::value(static_cast<double>(occupancy_));
    obj["items"] = picojson::value(serializedItems());
    return obj;
}

DepartmentStateJson SpecialDepartment::serialize() const
{
    return picojson::value(asJson()).serialize();
}

picojson::array SpecialDepartment::serializedItems() const
{
    picojson::array arr;
    for (const auto &item : items_)
    {
        arr.emplace_back(item->asJson());
    }
    return arr;
}

std::string SpecialDepartment::departmentName() const
{
    return "SpecialDepartment";
}

}  // namespace warehouseInterface