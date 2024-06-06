#include <gtest/gtest.h>
#include "BusinessSystem.cpp"

TEST(BusinessTest, GroceryPriceChangeTest) {
    EstateOwner estateOwner;
    GroceryStore groceryStore;
    Restaurant restaurant;
    BusinessMediator mediator(estateOwner, groceryStore, restaurant);

    groceryStore.AlterPrice(100); // Set initial price
    // Change price by +50
    EXPECT_EQ(groceryStore.AlterPrice(50), 150);
}

TEST(BusinessTest, GroceryStockChangeTest) {
    EstateOwner estateOwner;
    GroceryStore groceryStore;
    Restaurant restaurant;
    BusinessMediator mediator(estateOwner, groceryStore, restaurant);

    groceryStore.Supply(10);
    EXPECT_NO_THROW(restaurant.CookFood()); // Restaurant should be open

    groceryStore.Supply(-10);
    EXPECT_EQ(restaurant.CookFood(), 0); // Restaurant should be closed
}

TEST(BusinessTest, FoodIsCookedTest) {
    EstateOwner estateOwner;
    GroceryStore groceryStore;
    Restaurant restaurant;
    BusinessMediator mediator(estateOwner, groceryStore, restaurant);

    groceryStore.Supply(1);
    EXPECT_NO_THROW(restaurant.CookFood()); // Should not throw, as grocery is available

    groceryStore.Sell(); // Sell one item to make stock 0
    EXPECT_THROW(groceryStore.Sell(), std::logic_error); // Out of stock
}
