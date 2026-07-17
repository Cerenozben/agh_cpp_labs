
#include <PicoJson/picojson.h>
#include <gtest/gtest.h>

#include <Departments/DepartmentsList.hpp>
#include <Interfaces/IProduct.hpp>
#include <Products/ProductsList.hpp>

namespace warehouse
{
// ------------------------------------ ColdRoomDepartment ------------------------------------
TEST(ColdRoomDepartmentTest, ConstructorAndConfigurationTest)
{
    warehouse::ColdRoomDepartment coldRoomDepartment(10.0F);
    EXPECT_EQ(coldRoomDepartment.getMaxOccupancy(), 10.0F);
    EXPECT_EQ(coldRoomDepartment.getMaxItemSize(), std::numeric_limits<float>().max());
    EXPECT_EQ(static_cast<uint32_t>(coldRoomDepartment.getSupportedFlags()), 80);
}

TEST(ColdRoomDepartmentTest, AddGetBasicTest)
{
    warehouse::ColdRoomDepartment coldRoomDepartment(10.0F);

    std::unique_ptr<warehouseInterface::IProduct> astronautsIceCreamVanillaPtr =
            std::make_unique<warehouse::AstronautsIceCream>("Vanilla", 0.5F);
    std::unique_ptr<warehouseInterface::IProduct> astronautsIceCreamChocolatePtr =
            std::make_unique<warehouse::AstronautsIceCream>("Chocolate", 1.5F);
    std::unique_ptr<warehouseInterface::IProduct> astronautsIceCreamApplePtr =
            std::make_unique<warehouse::AstronautsIceCream>("Apple", 10.0F);
    const auto productDesc = astronautsIceCreamVanillaPtr->serialize();

    bool addStatus = false;
    addStatus = coldRoomDepartment.addItem(std::move(astronautsIceCreamVanillaPtr));
    EXPECT_EQ(addStatus, true);
    addStatus = coldRoomDepartment.addItem(std::move(astronautsIceCreamChocolatePtr));
    EXPECT_EQ(addStatus, true);
    addStatus = coldRoomDepartment.addItem(std::move(astronautsIceCreamApplePtr));
    EXPECT_EQ(addStatus, false);
    EXPECT_EQ(coldRoomDepartment.getOccupancy(), 2.0F);

    auto item = coldRoomDepartment.getItem(productDesc);
    EXPECT_EQ(item == nullptr, false);
    EXPECT_EQ(item->itemSize(), 0.5F);
    EXPECT_EQ(item->name(), std::string("Vanilla"));
    EXPECT_EQ(coldRoomDepartment.getOccupancy(), 1.5F);
}

TEST(ColdRoomDepartmentTest, AddGetExtendedTest)
{
    warehouse::ColdRoomDepartment coldRoomDepartment(20.0F);
    std::unique_ptr<warehouseInterface::IProduct> astronautsIceCreamVanillaPtr =
            std::make_unique<warehouse::AstronautsIceCream>("Vanilla", 0.5F);
    std::unique_ptr<warehouseInterface::IProduct> astronautsIceCreamChocolatePtr =
            std::make_unique<warehouse::AstronautsIceCream>("Chocolate", 1.5F);
    std::unique_ptr<warehouseInterface::IProduct> astronautsIceCreamApplePtr =
            std::make_unique<warehouse::AstronautsIceCream>("Apple", 10.0F);

    coldRoomDepartment.addItem(std::move(astronautsIceCreamVanillaPtr));
    coldRoomDepartment.addItem(std::move(astronautsIceCreamChocolatePtr));
    coldRoomDepartment.addItem(std::move(astronautsIceCreamApplePtr));

    warehouseInterface::IProductPtr item;

    warehouseInterface::ProductDescriptionJson productDescOnlyName(R"({"name": "Chocolate"})");
    item = coldRoomDepartment.getItem(productDescOnlyName);
    EXPECT_EQ(item == nullptr, false);
    EXPECT_EQ(item->itemSize(), 1.5F);
    EXPECT_EQ(item->name(), std::string("Chocolate"));
    EXPECT_EQ(dynamic_cast<warehouse::AstronautsIceCream *>(item.get()) != nullptr, true);
    EXPECT_EQ(dynamic_cast<warehouse::AcetoneBarrel *>(item.get()) != nullptr, false);
    EXPECT_EQ(coldRoomDepartment.getOccupancy(), 10.5F);

    warehouseInterface::ProductDescriptionJson productDescOnlyClass(R"({"class": "AstronautsIceCream"})");
    item = coldRoomDepartment.getItem(productDescOnlyClass);
    EXPECT_EQ(item == nullptr, false);
    EXPECT_EQ(item->itemSize(), 0.5F);
    EXPECT_EQ(item->name(), std::string("Vanilla"));
    EXPECT_EQ(dynamic_cast<warehouse::AstronautsIceCream *>(item.get()) != nullptr, true);
    EXPECT_EQ(dynamic_cast<warehouse::AcetoneBarrel *>(item.get()) != nullptr, false);
    EXPECT_EQ(coldRoomDepartment.getOccupancy(), 10.0F);

    warehouseInterface::ProductDescriptionJson productDescOnlyNameNotExisting(R"({"name": "Strawberry"})");
    item = coldRoomDepartment.getItem(productDescOnlyNameNotExisting);
    EXPECT_EQ(item == nullptr, true);

    warehouseInterface::ProductDescriptionJson productDescOnlyClassNotExisting(R"({"class": "AcetoneBarrel"})");
    item = coldRoomDepartment.getItem(productDescOnlyClassNotExisting);
    EXPECT_EQ(item == nullptr, true);
    EXPECT_EQ(coldRoomDepartment.getOccupancy(), 10.0F);
}

TEST(ColdRoomDepartmentTest, SerializeTest)
{
    warehouse::ColdRoomDepartment coldRoomDepartment(20.0F);
    EXPECT_EQ(coldRoomDepartment.serialize(),
              std::string(R"({"class":"ColdRoomDepartment","items":[],"maxOccupancy":20,"occupancy":0})"));

    std::unique_ptr<warehouseInterface::IProduct> astronautsIceCreamVanillaPtr =
            std::make_unique<warehouse::AstronautsIceCream>("Vanilla", 0.5F);
    coldRoomDepartment.addItem(std::move(astronautsIceCreamVanillaPtr));
    EXPECT_EQ(
            coldRoomDepartment.serialize(),
            std::string(
                    R"({"class":"ColdRoomDepartment","items":[{"class":"AstronautsIceCream","flags":["KEEP_DRY","KEEP_FROZEN"],"name":"Vanilla","size":0.5}],"maxOccupancy":20,"occupancy":0.5})"));

    std::unique_ptr<warehouseInterface::IProduct> astronautsIceCreamChocolatePtr =
            std::make_unique<warehouse::AstronautsIceCream>("Chocolate", 1.5F);
    coldRoomDepartment.addItem(std::move(astronautsIceCreamChocolatePtr));
    EXPECT_EQ(
            coldRoomDepartment.serialize(),
            std::string(
                    R"({"class":"ColdRoomDepartment","items":[{"class":"AstronautsIceCream","flags":["KEEP_DRY","KEEP_FROZEN"],"name":"Vanilla","size":0.5},{"class":"AstronautsIceCream","flags":["KEEP_DRY","KEEP_FROZEN"],"name":"Chocolate","size":1.5}],"maxOccupancy":20,"occupancy":2})"));

    warehouseInterface::ProductDescriptionJson productDescOnlyName(R"({"name": "Chocolate"})");
    auto item = coldRoomDepartment.getItem(productDescOnlyName);
    EXPECT_EQ(
            coldRoomDepartment.serialize(),
            std::string(
                    R"({"class":"ColdRoomDepartment","items":[{"class":"AstronautsIceCream","flags":["KEEP_DRY","KEEP_FROZEN"],"name":"Vanilla","size":0.5}],"maxOccupancy":20,"occupancy":0.5})"));
}

// ------------------------------------ SmallElectronicDepartment ------------------------------------
TEST(SmallElectronicDepartmentTest, ConstructorAndConfigurationTest)
{
    warehouse::SmallElectronicDepartment smallElectronicDepartment(150.0F);
    EXPECT_EQ(smallElectronicDepartment.getMaxOccupancy(), 150.0F);
    EXPECT_EQ(smallElectronicDepartment.getMaxItemSize(), 5.0);
    EXPECT_EQ(static_cast<uint32_t>(smallElectronicDepartment.getSupportedFlags()), 144);
}

TEST(SmallElectronicDepartmentTest, AddGetBasicTest)
{
    warehouse::SmallElectronicDepartment smallElectronicDepartment(10.0F);

    std::unique_ptr<warehouseInterface::IProduct> electronicPartsSTMPtr =
            std::make_unique<warehouse::ElectronicParts>("STM", 5.5F);
    std::unique_ptr<warehouseInterface::IProduct> electronicPartsArduinoPtr =
            std::make_unique<warehouse::ElectronicParts>("Arduino", 2.5F);
    std::unique_ptr<warehouseInterface::IProduct> electronicPartsResistorPtr =
            std::make_unique<warehouse::ElectronicParts>("Resistor", 1.0F);
    const auto productDesc = electronicPartsArduinoPtr->serialize();

    bool addStatus = false;
    addStatus = smallElectronicDepartment.addItem(std::move(electronicPartsSTMPtr));
    EXPECT_EQ(addStatus, false);
    addStatus = smallElectronicDepartment.addItem(std::move(electronicPartsArduinoPtr));
    EXPECT_EQ(addStatus, true);
    addStatus = smallElectronicDepartment.addItem(std::move(electronicPartsResistorPtr));
    EXPECT_EQ(addStatus, true);
    EXPECT_EQ(smallElectronicDepartment.getOccupancy(), 3.5F);

    auto item = smallElectronicDepartment.getItem(productDesc);
    EXPECT_EQ(item == nullptr, false);
    EXPECT_EQ(item->itemSize(), 2.5F);
    EXPECT_EQ(item->name(), std::string("Arduino"));
    EXPECT_EQ(smallElectronicDepartment.getOccupancy(), 1.0F);
}

// ------------------------------------ OverSizeElectronicDepartment ------------------------------------
TEST(OverSizeElectronicDepartmentTest, ConstructorAndConfigurationTest)
{
    warehouse::OverSizeElectronicDepartment overSizeElectronicDepartment(150.0F);
    EXPECT_EQ(overSizeElectronicDepartment.getMaxOccupancy(), 150.0F);
    EXPECT_EQ(overSizeElectronicDepartment.getMaxItemSize(), std::numeric_limits<float>().max());
    EXPECT_EQ(static_cast<uint32_t>(overSizeElectronicDepartment.getSupportedFlags()), 144);
}

TEST(OverSizeElectronicDepartmentTest, AddGetBasicTest)
{
    warehouse::OverSizeElectronicDepartment overSizeElectronicDepartment(10.0F);

    std::unique_ptr<warehouseInterface::IProduct> electronicPartsSTMPtr =
            std::make_unique<warehouse::ElectronicParts>("STM", 5.5F);
    std::unique_ptr<warehouseInterface::IProduct> electronicPartsArduinoPtr =
            std::make_unique<warehouse::ElectronicParts>("Arduino", 2.5F);
    std::unique_ptr<warehouseInterface::IProduct> electronicPartsResistorPtr =
            std::make_unique<warehouse::ElectronicParts>("Resistor", 1.0F);
    const auto productDesc = electronicPartsArduinoPtr->serialize();

    bool addStatus = false;
    addStatus = overSizeElectronicDepartment.addItem(std::move(electronicPartsSTMPtr));
    EXPECT_EQ(addStatus, true);
    addStatus = overSizeElectronicDepartment.addItem(std::move(electronicPartsArduinoPtr));
    EXPECT_EQ(addStatus, true);
    addStatus = overSizeElectronicDepartment.addItem(std::move(electronicPartsResistorPtr));
    EXPECT_EQ(addStatus, true);
    EXPECT_EQ(overSizeElectronicDepartment.getOccupancy(), 9.0F);

    auto item = overSizeElectronicDepartment.getItem(productDesc);
    EXPECT_EQ(item == nullptr, false);
    EXPECT_EQ(item->itemSize(), 2.5F);
    EXPECT_EQ(item->name(), std::string("Arduino"));
    EXPECT_EQ(overSizeElectronicDepartment.getOccupancy(), 6.5F);
}

// ------------------------------------ HazardousDepartment ------------------------------------
TEST(HazardousDepartmentTest, ConstructorAndConfigurationTest)
{
    warehouse::HazardousDepartment hazardousDepartment(100.0F);
    EXPECT_EQ(hazardousDepartment.getMaxOccupancy(), 100.0F);
    EXPECT_EQ(hazardousDepartment.getMaxItemSize(), std::numeric_limits<float>().max());
    EXPECT_EQ(static_cast<uint32_t>(hazardousDepartment.getSupportedFlags()), 19);
}

TEST(HazardousDepartmentTest, AddGetBasicTest)
{
    warehouse::HazardousDepartment hazardousDepartment(200.0F);

    std::unique_ptr<warehouseInterface::IProduct> acetoneBarrelSmallPtr =
            std::make_unique<warehouse::AcetoneBarrel>("Small Acetone Barrel", 25.0F);
    std::unique_ptr<warehouseInterface::IProduct> explosiveBarrelPtr =
            std::make_unique<warehouse::ExplosiveBarrel>("Explosive Barrel", 25.0F);
    std::unique_ptr<warehouseInterface::IProduct> acetoneBarrelBigPtr =
            std::make_unique<warehouse::AcetoneBarrel>("Big Acetone Barrel", 75.0F);
    const auto productDesc = acetoneBarrelSmallPtr->serialize();

    bool addStatus = false;
    addStatus = hazardousDepartment.addItem(std::move(acetoneBarrelSmallPtr));
    EXPECT_EQ(addStatus, true);
    addStatus = hazardousDepartment.addItem(std::move(explosiveBarrelPtr));
    EXPECT_EQ(addStatus, true);
    addStatus = hazardousDepartment.addItem(std::move(acetoneBarrelBigPtr));
    EXPECT_EQ(addStatus, true);
    EXPECT_EQ(hazardousDepartment.getOccupancy(), 125.0F);

    auto item = hazardousDepartment.getItem(productDesc);
    EXPECT_EQ(item == nullptr, false);
    EXPECT_EQ(item->itemSize(), 25.0F);
    EXPECT_EQ(item->name(), std::string("Small Acetone Barrel"));
    EXPECT_EQ(hazardousDepartment.getOccupancy(), 100.0F);
}

TEST(HazardousDepartmentTest, AddGetExtendedTest)
{
    warehouse::HazardousDepartment hazardousDepartment(200.0F);

    std::unique_ptr<warehouseInterface::IProduct> acetoneBarrelSmallPtr =
            std::make_unique<warehouse::AcetoneBarrel>("Small Acetone Barrel", 25.0F);
    std::unique_ptr<warehouseInterface::IProduct> explosiveBarrelPtr =
            std::make_unique<warehouse::ExplosiveBarrel>("Explosive Barrel", 25.0F);
    std::unique_ptr<warehouseInterface::IProduct> acetoneBarrelBigPtr =
            std::make_unique<warehouse::AcetoneBarrel>("Big Acetone Barrel", 75.0F);

    hazardousDepartment.addItem(std::move(acetoneBarrelSmallPtr));
    hazardousDepartment.addItem(std::move(explosiveBarrelPtr));
    hazardousDepartment.addItem(std::move(acetoneBarrelBigPtr));

    warehouseInterface::IProductPtr item;

    warehouseInterface::ProductDescriptionJson productDescSmallAcetoneBarrel(
            R"({"name": "Small Acetone Barrel", "class": "AcetoneBarrel"})");
    warehouseInterface::ProductDescriptionJson productDescExplosiveBarrel(
            R"({"name": "Explosive Barrel", "class": "ExplosiveBarrel"})");
    warehouseInterface::ProductDescriptionJson productDescBigAcetoneBarrel(
            R"({"name": "Big Acetone Barrel", "class": "AcetoneBarrel"})");

    item = hazardousDepartment.getItem(productDescExplosiveBarrel);
    EXPECT_EQ(item == nullptr, true);

    item = hazardousDepartment.getItem(productDescBigAcetoneBarrel);
    EXPECT_EQ(item == nullptr, true);

    item = hazardousDepartment.getItem(productDescSmallAcetoneBarrel);
    EXPECT_EQ(item == nullptr, false);
    EXPECT_EQ(item->itemSize(), 25.0F);
    EXPECT_EQ(item->name(), std::string("Small Acetone Barrel"));
    EXPECT_EQ(hazardousDepartment.getOccupancy(), 100.0F);

    warehouseInterface::ProductDescriptionJson productDescOnlyClass(R"({"class": "ExplosiveBarrel"})");
    item = hazardousDepartment.getItem(productDescOnlyClass);
    EXPECT_EQ(item == nullptr, false);
    EXPECT_EQ(item->itemSize(), 25.0F);
    EXPECT_EQ(item->name(), std::string("Explosive Barrel"));
    EXPECT_EQ(dynamic_cast<warehouse::ExplosiveBarrel *>(item.get()) != nullptr, true);
    EXPECT_EQ(hazardousDepartment.getOccupancy(), 75.0F);

    warehouseInterface::ProductDescriptionJson productDescOnlyNameNotExisting(R"({"name": "Strawberry"})");
    item = hazardousDepartment.getItem(productDescOnlyNameNotExisting);
    EXPECT_EQ(item == nullptr, true);

    warehouseInterface::ProductDescriptionJson productDescOnlyClassNotExisting(R"({"class": "ElectronicParts"})");
    item = hazardousDepartment.getItem(productDescOnlyNameNotExisting);
    EXPECT_EQ(item == nullptr, true);

    warehouseInterface::ProductDescriptionJson productDescOnlyName(R"({"name": "Big Acetone Barrel"})");
    item = hazardousDepartment.getItem(productDescOnlyName);
    EXPECT_EQ(item == nullptr, false);
    EXPECT_EQ(item->itemSize(), 75.0F);
    EXPECT_EQ(item->name(), std::string("Big Acetone Barrel"));
    EXPECT_EQ(dynamic_cast<warehouse::AcetoneBarrel *>(item.get()) != nullptr, true);
    EXPECT_EQ(hazardousDepartment.getOccupancy(), 0.0F);
}

TEST(HazardousDepartmentTest, SerializeTest)
{
    warehouse::HazardousDepartment hazardousDepartment(200.0F);

    std::unique_ptr<warehouseInterface::IProduct> acetoneBarrelSmallPtr =
            std::make_unique<warehouse::AcetoneBarrel>("Small Acetone Barrel", 25.0F);
    std::unique_ptr<warehouseInterface::IProduct> explosiveBarrelPtr =
            std::make_unique<warehouse::ExplosiveBarrel>("Explosive Barrel", 25.0F);

    warehouseInterface::ProductDescriptionJson productDescSmallAcetoneBarrel(
            R"({"name": "Small Acetone Barrel", "class": "AcetoneBarrel"})");
    warehouseInterface::ProductDescriptionJson productDescExplosiveBarrel(
            R"({"name": "Explosive Barrel", "class": "ExplosiveBarrel"})");

    hazardousDepartment.addItem(std::move(acetoneBarrelSmallPtr));
    EXPECT_EQ(
            hazardousDepartment.serialize(),
            std::string(
                    R"({"class":"HazardousDepartment","items":[{"class":"AcetoneBarrel","flags":["FIRE_HAZARDOUS","ESD_SENSITIVE"],"name":"Small Acetone Barrel","size":25}],"maxOccupancy":200,"occupancy":25})"));

    hazardousDepartment.addItem(std::move(explosiveBarrelPtr));
    EXPECT_EQ(
            hazardousDepartment.serialize(),
            std::string(
                    R"({"class":"HazardousDepartment","items":[{"class":"AcetoneBarrel","flags":["FIRE_HAZARDOUS","ESD_SENSITIVE"],"name":"Small Acetone Barrel","size":25},{"class":"ExplosiveBarrel","flags":["EXPLOSIVES","HANDLE_WITH_CARE"],"name":"Explosive Barrel","size":25}],"maxOccupancy":200,"occupancy":50})"));

    warehouseInterface::IProductPtr item;

    item = hazardousDepartment.getItem(productDescSmallAcetoneBarrel);
    EXPECT_EQ(
            hazardousDepartment.serialize(),
            std::string(
                    R"({"class":"HazardousDepartment","items":[{"class":"ExplosiveBarrel","flags":["EXPLOSIVES","HANDLE_WITH_CARE"],"name":"Explosive Barrel","size":25}],"maxOccupancy":200,"occupancy":25})"));

    item = hazardousDepartment.getItem(productDescExplosiveBarrel);
    EXPECT_EQ(hazardousDepartment.serialize(),
              std::string(R"({"class":"HazardousDepartment","items":[],"maxOccupancy":200,"occupancy":0})"));
}

// ------------------------------------ SpecialDepartment ------------------------------------
TEST(SpecialDepartmentTest, ConstructorAndConfigurationTest)
{
    warehouse::SpecialDepartment specialDepartment(100.0F);
    EXPECT_EQ(specialDepartment.getMaxOccupancy(), 100.0);
    EXPECT_EQ(specialDepartment.getMaxItemSize(), std::numeric_limits<float>().max());
    EXPECT_EQ(static_cast<uint32_t>(specialDepartment.getSupportedFlags()), 60);
}

TEST(SpecialDepartmentTest, AddGetBasicTest)
{
    warehouse::SpecialDepartment specialDepartment(200.0F);

    std::unique_ptr<warehouseInterface::IProduct> glassWareSmallPtr =
            std::make_unique<warehouse::GlassWare>("Small Glass Ware", 25.0F);
    std::unique_ptr<warehouseInterface::IProduct> serverRackPtr =
            std::make_unique<warehouse::IndustrialServerRack>("Server Rack", 25.0F);
    std::unique_ptr<warehouseInterface::IProduct> glassWareBigPtr =
            std::make_unique<warehouse::GlassWare>("Big Glass Ware", 75.0F);
    const auto productDesc = glassWareBigPtr->serialize();

    bool addStatus = false;
    addStatus = specialDepartment.addItem(std::move(glassWareSmallPtr));
    EXPECT_EQ(addStatus, true);
    addStatus = specialDepartment.addItem(std::move(serverRackPtr));
    EXPECT_EQ(addStatus, true);
    addStatus = specialDepartment.addItem(std::move(glassWareBigPtr));
    EXPECT_EQ(addStatus, true);
    EXPECT_EQ(specialDepartment.getOccupancy(), 125.0F);

    auto item = specialDepartment.getItem(productDesc);
    EXPECT_EQ(item == nullptr, false);
    EXPECT_EQ(item->itemSize(), 75.0F);
    EXPECT_EQ(item->name(), std::string("Big Glass Ware"));
    EXPECT_EQ(specialDepartment.getOccupancy(), 50.0F);
}

TEST(SpecialDepartmentTest, AddGetExtendedTest)
{
    warehouse::SpecialDepartment specialDepartment(200.0F);

    std::unique_ptr<warehouseInterface::IProduct> glassWareSmallPtr =
            std::make_unique<warehouse::GlassWare>("Small Glass Ware", 25.0F);
    std::unique_ptr<warehouseInterface::IProduct> serverRackPtr =
            std::make_unique<warehouse::IndustrialServerRack>("Server Rack", 25.0F);
    std::unique_ptr<warehouseInterface::IProduct> glassWareBigPtr =
            std::make_unique<warehouse::GlassWare>("Big Glass Ware", 75.0F);

    specialDepartment.addItem(std::move(glassWareSmallPtr));
    specialDepartment.addItem(std::move(serverRackPtr));
    specialDepartment.addItem(std::move(glassWareBigPtr));

    warehouseInterface::IProductPtr item;

    warehouseInterface::ProductDescriptionJson productDescSmallGlassWare(
            R"({"name": "Small Glass Ware", "class": "GlassWare"})");
    warehouseInterface::ProductDescriptionJson productDescIndustrialServerRack(
            R"({"name": "Server Rack", "class": "IndustrialServerRack"})");
    warehouseInterface::ProductDescriptionJson productDescBigGlassWare(R"({"name": "Big Glass Ware", "class": "GlassWare"})");

    item = specialDepartment.getItem(productDescIndustrialServerRack);
    EXPECT_EQ(item == nullptr, true);

    item = specialDepartment.getItem(productDescSmallGlassWare);
    EXPECT_EQ(item == nullptr, true);

    item = specialDepartment.getItem(productDescBigGlassWare);
    EXPECT_EQ(item == nullptr, false);
    EXPECT_EQ(item->itemSize(), 75.0F);
    EXPECT_EQ(item->name(), std::string("Big Glass Ware"));
    EXPECT_EQ(specialDepartment.getOccupancy(), 50.0F);

    warehouseInterface::ProductDescriptionJson productDescOnlyClass(R"({"class": "IndustrialServerRack"})");
    item = specialDepartment.getItem(productDescOnlyClass);
    EXPECT_EQ(item == nullptr, false);
    EXPECT_EQ(item->itemSize(), 25.0F);
    EXPECT_EQ(item->name(), std::string("Server Rack"));
    EXPECT_EQ(dynamic_cast<warehouse::IndustrialServerRack *>(item.get()) != nullptr, true);
    EXPECT_EQ(specialDepartment.getOccupancy(), 25.0F);

    warehouseInterface::ProductDescriptionJson productDescOnlyNameNotExisting(R"({"name": "Strawberry"})");
    item = specialDepartment.getItem(productDescOnlyNameNotExisting);
    EXPECT_EQ(item == nullptr, true);

    warehouseInterface::ProductDescriptionJson productDescOnlyClassNotExisting(R"({"class": "ElectronicParts"})");
    item = specialDepartment.getItem(productDescOnlyNameNotExisting);
    EXPECT_EQ(item == nullptr, true);

    warehouseInterface::ProductDescriptionJson productDescOnlyName(R"({"name": "Small Glass Ware"})");
    item = specialDepartment.getItem(productDescOnlyName);
    EXPECT_EQ(item == nullptr, false);
    EXPECT_EQ(item->itemSize(), 25.0F);
    EXPECT_EQ(item->name(), std::string("Small Glass Ware"));
    EXPECT_EQ(dynamic_cast<warehouse::GlassWare *>(item.get()) != nullptr, true);
    EXPECT_EQ(specialDepartment.getOccupancy(), 0.0F);
}

TEST(SpecialDepartmentTest, SerializeTest)
{
    warehouse::SpecialDepartment specialDepartment(200.0F);

    std::unique_ptr<warehouseInterface::IProduct> glassWareSmallPtr =
            std::make_unique<warehouse::GlassWare>("Small Glass Ware", 25.0F);
    std::unique_ptr<warehouseInterface::IProduct> serverRackPtr =
            std::make_unique<warehouse::IndustrialServerRack>("Server Rack", 25.0F);

    warehouseInterface::ProductDescriptionJson productDescSmallGlassWare(
            R"({"name": "Small Glass Ware", "class": "GlassWare"})");
    warehouseInterface::ProductDescriptionJson productDescIndustrialServerRack(
            R"({"name": "Server Rack", "class": "IndustrialServerRack"})");

    specialDepartment.addItem(std::move(glassWareSmallPtr));
    EXPECT_EQ(
            specialDepartment.serialize(),
            std::string(
                    R"({"class":"SpecialDepartment","items":[{"class":"GlassWare","flags":["FRAGILE","UPWARD"],"name":"Small Glass Ware","size":25}],"maxOccupancy":200,"occupancy":25})"));

    specialDepartment.addItem(std::move(serverRackPtr));
    EXPECT_EQ(
            specialDepartment.serialize(),
            std::string(
                    R"({"class":"SpecialDepartment","items":[{"class":"GlassWare","flags":["FRAGILE","UPWARD"],"name":"Small Glass Ware","size":25},{"class":"IndustrialServerRack","flags":["UPWARD","KEEP_DRY","HANDLE_WITH_CARE","ESD_SENSITIVE"],"name":"Server Rack","size":25}],"maxOccupancy":200,"occupancy":50})"));

    warehouseInterface::IProductPtr item;

    item = specialDepartment.getItem(productDescIndustrialServerRack);
    EXPECT_EQ(
            specialDepartment.serialize(),
            std::string(
                    R"({"class":"SpecialDepartment","items":[{"class":"GlassWare","flags":["FRAGILE","UPWARD"],"name":"Small Glass Ware","size":25}],"maxOccupancy":200,"occupancy":25})"));

    item = specialDepartment.getItem(productDescSmallGlassWare);
    EXPECT_EQ(specialDepartment.serialize(),
              std::string(R"({"class":"SpecialDepartment","items":[],"maxOccupancy":200,"occupancy":0})"));
}

}  // namespace warehouse