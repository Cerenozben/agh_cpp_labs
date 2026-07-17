#include "Departments/OverSizeElectronicDepartment.h"

#include <limits>

#include "Interfaces/Aliases.hpp"
#include "Interfaces/IProduct.hpp"
#include "Interfaces/ProductFlags.hpp"

namespace warehouseInterface
{
OverSizeElectronicDepartment::OverSizeElectronicDepartment(float maxOccupancy) : items_()
{
    this->maxOccupancy_ = maxOccupancy;
    this->occupancy_ = 0.0;
    this->maxItemSize_ = std::numeric_limits<float>::max();
}

bool OverSizeElectronicDepartment::addItem(IProductPtr item)
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

IProductPtr OverSizeElectronicDepartment::getItem(const ProductDescriptionJson &desc)
{
    picojson::value descVal;
    std::string err = picojson::parse(descVal, desc);

    if (!err.empty() || !descVal.is<picojson::object>())
    {
        return nullptr;
    }

    picojson::object descObj = descVal.get<picojson::object>();

    for (auto it = items_.begin(); it != items_.end(); ++it)
    {
        bool match = true;

        if (descObj.contains("name"))
        {
            if ((*it)->name() != descObj["name"].get<std::string>())
            {
                match = false;
            }
        }

        if (match && descObj.contains("class"))
        {
            picojson::object itemJson = (*it)->asJson();
            if (!itemJson.contains("class") || itemJson["class"].get<std::string>() != descObj["class"].get<std::string>())
            {
                match = false;
            }
        }

        if (match)
        {
            IProductPtr foundItem = std::move(*it);
            this->occupancy_ -= foundItem->itemSize();
            items_.erase(it);
            return foundItem;
        }
    }

    return nullptr;
}

float OverSizeElectronicDepartment::getOccupancy() const
{
    return this->occupancy_;
}

float OverSizeElectronicDepartment::getMaxOccupancy() const
{
    return this->maxOccupancy_;
}

float OverSizeElectronicDepartment::getMaxItemSize() const
{
    return this->maxItemSize_;
}

ProductLabelFlags OverSizeElectronicDepartment::getSupportedFlags() const
{
    return static_cast<ProductLabelFlags>(static_cast<int>(ProductLabelFlags::ESD_SENSITIVE) |
                                          static_cast<int>(ProductLabelFlags::KEEP_DRY));
}

picojson::object OverSizeElectronicDepartment::asJson() const
{
    picojson::object obj;
    obj["class"] = picojson::value(departmentName());
    obj["maxOccupancy"] = picojson::value(static_cast<double>(maxOccupancy_));
    obj["occupancy"] = picojson::value(static_cast<double>(occupancy_));
    obj["items"] = picojson::value(serializedItems());
    return obj;
}

DepartmentStateJson OverSizeElectronicDepartment::serialize() const
{
    return picojson::value(asJson()).serialize();
}

picojson::array OverSizeElectronicDepartment::serializedItems() const
{
    picojson::array arr;
    for (const auto &item : items_)
    {
        arr.emplace_back(item->asJson());
    }
    return arr;
}

std::string OverSizeElectronicDepartment::departmentName() const
{
    return "OverSizeElectronicDepartment";
}

}  // namespace warehouseInterface