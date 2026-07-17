#pragma once
#include <string>
#include <vector>

#include "Interfaces/Aliases.hpp"
#include "Interfaces/IDepartment.hpp"
#include "Interfaces/IProduct.hpp"
#include "Interfaces/ProductFlags.hpp"
namespace warehouseInterface
{

class OverSizeElectronicDepartment : public IDepartment
{
private:
    std::vector<IProductPtr> items_;

public:
    explicit OverSizeElectronicDepartment(float maxOccupancy);

    bool addItem(IProductPtr item) override;
    IProductPtr getItem(const ProductDescriptionJson &desc) override;

    float getOccupancy() const override;
    float getMaxOccupancy() const override;
    float getMaxItemSize() const override;
    ProductLabelFlags getSupportedFlags() const override;
    picojson::object asJson() const override;
    DepartmentStateJson serialize() const override;
    picojson::array serializedItems() const override;
    std::string departmentName() const override;
};
}  // namespace warehouseInterface