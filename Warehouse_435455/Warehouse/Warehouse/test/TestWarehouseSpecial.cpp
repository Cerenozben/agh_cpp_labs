#include <PicoJson/picojson.h>
#include <Warehouse/Warehouse.h>
#include <gtest/gtest.h>

#include <Departments/DepartmentsList.hpp>
#include <Factory/ProductFactory.hpp>
#include <Products/ProductsList.hpp>

namespace warehouse
{
TEST(WarehouseTest, ProductNotFound)
{
    ProductFactory productFactory{};
    Warehouse warehouse{};

    warehouse.addDepartment(std::make_unique<SmallElectronicDepartment>(1000.0));

    std::vector<warehouseInterface::IProductPtr> products{};
    products.emplace_back(productFactory.createProduct("ElectronicParts", "MacBook Pro", 2.0F));
    products.emplace_back(productFactory.createProduct("ElectronicParts", "Dell XPS", 2.0F));
    EXPECT_EQ(
            warehouse.newDelivery(std::move(products)),
            R"({"deliveryReport":[{"assignedDepartment":"SmallElectronicDepartment","errorLog":"","productName":"MacBook Pro","status":"Success"},{"assignedDepartment":"SmallElectronicDepartment","errorLog":"","productName":"Dell XPS","status":"Success"}]})");
    auto order = warehouse.newOrder(R"({"order": [{"class":"ElectronicParts","name":"Lenovo ThinkPad"}]})");
    EXPECT_EQ(order.products.size(), 0);
    EXPECT_EQ(warehouse.getOccupancyReport(),
              R"({"departmentsOccupancy":[{"departmentName":"SmallElectronicDepartment","maxOccupancy":1000,"occupancy":4}]})");
}

TEST(WarehouseTest, ProductCannotBeStored)
{
    ProductFactory productFactory{};
    Warehouse warehouse{};

    warehouse.addDepartment(std::make_unique<SmallElectronicDepartment>(3.0));

    std::vector<warehouseInterface::IProductPtr> products{};
    products.emplace_back(productFactory.createProduct("ElectronicParts", "MacBook Pro", 2.0F));
    products.emplace_back(productFactory.createProduct("ElectronicParts", "Dell XPS", 2.0F));
    products.emplace_back(productFactory.createProduct("ExplosiveBarrel", "Explosive Barrel", 100.0F));

    EXPECT_EQ(
            warehouse.newDelivery(std::move(products)),
            R"({"deliveryReport":[{"assignedDepartment":"SmallElectronicDepartment","errorLog":"","productName":"MacBook Pro","status":"Success"},{"assignedDepartment":"None","errorLog":"Warehouse cannot store this product. Lack of space in departments.","productName":"Dell XPS","status":"Fail"},{"assignedDepartment":"None","errorLog":"Warehouse cannot store this product. Lack of required department.","productName":"Explosive Barrel","status":"Fail"}]})");
}

TEST(WarehouseTest, saveLoad)
{
    ProductFactory productFactory{};
    Warehouse warehouse{};

    warehouse.addDepartment(std::make_unique<SpecialDepartment>(1000.0F));
    warehouse.addDepartment(std::make_unique<ColdRoomDepartment>(1000.0F));
    warehouse.addDepartment(std::make_unique<HazardousDepartment>(1000.0F));
    warehouse.addDepartment(std::make_unique<SmallElectronicDepartment>(1000.0F));
    warehouse.addDepartment(std::make_unique<OverSizeElectronicDepartment>(1000.0F));

    std::vector<warehouseInterface::IProductPtr> products{};
    products.emplace_back(productFactory.createProduct("IndustrialServerRack", "Server Rack", 2.0F));
    products.emplace_back(productFactory.createProduct("GlassWare", "Glass Plate", 0.5F));
    products.emplace_back(productFactory.createProduct("ElectronicParts", "Transistor", 0.5F));
    products.emplace_back(productFactory.createProduct("AstronautsIceCream", "0", 2.0F));
    products.emplace_back(productFactory.createProduct("AstronautsIceCream", "1", 2.0F));
    products.emplace_back(productFactory.createProduct("AstronautsIceCream", "2", 2.0F));
    products.emplace_back(productFactory.createProduct("AstronautsIceCream", "3", 2.0F));
    products.emplace_back(productFactory.createProduct("GlassWare", "Glass Plate", 0.5F));
    products.emplace_back(productFactory.createProduct("ElectronicParts", "Transistor", 0.5F));
    products.emplace_back(productFactory.createProduct("ElectronicParts", "STM", 6.0F));
    products.emplace_back(productFactory.createProduct("IndustrialServerRack", "Server Rack", 2.0F));
    products.emplace_back(productFactory.createProduct("AcetoneBarrel", "1 gal", 50.0F));
    products.emplace_back(productFactory.createProduct("ExplosiveBarrel", "100l", 100.0F));
    products.emplace_back(productFactory.createProduct("TV", "Brave", 40.0F));
    products.emplace_back(productFactory.createProduct("AstronautsIceCream", "2", 2.0F));
    warehouse.newDelivery(std::move(products));

    EXPECT_EQ(
            warehouse.saveWarehouseState(),
            "{\"warehouseState\":[{\"class\":\"SpecialDepartment\",\"items\":[{\"class\":\"GlassWare\",\"flags\":["
            "\"FRAGILE\",\"UPWARD\"],\"name\":\"Glass "
            "Plate\",\"size\":0.5},{\"class\":\"GlassWare\",\"flags\":[\"FRAGILE\",\"UPWARD\"],\"name\":\"Glass "
            "Plate\",\"size\":0.5},{\"class\":\"TV\",\"flags\":[\"FRAGILE\",\"KEEP_DRY\"],\"name\":\"Brave\",\"size\":40}],"
            "\"maxOccupancy\":1000,\"occupancy\":41},{\"class\":\"ColdRoomDepartment\",\"items\":[{\"class\":"
            "\"AstronautsIceCream\",\"flags\":[\"KEEP_DRY\",\"KEEP_FROZEN\"],\"name\":\"0\",\"size\":2},{\"class\":"
            "\"AstronautsIceCream\",\"flags\":[\"KEEP_DRY\",\"KEEP_FROZEN\"],\"name\":\"1\",\"size\":2},{\"class\":"
            "\"AstronautsIceCream\",\"flags\":[\"KEEP_DRY\",\"KEEP_FROZEN\"],\"name\":\"2\",\"size\":2},{\"class\":"
            "\"AstronautsIceCream\",\"flags\":[\"KEEP_DRY\",\"KEEP_FROZEN\"],\"name\":\"3\",\"size\":2},{\"class\":"
            "\"AstronautsIceCream\",\"flags\":[\"KEEP_DRY\",\"KEEP_FROZEN\"],\"name\":\"2\",\"size\":2}],\"maxOccupancy\":1000,"
            "\"occupancy\":10},{\"class\":\"HazardousDepartment\",\"items\":[{\"class\":\"AcetoneBarrel\",\"flags\":["
            "\"FIRE_HAZARDOUS\",\"ESD_SENSITIVE\"],\"name\":\"1 "
            "gal\",\"size\":50},{\"class\":\"ExplosiveBarrel\",\"flags\":[\"EXPLOSIVES\",\"HANDLE_WITH_CARE\"],\"name\":"
            "\"100l\",\"size\":100}],\"maxOccupancy\":1000,\"occupancy\":150},{\"class\":\"SmallElectronicDepartment\","
            "\"items\":[{\"class\":\"IndustrialServerRack\",\"flags\":[\"UPWARD\",\"KEEP_DRY\",\"HANDLE_WITH_CARE\","
            "\"ESD_SENSITIVE\"],\"name\":\"Server "
            "Rack\",\"size\":2},{\"class\":\"ElectronicParts\",\"flags\":[\"KEEP_DRY\",\"ESD_SENSITIVE\"],\"name\":"
            "\"Transistor\",\"size\":0.5},{\"class\":\"ElectronicParts\",\"flags\":[\"KEEP_DRY\",\"ESD_SENSITIVE\"],\"name\":"
            "\"Transistor\",\"size\":0.5},{\"class\":\"IndustrialServerRack\",\"flags\":[\"UPWARD\",\"KEEP_DRY\","
            "\"HANDLE_WITH_CARE\",\"ESD_SENSITIVE\"],\"name\":\"Server "
            "Rack\",\"size\":2}],\"maxOccupancy\":1000,\"occupancy\":5},{\"class\":\"OverSizeElectronicDepartment\","
            "\"items\":[{\"class\":\"ElectronicParts\",\"flags\":[\"KEEP_DRY\",\"ESD_SENSITIVE\"],\"name\":\"STM\",\"size\":6}]"
            ",\"maxOccupancy\":1000,\"occupancy\":6}]}");

    auto save = warehouse.saveWarehouseState();
    {
        Warehouse warehouse2{};
        warehouse2.loadWarehouseState(save);
        EXPECT_EQ(warehouse2.saveWarehouseState(), save);
    }
}
}  // namespace warehouse