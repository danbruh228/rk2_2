#ifndef BUSINESSSYSTEM_H
#define BUSINESSSYSTEM_H

#include <cstdint>
#include <stdexcept>

// Define design namespace and AccessKey template
namespace design {
    template<typename T>
    class AccessKey {
        friend T;
        AccessKey() {} // Ensure this is defined appropriately
    };
}

class BusinessMediator;

// EstateOwner Class
class EstateOwner {
public:
    BusinessMediator* SetBusinessMediator(design::AccessKey<BusinessMediator>, BusinessMediator* mediator);
    void SetEstateRentPrice(std::int32_t newPrice);
private:
    BusinessMediator* mediator_ = nullptr;
    std::int32_t rentPrice_ = 0;
};

// GroceryStore Class
class GroceryStore {
public:
    BusinessMediator* SetBusinessMediator(design::AccessKey<BusinessMediator>, BusinessMediator* mediator);
    void Supply(std::int32_t quantity);
    std::int32_t AlterPrice(std::int32_t priceChange);
    void Sell();
private:
    BusinessMediator* mediator_ = nullptr;
    std::int32_t stock_ = 0;
    std::int32_t price_ = 0;
};

// Restaurant Class
class Restaurant {
public:
    BusinessMediator* SetBusinessMediator(design::AccessKey<BusinessMediator>, BusinessMediator* mediator);
    void SetIsOpened(design::AccessKey<BusinessMediator>, bool isOpened);
    std::int32_t CookFood();
    std::int32_t AlterPrice(std::int32_t priceChange);
private:
    BusinessMediator* mediator_ = nullptr;
    bool isOpened_ = false;
    std::int32_t price_ = 0;
};

// BusinessMediator Class
class BusinessMediator {
public:
    BusinessMediator(EstateOwner& estateOwner, GroceryStore& groceryStore, Restaurant& restaurant);

    void EstateRentPriceChanged(std::int32_t oldPrice, std::int32_t newPrice);
    void GroceryStockChanged(std::int32_t newStock);
    void GroceryPriceChanged(std::int32_t oldPrice, std::int32_t newPrice);
    void FoodIsCooked();

private:
    EstateOwner& estateOwner_;
    GroceryStore& groceryStore_;
    Restaurant& restaurant_;
};

#endif // BUSINESSSYSTEM_H

