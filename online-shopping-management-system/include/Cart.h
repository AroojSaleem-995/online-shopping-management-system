#ifndef CART_H
#define CART_H 
#include "Product.h" 
class Cart{
Product *products;
int quantity;
double calculateTotal() const; 
public:
Cart(): products(nullptr), quantity(0){};
Product *getProducts() const;
int getQuantity() const;
void addProduct(const Product& product, int qty);
void removeProduct(const Product& product); 
void clearCart();
void viewCart() const;
};
#endif
