
#include <Classes/PicoJson/picojson.h>
#include <gtest/gtest.h>

#include <Classes/Products/ProductsList.hpp>

namespace classes
{
TEST(TVTest, SerializesToJson)
{
    classes::TV tv("Sony Bravia", 50.0F);

    picojson::value jsonValue;
    std::string err = picojson::parse(jsonValue, tv.serialize());
    EXPECT_TRUE(err.empty());

    picojson::object json = jsonValue.get<picojson::object>();

    EXPECT_TRUE(json["name"].is<std::string>());
    EXPECT_EQ(json["name"].get<std::string>(), "Sony Bravia");
    EXPECT_TRUE(json["name"].is<std::string>());
    EXPECT_EQ(json["name"].get<std::string>(), "Sony Bravia");
    EXPECT_TRUE(json["flags"].is<picojson::array>());
    EXPECT_EQ(json["flags"].serialize(), R"(["FRAGILE","KEEP_DRY"])");
    EXPECT_TRUE(json["class"].is<std::string>());
    EXPECT_EQ(json["class"].get<std::string>(), "TV");
    EXPECT_TRUE(json["size"].is<double>());
    EXPECT_EQ(json["size"].get<double>(), 50.0);
}

TEST(TVTest, ReturnsCorrectFlags)
{
    classes::TV tv("Sony Bravia", 50.0F);
    auto flags = tv.itemFlags();

    using magic_enum::bitwise_operators::operator&;
    EXPECT_TRUE((flags & classesInterface::ProductLabelFlags::FRAGILE) == classesInterface::ProductLabelFlags::FRAGILE);
    EXPECT_TRUE((flags & classesInterface::ProductLabelFlags::KEEP_DRY) == classesInterface::ProductLabelFlags::KEEP_DRY);
}

TEST(TVTest, NameAndSizeTest)
{
    const std::string name{"Sony Bravia"};
    const float size{50.0F};

    classes::TV tv{name, size};
    EXPECT_EQ(tv.name(), name);
    EXPECT_EQ(tv.itemSize(), size);
}

TEST(AcetoneBarrelTest, SerializesToJson)
{
    AcetoneBarrel barrel("Acetone Barrel", 200.0F);
    picojson::value jsonValue;
    std::string err = picojson::parse(jsonValue, barrel.serialize());
    EXPECT_TRUE(err.empty());

    picojson::object json = jsonValue.get<picojson::object>();

    EXPECT_TRUE(json["name"].is<std::string>());
    EXPECT_EQ(json["name"].get<std::string>(), "Acetone Barrel");
    EXPECT_TRUE(json["flags"].is<picojson::array>());
    EXPECT_EQ(json["flags"].serialize(), R"(["FIRE_HAZARDOUS","ESD_SENSITIVE"])");
    EXPECT_TRUE(json["class"].is<std::string>());
    EXPECT_EQ(json["class"].get<std::string>(), "AcetoneBarrel");
    EXPECT_TRUE(json["size"].is<double>());
    EXPECT_EQ(json["size"].get<double>(), 200.0);
}

TEST(AcetoneBarrelTest, ReturnsCorrectFlags)
{
    AcetoneBarrel barrel("Acetone Barrel", 200.0F);
    auto flags = barrel.itemFlags();

    using magic_enum::bitwise_operators::operator&;
    EXPECT_TRUE((flags & classesInterface::ProductLabelFlags::FIRE_HAZARDOUS) ==
                classesInterface::ProductLabelFlags::FIRE_HAZARDOUS);
    EXPECT_TRUE((flags & classesInterface::ProductLabelFlags::ESD_SENSITIVE) ==
                classesInterface::ProductLabelFlags::ESD_SENSITIVE);
}

TEST(AcetoneBarrelTest, NameAndSizeTest)
{
    const std::string name{"Acetone Barrel"};
    const float size{200.0F};

    AcetoneBarrel barrel{name, size};
    EXPECT_EQ(barrel.name(), name);
    EXPECT_EQ(barrel.itemSize(), size);
}

TEST(AstronautsIceCreamTest, SerializesToJson)
{
    classes::AstronautsIceCream astronautsIceCream("Chocolate", 0.5F);
    picojson::value jsonValue;
    std::string err = picojson::parse(jsonValue, astronautsIceCream.serialize());
    EXPECT_TRUE(err.empty());

    picojson::object json = jsonValue.get<picojson::object>();

    EXPECT_TRUE(json["name"].is<std::string>());
    EXPECT_EQ(json["name"].get<std::string>(), "Chocolate");
    EXPECT_TRUE(json["flags"].is<picojson::array>());
    EXPECT_EQ(json["flags"].serialize(), R"(["KEEP_DRY","KEEP_FROZEN"])");
    EXPECT_TRUE(json["class"].is<std::string>());
    EXPECT_EQ(json["class"].get<std::string>(), "AstronautsIceCream");
    EXPECT_TRUE(json["size"].is<double>());
    EXPECT_EQ(json["size"].get<double>(), 0.5F);
}

TEST(AstronautsIceCreamTest, ReturnsCorrectFlags)
{
    classes::AstronautsIceCream astronautsIceCream("Vanilla", 0.5F);
    auto flags = astronautsIceCream.itemFlags();

    using magic_enum::bitwise_operators::operator&;
    EXPECT_TRUE((flags & classesInterface::ProductLabelFlags::KEEP_FROZEN) == classesInterface::ProductLabelFlags::KEEP_FROZEN);
    EXPECT_TRUE((flags & classesInterface::ProductLabelFlags::KEEP_DRY) == classesInterface::ProductLabelFlags::KEEP_DRY);
}

TEST(AstronautsIceCreamTest, NameAndSizeTest)
{
    const std::string name{"Strawberry"};
    const float size{1.5F};

    classes::AstronautsIceCream astronautsIceCream{name, size};
    EXPECT_EQ(astronautsIceCream.name(), name);
    EXPECT_EQ(astronautsIceCream.itemSize(), size);
}

TEST(ElectronicPartsTest, SerializesToJson)
{
    ElectronicParts electronicParts("Resistor", 0.01F);
    picojson::value jsonValue;
    std::string err = picojson::parse(jsonValue, electronicParts.serialize());
    EXPECT_TRUE(err.empty());

    picojson::object json = jsonValue.get<picojson::object>();

    EXPECT_TRUE(json["name"].is<std::string>());
    EXPECT_EQ(json["name"].get<std::string>(), "Resistor");
    EXPECT_TRUE(json["flags"].is<picojson::array>());
    EXPECT_EQ(json["flags"].serialize(), R"(["KEEP_DRY","ESD_SENSITIVE"])");
    EXPECT_TRUE(json["class"].is<std::string>());
    EXPECT_EQ(json["class"].get<std::string>(), "ElectronicParts");
    EXPECT_TRUE(json["size"].is<double>());
    EXPECT_EQ(json["size"].get<double>(), 0.01F);
}

TEST(ElectronicPartsTest, ReturnsCorrectFlags)
{
    ElectronicParts electronicParts("Resistor", 0.01F);
    auto flags = electronicParts.itemFlags();

    using magic_enum::bitwise_operators::operator&;
    EXPECT_TRUE((flags & classesInterface::ProductLabelFlags::KEEP_DRY) == classesInterface::ProductLabelFlags::KEEP_DRY);
    EXPECT_TRUE((flags & classesInterface::ProductLabelFlags::ESD_SENSITIVE) ==
                classesInterface::ProductLabelFlags::ESD_SENSITIVE);
}

TEST(ElectronicPartsTest, NameAndSizeTest)
{
    const std::string name{"Resistor"};
    const float size{0.01F};

    ElectronicParts electronicParts{name, size};
    EXPECT_EQ(electronicParts.name(), name);
    EXPECT_EQ(electronicParts.itemSize(), size);
}
TEST(ExplosiveBarrelTest, SerializesToJson)
{
    classes::ExplosiveBarrel explosiveBarrel("TNT", 1.5F);
    picojson::value jsonValue;
    std::string err = picojson::parse(jsonValue, explosiveBarrel.serialize());
    EXPECT_TRUE(err.empty());

    picojson::object json = jsonValue.get<picojson::object>();

    EXPECT_TRUE(json["name"].is<std::string>());
    EXPECT_EQ(json["name"].get<std::string>(), "TNT");
    EXPECT_TRUE(json["flags"].is<picojson::array>());
    EXPECT_EQ(json["flags"].serialize(), R"(["EXPLOSIVES","HANDLE_WITH_CARE"])");
    EXPECT_TRUE(json["class"].is<std::string>());
    EXPECT_EQ(json["class"].get<std::string>(), "ExplosiveBarrel");
    EXPECT_TRUE(json["size"].is<double>());
    EXPECT_EQ(json["size"].get<double>(), 1.5F);
}

TEST(ExplosiveBarrelTest, ReturnsCorrectFlags)
{
    classes::ExplosiveBarrel explosiveBarrel("Dynamite", 2.5F);
    auto flags = explosiveBarrel.itemFlags();

    using magic_enum::bitwise_operators::operator&;
    EXPECT_TRUE((flags & classesInterface::ProductLabelFlags::EXPLOSIVES) == classesInterface::ProductLabelFlags::EXPLOSIVES);
    EXPECT_TRUE((flags & classesInterface::ProductLabelFlags::HANDLE_WITH_CARE) ==
                classesInterface::ProductLabelFlags::HANDLE_WITH_CARE);
}

TEST(ExplosiveBarrelTest, NameAndSizeTest)
{
    const std::string name{"C4"};
    const float size{3.5F};

    classes::ExplosiveBarrel explosiveBarrel{name, size};
    EXPECT_EQ(explosiveBarrel.name(), name);
    EXPECT_EQ(explosiveBarrel.itemSize(), size);
}
TEST(GlassWareTest, SerializesToJson)
{
    classes::GlassWare glassWare("Wine Glass", 0.2F);

    picojson::value jsonValue;
    std::string err = picojson::parse(jsonValue, glassWare.serialize());
    EXPECT_TRUE(err.empty());

    picojson::object json = jsonValue.get<picojson::object>();

    EXPECT_TRUE(json["name"].is<std::string>());
    EXPECT_EQ(json["name"].get<std::string>(), "Wine Glass");
    EXPECT_TRUE(json["flags"].is<picojson::array>());
    EXPECT_EQ(json["flags"].serialize(), R"(["FRAGILE","UPWARD"])");
    EXPECT_TRUE(json["class"].is<std::string>());
    EXPECT_EQ(json["class"].get<std::string>(), "GlassWare");
    EXPECT_TRUE(json["size"].is<double>());
    EXPECT_EQ(json["size"].get<double>(), 0.2F);
}

TEST(GlassWareTest, ReturnsCorrectFlags)
{
    classes::GlassWare glassWare("Water Glass", 0.1F);
    auto flags = glassWare.itemFlags();

    using magic_enum::bitwise_operators::operator&;
    EXPECT_TRUE((flags & classesInterface::ProductLabelFlags::FRAGILE) == classesInterface::ProductLabelFlags::FRAGILE);
    EXPECT_TRUE((flags & classesInterface::ProductLabelFlags::UPWARD) == classesInterface::ProductLabelFlags::UPWARD);
}

TEST(GlassWareTest, NameAndSizeTest)
{
    const std::string name{"Beer Glass"};
    const float size{0.3F};

    classes::GlassWare glassWare{name, size};
    EXPECT_EQ(glassWare.name(), name);
    EXPECT_EQ(glassWare.itemSize(), size);
}

TEST(IndustrialServerRackTest, SerializesToJson)
{
    classes::IndustrialServerRack rack("Rack01", 2.5F);

    picojson::value jsonValue;
    std::string err = picojson::parse(jsonValue, rack.serialize());
    EXPECT_TRUE(err.empty());

    picojson::object json = jsonValue.get<picojson::object>();

    EXPECT_TRUE(json["name"].is<std::string>());
    EXPECT_EQ(json["name"].get<std::string>(), "Rack01");
    EXPECT_TRUE(json["flags"].is<picojson::array>());
    EXPECT_EQ(json["flags"].serialize(), R"(["UPWARD","KEEP_DRY","HANDLE_WITH_CARE","ESD_SENSITIVE"])");
    EXPECT_TRUE(json["class"].is<std::string>());
    EXPECT_EQ(json["class"].get<std::string>(), "IndustrialServerRack");
    EXPECT_TRUE(json["size"].is<double>());
    EXPECT_EQ(json["size"].get<double>(), 2.5F);
}

TEST(IndustrialServerRackTest, ReturnsCorrectFlags)
{
    classes::IndustrialServerRack rack("Rack02", 3.0F);
    auto flags = rack.itemFlags();

    using magic_enum::bitwise_operators::operator&;
    EXPECT_TRUE((flags & classesInterface::ProductLabelFlags::HANDLE_WITH_CARE) ==
                classesInterface::ProductLabelFlags::HANDLE_WITH_CARE);
    EXPECT_TRUE((flags & classesInterface::ProductLabelFlags::ESD_SENSITIVE) ==
                classesInterface::ProductLabelFlags::ESD_SENSITIVE);
    EXPECT_TRUE((flags & classesInterface::ProductLabelFlags::UPWARD) == classesInterface::ProductLabelFlags::UPWARD);
    EXPECT_TRUE((flags & classesInterface::ProductLabelFlags::KEEP_DRY) == classesInterface::ProductLabelFlags::KEEP_DRY);
}

TEST(IndustrialServerRackTest, NameAndSizeTest)
{
    const std::string name{"Rack03"};
    const float size{4.0F};

    classes::IndustrialServerRack rack{name, size};
    EXPECT_EQ(rack.name(), name);
    EXPECT_EQ(rack.itemSize(), size);
}

}  // namespace classes