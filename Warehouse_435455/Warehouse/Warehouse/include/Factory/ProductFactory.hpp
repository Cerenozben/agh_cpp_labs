#pragma once
#include <Interfaces/IProduct.hpp>
#include <MagicEnum/magic_enum.hpp>
#include <Products/BasicProduct.hpp>
#include <Products/ProductsList.hpp>
#include <functional>
#include <memory>
#include <unordered_map>

namespace warehouse
{
class ProductFactory
{
public:
    warehouseInterface::IProductPtr createProduct(const std::string &className, const std::string &name, const float size) const
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
            std::unordered_map<std::string, std::function<std::unique_ptr<BasicProduct>(const std::string &, const float)>>;

    const ProductRegistry productRegistry_{
            {"IndustrialServerRack",
             [](const std::string &name, const float size) {
                 return std::make_unique<warehouse::IndustrialServerRack>(name, size);
             }},
            {"GlassWare",
             [](const std::string &name, const float size) { return std::make_unique<warehouse::GlassWare>(name, size); }},
            {"ExplosiveBarrel",
             [](const std::string &name, const float size) {
                 return std::make_unique<warehouse::ExplosiveBarrel>(name, size);
             }},
            {"ElectronicParts",
             [](const std::string &name, const float size) {
                 return std::make_unique<warehouse::ElectronicParts>(name, size);
             }},
            {"AstronautsIceCream",
             [](const std::string &name, const float size) {
                 return std::make_unique<warehouse::AstronautsIceCream>(name, size);
             }},
            {"AcetoneBarrel",
             [](const std::string &name, const float size) { return std::make_unique<warehouse::AcetoneBarrel>(name, size); }},
            {"TV", [](const std::string &name, const float size) { return std::make_unique<warehouse::TV>(name, size); }},

    };
};

}  // namespace warehouse