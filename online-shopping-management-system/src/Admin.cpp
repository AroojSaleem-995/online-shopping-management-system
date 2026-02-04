#include "Admin.h" 
#include <iostream>
#include <string>
#include <ctime> 
#include <iomanip>
#include <vector>
#include <limits>
void Admin::setPath(const string &path)
{
inventory.setPath(path);
}
void Admin::addProduct(const Product &product)
{
if (product.getProductID() != 0)
{
inventory.addProduct(product);
}
}
Product *Admin::getInventoryProducts()
{
return inventory.getProducts();
}
// Remove a product from the inventory by its ID 
void Admin::removeProduct(const int productID)
{
if (inventory.findProductByID(productID) != nullptr)
{
inventory.removeProduct(productID);
}
}
// Update an existing product in the inventory 
void Admin::updateProduct(int productID)
{
Product *existingProduct = inventory.findProductByID(productID);
if (existingProduct == nullptr || existingProduct->getProductID() == 0)
{
std::cout << "Product with ID " << productID << " not found." << std::endl; return;
}
// Display product name and stock
std::cout << "Product Information:" << std::endl;
std::cout << "Name: " << existingProduct->getName() << std::endl; 
std::cout << "Stock: " << existingProduct->getStockQuantity() << std::endl; std::cout << "	" << std::endl;
 
char choice{};
std::cout << "Enter + or - to increase or decrease stock: "; 
std::cin >> choice;
int quantity;
if (choice == '+')
{
std::cout << "Enter quantity to add: "; 
std::cin >> quantity;
existingProduct->updateStock(existingProduct->getStockQuantity() + quantity);
}
else if (choice == '-')
{
std::cout << "Enter quantity to remove: "; 
std::cin >> quantity;
if (existingProduct->getStockQuantity() < quantity)
{
std::cout << "Insufficient stock. Cannot remove more than available." << std::endl; return;
}
existingProduct->updateStock(existingProduct->getStockQuantity() - quantity);
}
else
{
std::cout << "Invalid choice. Please try again." << std::endl;
}
}
// Display inventory management menu and handle options 
void Admin::manageInventory()
{
int choice; do
{
std::cout << "\n===== Inventory Management =====" << std::endl; 
std::cout << "1. View All Products" << std::endl;
std::cout << "2. Add New Product" << std::endl; 
std::cout << "3. Update Existing Product" << std::endl; 
std::cout << "4. Remove Product" << std::endl; 
std::cout << "5. Check Low Stock" << std::endl; 
std::cout << "6. Return to Main Menu" << std::endl; 
std::cout << "Enter your choice: ";
 
std::cin >> choice; switch (choice)
{
case 1:
{
inventory.listAllProducts(); break;
}
case 2:
{
    // Get product details from admin
    int id = 0, stock = 0;
    double price;
    std::string name, description;
    // clear the rest of the current input line before using getline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter Product Name: ";
    std::getline(std::cin, name);
    std::cout << "Enter Product Description: ";
    std::getline(std::cin, description);
    std::cout << "Enter Product Price: $";
    std::cin >> price;
    std::cout << "Enter Stock Quantity: ";
    std::cin >> stock;
    id = static_cast<int>(time(nullptr) % 10000);
    Product newProduct(id, name, description, price, stock);
    addProduct(newProduct);
    break;
}
case 3:
{
int id;
std::cout << "Enter Product ID to update: "; std::cin >> id;
updateProduct(id); break;
}
case 4:
{
int id;
std::cout << "Enter Product ID to remove: ";
 
std::cin >> id; removeProduct(id); break;
}
case 5:
{
inventory.checkLowStock(); break;
}
case 6:
{
std::cout << "Returning to main menu..." << std::endl; break;
}
default:
{
std::cout << "Invalid choice. Please try again." << std::endl;
}
}
} while (choice != 6);
}
struct ProductAndQuantity
{
Product product; int quantity{};
};
// Generate a sales report
void Admin::viewSalesReport(vector<Product> &sales)
{
// This is a simplified version that would normally connect to database or sales records 
std::cout << "\n========== Sales Report ==========" << std::endl; 
vector<ProductAndQuantity> productQuantities;
for (const Product &product : sales)
{
if (product.getProductID() != 0)
{
bool sameProduct = false;
for (ProductAndQuantity &pq : productQuantities)
{
if (pq.product.getProductID() == product.getProductID())
 
{
pq.quantity++; sameProduct = true; break;
}
}
if (!sameProduct)
{
ProductAndQuantity pq{product, 1}; productQuantities.push_back(pq);
}
}
}
// Get current time for the report 
const time_t now = time(nullptr);
const tm *timeInfo = localtime(&now); char buffer[80];
strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo); std::cout << "Report Generated: " << buffer << std::endl;
std::cout << "	" << std::endl;
// List all products and their simulated sales data 
std::cout << std::left << std::setw(5) << "ID"
<< std::setw(20) << "Product"
<< std::setw(10) << "Price"
<< std::setw(10) << "Sold"
<< std::setw(15) << "Revenue" << std::endl; std::cout << "	" << std::endl;
double totalRevenue = 0.0; int totalSold = 0;
for (ProductAndQuantity pq : productQuantities)
{
const int sold = pq.quantity;
const Product &product = pq.product;
// Generate sales data for demo purpose
const double revenue = sold * product.getPrice(); totalSold += sold;
totalRevenue += revenue;
std::cout << std::left << std::setw(5) << product.getProductID() << std::setw(20) << product.getName() << "Rs." << std::setw(9) << std::fixed << std::setprecision(2) << product.getPrice()<< std::setw(10) << sold
<< "Rs." << std::setw(14) << std::fixed << std::setprecision(2) << revenue << std::endl;
}
std::cout << "	" << std::endl;
std::cout << "Total Items Sold: " << totalSold << std::endl;
std::cout << "Total Revenue: Rs." << std::fixed << std::setprecision(2) << totalRevenue << std::endl;
std::cout << "==================================" << std::endl;
}
