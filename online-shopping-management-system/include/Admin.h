#ifndef ADMIN_H 
#define ADMIN_H 
#include <vector> 
#include "User.h" 
#include "Product.h"
#include "Inventory.h" 
class Admin : public User
{
Inventory inventory{}; public:
Admin() : User() {}
void addProduct(const Product &product); 
void setPath(const string &path);
Product *getInventoryProducts(); 
void removeProduct(int productID); 
void updateProduct(int productID); 
void manageInventory();
void viewSalesReport(vector<Product> &sales);
};
#endif
