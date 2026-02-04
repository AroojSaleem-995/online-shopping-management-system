#include "Cart.h" 
#include <iostream>
// Calculate the total price of all products in the cart 
double Cart::calculateTotal() const
{
double total = 0.0;
for (int i = 0; i < quantity; i++) { total += products[i].getPrice();
}
return total;
}
Product* Cart::getProducts() const
{
return products;
}
int Cart::getQuantity() const
{
return quantity;
}
// Add a product to the cart
void Cart::addProduct(const Product& product, const int qty)
{ if (product.getStockQuantity() < qty) 
    {
        std::cout << "Not enough stock available for " << product.getName() << std::endl;
        return;
    }
// Create a new array with increased size
Product* newProducts = new Product[quantity + qty];
// Copy existing products to the new array 
if (products != nullptr)
{
for (int i = 0; i < quantity; i++) { newProducts[i] = products[i];
}
}
// Add the new product to the end of the array (qty times) 
for (int i = 0; i < qty; i++) {
newProducts[quantity + i] = product;
}
// Delete the old array if it exists delete[] products;
// Update the product pointer and quantity 
products = newProducts;
quantity += qty;
std::cout << qty << " " << product.getName() << "(s) added to cart." << std::endl;
}
// Remove a product from the cart
void Cart::removeProduct(const Product& product) { const int productID = product.getProductID(); bool found = false;
int removeIndex{};
// Find the product in the cart 
for (int i = 0; i < quantity; i++) {
if (products[i].getProductID() == productID) { removeIndex = i;
found = true; break;
}
}
if (!found) {
std::cout << "Product not found in cart." << std::endl; return;
}
// Create a new array with decreased size
Product* newProducts = new Product[quantity - 1];
// Copy all products except the one to be removed 
for (int i = 0, j = 0; i < quantity; i++) {
if (i != removeIndex) { newProducts[j++] = products[i];
}
}
 

// Delete the old array delete[] products;
// Update the products pointer and quantity 
products = newProducts;
quantity--;
std::cout << product.getName() << " removed from cart." << std::endl;
}
// Clear all products from the cart 
void Cart::clearCart() {
if (products != nullptr) { delete[] products; products = nullptr;
}
quantity = 0;
std::cout << "Cart has been cleared." << std::endl;
}
// View all products in the cart 
void Cart::viewCart() const
{
if (quantity == 0) {
std::cout << "Your cart is empty." << std::endl; return;
}
std::cout << "===== Your Cart =====" << std::endl; for (int i = 0; i < quantity; i++) {
std::cout << i + 1 << ". "; products[i].displayInfo();
std::cout << "	" << std::endl;
}
double total = calculateTotal();
std::cout << "Total Items: " << quantity << std::endl; std::cout << "Total Price: $" << total << std::endl; std::cout << "====================" << std::endl;
}
