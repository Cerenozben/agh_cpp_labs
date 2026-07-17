#pragma once
#include <Classes/Interfaces/IProduct.hpp>
#include <Classes/MagicEnum/magic_enum.hpp>
#include <Classes/Products/BasicProduct.hpp>
#include <Classes/Products/ProductsList.hpp>
#include <functional>
#include <memory>
#include <unordered_map>

namespace warehouse
{
class ProductFactory
{
public:
    classesInterface::IProductPtr createProduct(const std::string &className, const std::string &name, const float size) const
    {
        const auto it = productRegistry_.find(className);
        if (it == productRegistry_.end())
        {
            throw std::runtime_error("Unknown product class: " + className);
        }
        return it->second(name, size);
    }

private:
    using ProductRegistry =
            std::unordered_map<std::string, std::function<classesInterface::IProductPtr(const std::string &, const float)>>;

    const ProductRegistry productRegistry_{
            {"IndustrialServerRack",
             [](const std::string &name, const float size) {
                 return std::make_unique<classes::IndustrialServerRack>(name, size);
             }},
            {"GlassWare",
             [](const std::string &name, const float size) { return std::make_unique<classes::GlassWare>(name, size); }},
            {"ExplosiveBarrel",
             [](const std::string &name, const float size) { return std::make_unique<classes::ExplosiveBarrel>(name, size); }},
            {"ElectronicParts",
             [](const std::string &name, const float size) { return std::make_unique<classes::ElectronicParts>(name, size); }},
            {"AstronautsIceCream",
             [](const std::string &name, const float size) {
                 return std::make_unique<classes::AstronautsIceCream>(name, size);
             }},
            {"AcetoneBarrel",
             [](const std::string &name, const float size) { return std::make_unique<classes::AcetoneBarrel>(name, size); }},
            {"TV", [](const std::string &name, const float size) { return std::make_unique<classes::TV>(name, size); }},

    };
};

}  // namespace warehouse