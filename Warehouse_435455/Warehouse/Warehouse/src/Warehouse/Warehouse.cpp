#include <Warehouse/Warehouse.h>

#include "Departments/ColdRoomDepartment.h"
#include "Departments/HazardousDepartment.h"
#include "Departments/OverSizeElectronicDepartment.h"
#include "Departments/SmallElectronicDepartment.h"
#include "Departments/SpecialDepartment.h"
#include "Factory/ProductFactory.hpp"

namespace warehouse
{

using ColdRoomDepartment = warehouseInterface::ColdRoomDepartment;
using HazardousDepartment = warehouseInterface::HazardousDepartment;
using OverSizeElectronicDepartment = warehouseInterface::OverSizeElectronicDepartment;
using SmallElectronicDepartment = warehouseInterface::SmallElectronicDepartment;
using SpecialDepartment = warehouseInterface::SpecialDepartment;

bool Warehouse::hasFlag(warehouseInterface::ProductLabelFlags itemFlags, warehouseInterface::ProductLabelFlags targetFlag)
{
    return (static_cast<int>(itemFlags) & static_cast<int>(targetFlag)) != 0;
}

std::string Warehouse::getTargetDepartmentName(const warehouseInterface::IProductPtr &item)
{
    auto flags = item->itemFlags();

    if (hasFlag(flags, warehouseInterface::ProductLabelFlags::EXPLOSIVES) ||
        hasFlag(flags, warehouseInterface::ProductLabelFlags::FIRE_HAZARDOUS))
    {
        return "HazardousDepartment";
    }

    if (hasFlag(flags, warehouseInterface::ProductLabelFlags::ESD_SENSITIVE))
    {
        if (item->itemSize() <= 5.0F)
        {
            return "SmallElectronicDepartment";
        }

        return "OverSizeElectronicDepartment";
    }

    if (hasFlag(flags, warehouseInterface::ProductLabelFlags::KEEP_FROZEN))
    {
        return "ColdRoomDepartment";
    }

    if (hasFlag(flags, warehouseInterface::ProductLabelFlags::FRAGILE) ||
        hasFlag(flags, warehouseInterface::ProductLabelFlags::HANDLE_WITH_CARE) ||
        hasFlag(flags, warehouseInterface::ProductLabelFlags::UPWARD))
    {
        return "SpecialDepartment";
    }

    return "Any";
}

void Warehouse::addDepartment(warehouseInterface::IDepartmentPtr dept)
{
    if (dept != nullptr)
    {
        departments_.push_back(std::move(dept));
    }
}

warehouseInterface::DeliveryReportJson Warehouse::newDelivery(std::vector<warehouseInterface::IProductPtr> delivery)
{
    picojson::array reportArray;

    for (auto &item : delivery)
    {
        if (!item)
        {
            continue;
        }

        std::string productName = item->name();

        picojson::object reportEntry;
        reportEntry["productName"] = picojson::value(productName);

        std::string targetDeptName = getTargetDepartmentName(item);
        warehouseInterface::IDepartment *targetDeptPtr = nullptr;
        std::string assignedDept = "None";
        std::string errorLog;
        std::string status = "Fail";

        if (targetDeptName == "Any")
        {
            for (auto &dept : departments_)
            {
                if (dept->getOccupancy() + item->itemSize() <= dept->getMaxOccupancy() &&
                    item->itemSize() <= dept->getMaxItemSize())
                {
                    targetDeptPtr = dept.get();
                    break;
                }
            }
        }
        else
        {
            for (auto &dept : departments_)
            {
                if (dept->departmentName() == targetDeptName)
                {
                    targetDeptPtr = dept.get();
                    break;
                }
            }
        }

        if (targetDeptPtr != nullptr)
        {
            if (targetDeptPtr->addItem(std::move(item)))
            {
                assignedDept = targetDeptPtr->departmentName();
                status = "Success";
            }
            else
            {
                errorLog = "Warehouse cannot store this product. Lack of space in departments.";
            }
        }
        else
        {
            if (targetDeptName != "Any")
            {
                errorLog = "Warehouse cannot store this product. Lack of required department.";
            }
            else
            {
                errorLog = "Warehouse cannot store this product. Lack of space in departments.";
            }
        }

        reportEntry["assignedDepartment"] = picojson::value(assignedDept);
        reportEntry["errorLog"] = picojson::value(errorLog);
        reportEntry["status"] = picojson::value(status);
        reportArray.emplace_back(reportEntry);
    }

    picojson::object reportObj;
    reportObj["deliveryReport"] = picojson::value(reportArray);
    return picojson::value(reportObj).serialize();
}

warehouseInterface::Order Warehouse::newOrder(const warehouseInterface::OrderJson &orderJson)
{
    warehouseInterface::Order resultOrder;
    resultOrder.receipt = orderJson;

    picojson::value v;
    std::string err = picojson::parse(v, orderJson);
    if (!err.empty() || !v.is<picojson::object>())
    {
        return resultOrder;
    }

    picojson::object obj = v.get<picojson::object>();
    if (!obj.contains("order") || !obj["order"].is<picojson::array>())
    {
        return resultOrder;
    }

    picojson::array arr = obj["order"].get<picojson::array>();

    for (const auto &request : arr)
    {
        std::string requestStr = picojson::value(request).serialize();

        for (auto &dept : departments_)
        {
            if (warehouseInterface::IProductPtr prod = dept->getItem(requestStr))
            {
                resultOrder.products.push_back(std::move(prod));
                break;
            }
        }
    }

    return resultOrder;
}

warehouseInterface::OccupancyReportJson Warehouse::getOccupancyReport() const
{
    picojson::array depsArr;
    for (const auto &dept : departments_)
    {
        picojson::object d;
        d["departmentName"] = picojson::value(dept->departmentName());
        d["maxOccupancy"] = picojson::value(static_cast<double>(dept->getMaxOccupancy()));
        d["occupancy"] = picojson::value(static_cast<double>(dept->getOccupancy()));
        depsArr.emplace_back(d);
    }

    picojson::object res;
    res["departmentsOccupancy"] = picojson::value(depsArr);
    return picojson::value(res).serialize();
}

warehouseInterface::WarehouseStateJson Warehouse::saveWarehouseState() const
{
    picojson::array stateArray;

    for (const auto &dept : departments_)
    {
        picojson::value deptVal;
        std::string serializedDept = dept->serialize();
        std::string err = picojson::parse(deptVal, serializedDept);

        if (err.empty() && deptVal.is<picojson::object>())
        {
            stateArray.emplace_back(deptVal);
        }
    }

    picojson::object stateObj;
    stateObj["warehouseState"] = picojson::value(stateArray);
    return picojson::value(stateObj).serialize();
}

bool Warehouse::loadWarehouseState(const warehouseInterface::WarehouseStateJson &stateJson)
{
    picojson::value v;
    std::string err = picojson::parse(v, stateJson);
    if (!err.empty() || !v.is<picojson::object>())
    {
        return false;
    }

    picojson::object obj = v.get<picojson::object>();
    if (!obj.contains("warehouseState") || !obj["warehouseState"].is<picojson::array>())
    {
        return false;
    }

    departments_.clear();

    picojson::array arr = obj["warehouseState"].get<picojson::array>();
    for (const auto &dVal : arr)
    {
        if (!dVal.is<picojson::object>())
        {
            return false;
        }
        picojson::object dObj = dVal.get<picojson::object>();

        if (!dObj.contains("class") || !dObj.contains("maxOccupancy"))
        {
            return false;
        }

        std::string className = dObj["class"].get<std::string>();
        float maxOcc = static_cast<float>(dObj["maxOccupancy"].get<double>());

        warehouseInterface::IDepartmentPtr newDept;

        if (className == "ColdRoomDepartment")
        {
            newDept = std::make_unique<warehouseInterface::ColdRoomDepartment>(maxOcc);
        }
        else if (className == "HazardousDepartment")
        {
            newDept = std::make_unique<warehouseInterface::HazardousDepartment>(maxOcc);
        }
        else if (className == "OverSizeElectronicDepartment")
        {
            newDept = std::make_unique<warehouseInterface::OverSizeElectronicDepartment>(maxOcc);
        }
        else if (className == "SmallElectronicDepartment")
        {
            newDept = std::make_unique<warehouseInterface::SmallElectronicDepartment>(maxOcc);
        }
        else if (className == "SpecialDepartment")
        {
            newDept = std::make_unique<warehouseInterface::SpecialDepartment>(maxOcc);
        }
        else
        {
            return false;
        }
        if (dObj.contains("items") && dObj["items"].is<picojson::array>())
        {
            picojson::array itemsArr = dObj["items"].get<picojson::array>();
            ProductFactory factory;
            for (const auto &itemVal : itemsArr)
            {
                picojson::object itemObj = itemVal.get<picojson::object>();

                std::string itemClassName = itemObj["class"].get<std::string>();
                std::string itemName = itemObj["name"].get<std::string>();
                float itemSize = static_cast<float>(itemObj["size"].get<double>());

                auto product = factory.createProduct(itemClassName, itemName, itemSize);

                if (product)
                {
                    newDept->addItem(std::move(product));
                }
            }
        }
        addDepartment(std::move(newDept));
    }

    return true;
}

}  // namespace warehouse