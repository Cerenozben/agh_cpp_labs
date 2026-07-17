#include "Departments/HazardousDepartment.h"

#include <limits>

#include "Interfaces/Aliases.hpp"
#include "Interfaces/IProduct.hpp"
#include "Interfaces/ProductFlags.hpp"

namespace warehouseInterface
{
HazardousDepartment::HazardousDepartment(float maxOccupancy) : items_()
{
    this->maxOccupancy_ = maxOccupancy;
    this->occupancy_ = 0.0;
    this->maxItemSize_ = std::numeric_limits<float>::max();
}

bool HazardousDepartment::addItem(IProductPtr item)
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

IProductPtr HazardousDepartment::getItem(const ProductDescriptionJson &desc)
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
    const auto &frontItem = items_.front();

    if (descObj.contains("name"))
    {
        if (frontItem->name() != descObj["name"].get<std::string>())
        {
            match = false;
        }
    }

    if (match && descObj.contains("class"))
    {
        picojson::object itemJson = frontItem->asJson();
        if (!itemJson.contains("class") || itemJson["class"].get<std::string>() != descObj["class"].get<std::string>())
        {
            match = false;
        }
    }

    if (match)
    {
        IProductPtr foundItem = std::move(items_.front());
        this->occupancy_ -= foundItem->itemSize();
        items_.pop_front();
        return foundItem;
    }

    return nullptr;
}

float HazardousDepartment::getOccupancy() const
{
    return this->occupancy_;
}

float HazardousDepartment::getMaxOccupancy() const
{
    return this->maxOccupancy_;
}

float HazardousDepartment::getMaxItemSize() const
{
    return this->maxItemSize_;
}

ProductLabelFlags HazardousDepartment::getSupportedFlags() const
{
    return static_cast<ProductLabelFlags>(static_cast<int>(ProductLabelFlags::FIRE_HAZARDOUS) |
                                          static_cast<int>(ProductLabelFlags::EXPLOSIVES) |
                                          static_cast<int>(ProductLabelFlags::KEEP_DRY));
}

picojson::object HazardousDepartment::asJson() const
{
    picojson::object obj;
    obj["class"] = picojson::value(departmentName());
    obj["maxOccupancy"] = picojson::value(static_cast<double>(maxOccupancy_));
    obj["occupancy"] = picojson::value(static_cast<double>(occupancy_));
    obj["items"] = picojson::value(serializedItems());
    return obj;
}

DepartmentStateJson HazardousDepartment::serialize() const
{
    return picojson::value(asJson()).serialize();
}

picojson::array HazardousDepartment::serializedItems() const
{
    picojson::array arr;
    for (const auto &item : items_)
    {
        arr.emplace_back(item->asJson());
    }
    return arr;
}

std::string HazardousDepartment::departmentName() const
{
    return "HazardousDepartment";
}
}  // namespace warehouseInterface