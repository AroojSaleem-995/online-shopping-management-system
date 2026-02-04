#ifndef PRODUCT_H 
#define PRODUCT_H 
#include <string> 
#include <vector> 
#include "Review.h" 
using namespace std; 
class Product
{
int productID, stockQuantity; 
string name, description; 
double price; 
vector<Review> reviews;
public:
Product() : productID(0), stockQuantity(0), price(0.0) {}
Product(int id, string name, string description, double price, int stockQuantity, vector<Review> reviews = {}): productID(id), name(std::move(name)), description(std::move(description)), price(price), stockQuantity(stockQuantity), reviews(std::move(reviews)) {};
string getName() const;
 
double getPrice() const; 
vector<Review> getReviews() const; 
string getDescription() const;
void addReview(const Review &review); 
int getStockQuantity() const;
int getProductID() const;
void updateStock(int newStock); 
void displayInfo() const;
};
#endif
