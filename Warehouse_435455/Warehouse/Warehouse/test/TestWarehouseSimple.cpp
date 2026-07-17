
#include <PicoJson/picojson.h>
#include <Warehouse/Warehouse.h>
#include <gtest/gtest.h>

#include <Departments/DepartmentsList.hpp>
#include <Factory/ProductFactory.hpp>
#include <Products/ProductsList.hpp>

namespace warehouse
{
TEST(WarehouseTest, OneProduct)
{
    ProductFactory productFactory{};

    Warehouse warehouse{};
    EXPECT_EQ(warehouse.getOccupancyReport(), R"({"departmentsOccupancy":[]})");

    warehouse.addDepartment(std::make_unique<OverSizeElectronicDepartment>(20.0));
    EXPECT_EQ(
            warehouse.getOccupancyReport(),
            R"({"departmentsOccupancy":[{"departmentName":"OverSizeElectronicDepartment","maxOccupancy":20,"occupancy":0}]})");

    std::vector<warehouseInterface::IProductPtr> products{};
    products.emplace_back(productFactory.createProduct("IndustrialServerRack", "Server Rack", 10.0F));
    auto *rawProductPtr = products.back().get();

    EXPECT_EQ(
            warehouse.newDelivery(std::move(products)),
            R"({"deliveryReport":[{"assignedDepartment":"OverSizeElectronicDepartment","errorLog":"","productName":"Server Rack","status":"Success"}]})");

    EXPECT_EQ(
            warehouse.getOccupancyReport(),
            R"({"departmentsOccupancy":[{"departmentName":"OverSizeElectronicDepartment","maxOccupancy":20,"occupancy":10}]})");
    auto order = warehouse.newOrder(R"({"order": [{"class":"IndustrialServerRack"}]})");
    EXPECT_EQ(order.receipt, R"({"order": [{"class":"IndustrialServerRack"}]})");
    EXPECT_EQ(order.products.back().get(), rawProductPtr);
}

TEST(WarehouseTest, GlassWareDelivery)
{
    ProductFactory productFactory{};
    Warehouse warehouse{};

    warehouse.addDepartment(std::make_unique<SpecialDepartment>(10.0));
    EXPECT_EQ(warehouse.getOccupancyReport(),
              R"({"departmentsOccupancy":[{"departmentName":"SpecialDepartment","maxOccupancy":10,"occupancy":0}]})");

    std::vector<warehouseInterface::IProductPtr> products{};
    products.emplace_back(productFactory.createProduct("GlassWare", "Glass Plate", 0.5F));
    auto *rawProductPtr = products.back().get();
    EXPECT_EQ(
            warehouse.newDelivery(std::move(products)),
            R"({"deliveryReport":[{"assignedDepartment":"SpecialDepartment","errorLog":"","productName":"Glass Plate","status":"Success"}]})");
    EXPECT_EQ(warehouse.getOccupancyReport(),
              R"({"departmentsOccupancy":[{"departmentName":"SpecialDepartment","maxOccupancy":10,"occupancy":0.5}]})");
    auto order = warehouse.newOrder(R"({"order": [{"class":"GlassWare"}]})");
    EXPECT_EQ(order.receipt, R"({"order": [{"class":"GlassWare"}]})");
    EXPECT_EQ(order.products.back().get(), rawProductPtr);
}

TEST(WarehouseTest, SmallElectronicPartsDelivery)
{
    ProductFactory productFactory{};
    Warehouse warehouse{};

    warehouse.addDepartment(std::make_unique<SmallElectronicDepartment>(10.0));
    EXPECT_EQ(warehouse.getOccupancyReport(),
              R"({"departmentsOccupancy":[{"departmentName":"SmallElectronicDepartment","maxOccupancy":10,"occupancy":0}]})");

    std::vector<warehouseInterface::IProductPtr> products{};
    products.emplace_back(productFactory.createProduct("ElectronicParts", "Transistor", 0.5F));
    auto *rawProductPtr = products.back().get();
    EXPECT_EQ(
            warehouse.newDelivery(std::move(products)),
            R"({"deliveryReport":[{"assignedDepartment":"SmallElectronicDepartment","errorLog":"","productName":"Transistor","status":"Success"}]})");
    EXPECT_EQ(warehouse.getOccupancyReport(),
              R"({"departmentsOccupancy":[{"departmentName":"SmallElectronicDepartment","maxOccupancy":10,"occupancy":0.5}]})");
    auto order = warehouse.newOrder(R"({"order": [{"class":"ElectronicParts"}]})");
    EXPECT_EQ(order.receipt, R"({"order": [{"class":"ElectronicParts"}]})");
    EXPECT_EQ(order.products.back().get(), rawProductPtr);
}

TEST(WarehouseTest, BigElectronicPartsDelivery)
{
    ProductFactory productFactory{};
    Warehouse warehouse{};

    warehouse.addDepartment(std::make_unique<OverSizeElectronicDepartment>(10.0));
    EXPECT_EQ(
            warehouse.getOccupancyReport(),
            R"({"departmentsOccupancy":[{"departmentName":"OverSizeElectronicDepartment","maxOccupancy":10,"occupancy":0}]})");

    std::vector<warehouseInterface::IProductPtr> products{};
    products.emplace_back(productFactory.createProduct("ElectronicParts", "STM", 5.50F));
    auto *rawProductPtr = products.back().get();
    EXPECT_EQ(
            warehouse.newDelivery(std::move(products)),
            R"({"deliveryReport":[{"assignedDepartment":"OverSizeElectronicDepartment","errorLog":"","productName":"STM","status":"Success"}]})");
    EXPECT_EQ(
            warehouse.getOccupancyReport(),
            R"({"departmentsOccupancy":[{"departmentName":"OverSizeElectronicDepartment","maxOccupancy":10,"occupancy":5.5}]})");
    auto order = warehouse.newOrder(R"({"order": [{"class":"ElectronicParts"}]})");
    EXPECT_EQ(order.receipt, R"({"order": [{"class":"ElectronicParts"}]})");
    EXPECT_EQ(order.products.back().get(), rawProductPtr);
}

TEST(WarehouseTest, ExplosiveBarrelDelivery)
{
    ProductFactory productFactory{};
    Warehouse warehouse{};

    warehouse.addDepartment(std::make_unique<HazardousDepartment>(100.0));
    EXPECT_EQ(warehouse.getOccupancyReport(),
              R"({"departmentsOccupancy":[{"departmentName":"HazardousDepartment","maxOccupancy":100,"occupancy":0}]})");

    std::vector<warehouseInterface::IProductPtr> products{};
    products.emplace_back(productFactory.createProduct("ExplosiveBarrel", "TNT Barrel", 50.0F));
    auto *rawProductPtr = products.back().get();
    EXPECT_EQ(
            warehouse.newDelivery(std::move(products)),
            R"({"deliveryReport":[{"assignedDepartment":"HazardousDepartment","errorLog":"","productName":"TNT Barrel","status":"Success"}]})");
    EXPECT_EQ(warehouse.getOccupancyReport(),
              R"({"departmentsOccupancy":[{"departmentName":"HazardousDepartment","maxOccupancy":100,"occupancy":50}]})");
    auto order = warehouse.newOrder(R"({"order": [{"name":"TNT Barrel"}]})");
    EXPECT_EQ(order.receipt, R"({"order": [{"name":"TNT Barrel"}]})");
    EXPECT_EQ(order.products.back().get(), rawProductPtr);
}

TEST(WarehouseTest, AstronautsIceCreamDelivery)
{
    ProductFactory productFactory{};
    Warehouse warehouse{};

    warehouse.addDepartment(std::make_unique<ColdRoomDepartment>(5.0));
    EXPECT_EQ(warehouse.getOccupancyReport(),
              R"({"departmentsOccupancy":[{"departmentName":"ColdRoomDepartment","maxOccupancy":5,"occupancy":0}]})");

    std::vector<warehouseInterface::IProductPtr> products{};
    products.emplace_back(productFactory.createProduct("AstronautsIceCream", "Chocolate Ice Cream", 0.5F));
    auto *rawProductPtr = products.back().get();
    EXPECT_EQ(
            warehouse.newDelivery(std::move(products)),
            R"({"deliveryReport":[{"assignedDepartment":"ColdRoomDepartment","errorLog":"","productName":"Chocolate Ice Cream","status":"Success"}]})");
    EXPECT_EQ(warehouse.getOccupancyReport(),
              R"({"departmentsOccupancy":[{"departmentName":"ColdRoomDepartment","maxOccupancy":5,"occupancy":0.5}]})");
    auto order = warehouse.newOrder(R"({"order": [{"class":"AstronautsIceCream"}]})");
    EXPECT_EQ(order.receipt, R"({"order": [{"class":"AstronautsIceCream"}]})");
    EXPECT_EQ(order.products.back().get(), rawProductPtr);
}

TEST(WarehouseTest, AcetoneBarrelDelivery)
{
    ProductFactory productFactory{};
    Warehouse warehouse{};

    warehouse.addDepartment(std::make_unique<HazardousDepartment>(100.0));
    EXPECT_EQ(warehouse.getOccupancyReport(),
              R"({"departmentsOccupancy":[{"departmentName":"HazardousDepartment","maxOccupancy":100,"occupancy":0}]})");
    std::vector<warehouseInterface::IProductPtr> products{};
    products.emplace_back(productFactory.createProduct("AcetoneBarrel", "Acetone Barrel", 25.0F));
    auto *rawProductPtr = products.back().get();
    EXPECT_EQ(
            warehouse.newDelivery(std::move(products)),
            R"({"deliveryReport":[{"assignedDepartment":"HazardousDepartment","errorLog":"","productName":"Acetone Barrel","status":"Success"}]})");
    EXPECT_EQ(warehouse.getOccupancyReport(),
              R"({"departmentsOccupancy":[{"departmentName":"HazardousDepartment","maxOccupancy":100,"occupancy":25}]})");
    auto order = warehouse.newOrder(R"({"order": [{"class":"AcetoneBarrel"}]})");
    EXPECT_EQ(order.receipt, R"({"order": [{"class":"AcetoneBarrel"}]})");
    EXPECT_EQ(order.products.back().get(), rawProductPtr);
}

}  // namespace warehouse