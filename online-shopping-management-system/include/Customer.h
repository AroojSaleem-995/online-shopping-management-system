#ifndef CUSTOMER_H 
#define CUSTOMER_H 
#include <string> 
#include <vector> 
#include "Inventory.h" 
using namespace std; 
#include "User.h" 
#include "Product.h" 
#include "Order.h" 
#include "Cart.h"
class Customer : public User
{
std::vector<Order> orderHistory; 
Cart cart;
public:
Customer();
void browseProducts(vector<Product> &shop); 
void addToCart(const Product &product);
void placeOrder();
void viewOrderHistory() const;
void review(string reviewText, int rating);
};
#endif
