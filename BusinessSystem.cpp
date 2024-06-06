 #include "BusinessSystem.h"

// Implementations for EstateOwner
BusinessMediator* EstateOwner::SetBusinessMediator(design::AccessKey<BusinessMediator>, BusinessMediator* mediator) {
    BusinessMediator* old = mediator_;
    mediator_ = mediator;
    return old;
}

void EstateOwner::SetEstateRentPrice(std::int32_t newPrice) {
    if (mediator_) mediator_->EstateRentPriceChanged(rentPrice_, newPrice);
    rentPrice_ = newPrice;
}

// Implementations for GroceryStore
BusinessMediator* GroceryStore::SetBusinessMediator(design::AccessKey<BusinessMediator>, BusinessMediator* mediator) {
    BusinessMediator* old = mediator_;
    mediator_ = mediator;
    return old;
}

void GroceryStore::Supply(std::int32_t quantity) {
    stock_ += quantity;
    if (mediator_) mediator_->GroceryStockChanged(stock_);
}

std::int32_t GroceryStore::AlterPrice(std::int32_t priceChange) {
    price_ += priceChange;
    return price_;
}

void GroceryStore::Sell() {
    if (stock_ <= 0) throw std::logic_error("Out of stock");
    stock_--;
}

// Implementations for Restaurant
BusinessMediator* Restaurant::SetBusinessMediator(design::AccessKey<BusinessMediator>, BusinessMediator* mediator) {
    BusinessMediator* old = mediator_;
    mediator_ = mediator;
    return old;
}

void Restaurant::SetIsOpened(design::AccessKey<BusinessMediator>, bool isOpened) {
    isOpened_ = isOpened;
}

std::int32_t Restaurant::CookFood() {
    if (isOpened_) {
        if (mediator_) mediator_->FoodIsCooked();
        return price_;
    }
    return 0;
}

std::int32_t Restaurant::AlterPrice(std::int32_t priceChange) {
    price_ += priceChange;
    return price_;
}

// Implementations for BusinessMediator
BusinessMediator::BusinessMediator(EstateOwner& estateOwner, GroceryStore& groceryStore, Restaurant& restaurant)
    : estateOwner_(estateOwner), groceryStore_(groceryStore), restaurant_(restaurant) {
    estateOwner_.SetBusinessMediator(design::AccessKey<BusinessMediator>(), this);
    groceryStore_.SetBusinessMediator(design::AccessKey<BusinessMediator>(), this);
    restaurant_.SetBusinessMediator(design::AccessKey<BusinessMediator>(), this);
}

void BusinessMediator::EstateRentPriceChanged(std::int32_t oldPrice, std::int32_t newPrice) {
    restaurant_.AlterPrice((newPrice - oldPrice) / 1000);
}

void BusinessMediator::GroceryStockChanged(std::int32_t newStock) {
    if (newStock > 0) {
        restaurant_.SetIsOpened(design::AccessKey<BusinessMediator>(), true);
    } else {
        restaurant_.SetIsOpened(design::AccessKey<BusinessMediator>(), false);
    }
}

void BusinessMediator::GroceryPriceChanged(std::int32_t oldPrice, std::int32_t newPrice) {
    restaurant_.AlterPrice(newPrice - oldPrice);
}

void BusinessMediator::FoodIsCooked() {
    // Implementation for when food is cooked
}
