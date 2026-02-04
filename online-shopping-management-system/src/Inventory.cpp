#include "Inventory.h" 
#include <iostream> 
#include <fstream>
#include <string>
Inventory::Inventory()
{
std::ifstream inventoryFile(filePath); 
if (inventoryFile)
{
std::string line;
int productID = 0, stockQuantity{}; string name, description;
double price{}; vector<Review> reviews; int productsLoaded = 0;
while (getline(inventoryFile, line))
{
if (line.find("Product ID: ") == 0)
{
productID = stoi(line.substr(12));
}
else if (line.find("Name: ") == 0)
{
name = line.substr(6);
}
else if (line.find("Description: ") == 0)
{
description = line.substr(13);
}
else if (line.find("Price: $") == 0)
{
price = stod(line.substr(8));
}
else if (line.find("Stock Quantity: ") == 0)
{
 
stockQuantity = stoi(line.substr(16));
}
else if (line.find("Review ID: ") == 0)
{
int reviewID;
string comment, author; int rating;
size_t authorStart = line.find("Author: "); 
size_t ratingStart = line.find("Rating: ");
size_t commentStart = line.find("Comment: "); 
reviewID = stoi(line.substr(11, commentStart - 12));
comment = line.substr(commentStart + 9, ratingStart - commentStart - 10); 
rating = stoi(line.substr(ratingStart + 8, authorStart - ratingStart - 9)); 
author = line.substr(authorStart + 8);
Review review(reviewID, comment, rating, author); reviews.push_back(review);
}
else if (line.find("	") == 0)
{
Product product(productID, name, description, price, stockQuantity, reviews); products[productsLoaded++] = product;
productID = 0; reviews.clear();
}
}
}
inventoryFile.close();
}
void Inventory::addProduct(const Product &product)
{
// Check if the product already exists in the inventory
Product *existingProduct = findProductByID(product.getProductID()); if (existingProduct != nullptr)
{
std::cout << "Product already exists in inventory. Updating stock quantity." << std::endl; existingProduct->updateStock(product.getStockQuantity() + existingProduct->getStockQuantity()); return;
}
 
// Add the product to the inventory
// check if the length of the product array is less than 10; 
bool added = false;
for (Product &prod : products)
{
if (prod.getProductID() == 0)
{
prod = product; added = true;
bool addedToInventory = false;
std::ofstream inventoryFile(filePath, std::ios::app); if (inventoryFile)
{
inventoryFile << "Product ID: " << product.getProductID() << std::endl; inventoryFile << "Name: " << product.getName() << std::endl; inventoryFile << "Description: " << product.getDescription() << std::endl; inventoryFile << "Price: $" << product.getPrice() << std::endl;
inventoryFile << "Stock Quantity: " << product.getStockQuantity() << std::endl;
// Write reviews to the file
for (const Review &review : product.getReviews())
{
inventoryFile << "Review ID: " << review.getReviewID() << " "; inventoryFile << "Comment: " << review.getComment() << " "; inventoryFile << "Rating: " << review.getRating() << " "; inventoryFile << "Author: " << review.getAuthor() << " ";
}
inventoryFile << "	" << std::endl;

addedToInventory = true;
}
else
{
std::cout << "Error opening inventory file for writing." << std::endl;
}
inventoryFile.close();

if (addedToInventory)
{
// add to shop as well
std::ofstream shopFile("database/shop.dat", std::ios::app);
 
if (shopFile)
{
shopFile << "Product ID: " << product.getProductID() << std::endl; shopFile << "Name: " << product.getName() << std::endl;
shopFile << "Description: " << product.getDescription() << std::endl; shopFile << "Price: $" << product.getPrice() << std::endl;
shopFile << "Stock Quantity: " << product.getStockQuantity() << std::endl; shopFile << "	" << std::endl;
}
else
{
std::cout << "Error opening shop file for writing." << std::endl;
}
shopFile.close();
}
break;
}
}
if (!added)
{
std::cout << "Error: Inventory is full. Cannot add more products." << std::endl;
}
else
{
std::cout << "Product added to inventory." << std::endl;
}
}
void Inventory::setPath(const string &path)
{
filePath = path;
}
void Inventory::removeProduct(int productID)
{
// Check if the product exists in the inventory
Product *existingProduct = findProductByID(productID); if (existingProduct == nullptr)
{
std::cout << "Product not found in inventory." << std::endl; return;
}
 

// Remove the product from the inventory
// find the product to remove 
int removingIndex{};
for (int i = 0; i < 10; i++)
{
if (products[i].getProductID() == productID)
{
removingIndex = i; break;
}
}
// copy existing products and skip the one to be removed;
 Product *newProducts = new Product[10];
int j = 0;
for (int i = 0; i < 10; i++)
{
if (i != removingIndex)
{
newProducts[j++] = products[i];
}
}
// copy the updated products to the original 
for (int i = 0; i < 10; i++)
{
products[i] = newProducts[i];
}
delete[] newProducts;

cout << "Product removed from inventory." << endl;
}
Product *Inventory::getProducts()
{
return products;
}
// Check for products with low stock (less than 3 items) 
void Inventory::checkLowStock()
{
std::cout << "=== Low Stock Report ===" << std::endl; bool found = false;
 

for (const Product &product : products)
{
// Only check products that have a valid ID (non-zero means initialized) 
if (product.getProductID() != 0)
{
if (product.getStockQuantity() < 3)
{
std::cout << "Product ID: " << product.getProductID() << std::endl; 
std::cout << "Name: " << product.getName() << std::endl;
std::cout << "Available Stock: " << product.getStockQuantity() << std::endl;
}
found = true;
std::cout << "	" << std::endl;
}
}
if (!found)
{
std::cout << "No products in inventory." << std::endl;
}

std::cout << "=======================\n"
<< std::endl;
}
// Find the product by its ID
Product *Inventory::findProductByID(const int productID)
{
for (auto &product : products)
{
if (product.getProductID() == productID)
{
return &product;
}
}

return nullptr; // Product not found
}
// List all products in inventory 
void Inventory::listAllProducts()
{
 
std::cout << "====== Inventory Products ======" << std::endl; bool found = false;
for (const auto &product : products)
{
// Only display products that have a valid ID (non-zero means initialized) 
if (product.getProductID() != 0)
{
product.displayInfo(); found = true;
std::cout << "	" << std::endl;
}
}
if (!found)
{
std::cout << "No products in inventory." << std::endl;
}
std::cout << "===============================" << std::endl;
}
