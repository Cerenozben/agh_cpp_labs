#include <PicoJson/picojson.h>

#include <Interfaces/IWarehouse.hpp>
#include <Interfaces/ProductFlags.hpp>
namespace warehouse
{
class Warehouse : public warehouseInterface::IWarehouse
{
    // student code begin
private:
    static bool hasFlag(warehouseInterface::ProductLabelFlags itemFlags, warehouseInterface::ProductLabelFlags targetFlag);
    static std::string getTargetDepartmentName(const warehouseInterface::IProductPtr &item);

public:
    Warehouse() = default;
    ~Warehouse() override = default;

    Warehouse(const Warehouse &) = delete;
    Warehouse &operator=(const Warehouse &) = delete;
    Warehouse(Warehouse &&) = delete;
    Warehouse &operator=(Warehouse &&) = delete;

    void addDepartment(warehouseInterface::IDepartmentPtr dept) override;
    warehouseInterface::DeliveryReportJson newDelivery(std::vector<warehouseInterface::IProductPtr> delivery) override;
    warehouseInterface::Order newOrder(const warehouseInterface::OrderJson &orderJson) override;
    warehouseInterface::OccupancyReportJson getOccupancyReport() const override;
    warehouseInterface::WarehouseStateJson saveWarehouseState() const override;
    bool loadWarehouseState(const warehouseInterface::WarehouseStateJson &stateJson) override;
    // student code end
};

}  // namespace warehouse