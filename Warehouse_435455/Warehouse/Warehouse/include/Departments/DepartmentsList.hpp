#pragma once
#include <Departments/ColdRoomDepartment.h>
#include <Departments/HazardousDepartment.h>
#include <Departments/OverSizeElectronicDepartment.h>
#include <Departments/SmallElectronicDepartment.h>
#include <Departments/SpecialDepartment.h>

namespace warehouse
{
using ColdRoomDepartment = warehouseInterface::ColdRoomDepartment;
using HazardousDepartment = warehouseInterface::HazardousDepartment;
using OverSizeElectronicDepartment = warehouseInterface::OverSizeElectronicDepartment;
using SmallElectronicDepartment = warehouseInterface::SmallElectronicDepartment;
using SpecialDepartment = warehouseInterface::SpecialDepartment;
}  // namespace warehouse