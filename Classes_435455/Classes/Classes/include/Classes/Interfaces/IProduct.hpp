#pragma once
#include <Classes/PicoJson/picojson.h>

#include <Classes/Interfaces/ProductFlags.hpp>
#include <memory>
#include <string>

namespace classesInterface
{
class IProduct;
using IProductPtr = std::unique_ptr<IProduct>;
using ProductDescriptionJson = std::string;

class IProduct
{
public:
    virtual ~IProduct() = default;

    IProduct() = default;
    IProduct(const IProduct &) = delete;
    IProduct &operator=(const IProduct &) = delete;
    IProduct(IProduct &&) = delete;
    IProduct &operator=(IProduct &&) = delete;

    /**
     * @brief Get the name of the product.
     * @return A string representing the name of the product.
     */
    virtual std::string name() const = 0;

    /**
     * @brief Get the size of the product.
     * @return A float representing the size of the product.
     */
    virtual float itemSize() const = 0;

    /**
     * @brief Get the flags associated with the product.
     * @return A ProductLabelFlags enum value representing the flags associated with the product.
     */
    virtual ProductLabelFlags itemFlags() const = 0;

    /**
     * @brief Function which convert product parameters to JSON object.
     * @return A JSON representing the product.
     */
    virtual picojson::object asJson() const = 0;

    /**
     * @brief Serialize the product to a JSON string.
     * @return A JSON string representing the serialized product.
     */
    virtual ProductDescriptionJson serialize() const = 0;
};
}  // namespace classesInterface