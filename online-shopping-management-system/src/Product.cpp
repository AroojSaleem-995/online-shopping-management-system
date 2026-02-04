#include "Product.h" 
#include <iostream> 
#include <utility>
string Product::getName() const
{
return name;
}
double Product::getPrice() const
{
return price;
}
void Product::addReview(const Review &review)
{
reviews.push_back(review);
}
int Product::getStockQuantity() const
{
return stockQuantity;
}
// Get product ID
int Product::getProductID() const
{
return productID;
}
string Product::getDescription() const
{
return description;
}
// Get all reviews
vector<Review> Product::getReviews() const
{
return reviews;
}
// Update stock quantity
void Product::updateStock(const int newStock)
{
if (newStock < 0)
 
std::cout << "Invalid stock quantity. Please provide a positive number." << std::endl; else
{
stockQuantity = newStock;
std::cout << "Stock quantity updated to: " << stockQuantity << std::endl;
}
}
// Display product information 
void Product::displayInfo() const
{
std::cout << "Product ID: " << productID << std::endl; std::cout << "Name: " << name << std::endl;
std::cout << "Description: " << description << std::endl; std::cout << "Price: $" << price << std::endl;
std::cout << "Available Stock: " << stockQuantity << std::endl;
}
