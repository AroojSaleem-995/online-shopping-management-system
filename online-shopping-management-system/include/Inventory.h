#ifndef INVENTORY_H 
#define INVENTORY_H
#include "Product.h" 
using namespace std; 
class Inventory
{
Product products[10]; 
string filePath;
public:
Inventory();
void addProduct(const Product &product); 
void setPath(const string &path);
Product *getProducts();
void removeProduct(int productID); 
void checkLowStock();
Product *findProductByID(int productID); 
void listAllProducts();
};
#endif
