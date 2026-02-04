#include "Customer.h" 
#include <iomanip> 
#include <iostream>
#include <string>
#include <vector>
#include "Inventory.h" 
Customer::Customer() : User()
{
orderHistory = {}; 
cart = {};
}
void Customer::browseProducts(vector<Product> &shop)
{
// Display products in the inventory 
for (Product &product : shop)
{
product.displayInfo();
std::cout << "	" << std::endl;
}
}
void Customer::addToCart(const Product &product)
{
int quantity{};
std::cout << "Enter quantity: "; 
std::cin >> quantity; std::cin.ignore(); cart.addProduct(product, quantity);
}
struct ProductAndQuantity
{
Product product; int quantity{};
double totalAmount;
};
void Customer ::placeOrder()
{
Product *cartProducts = cart.getProducts(); vector<ProductAndQuantity> pqArray;
// check for same products;
for (int i = 0; i < cart.getQuantity(); i++)
{
Product product = cartProducts[i] bool addedSameProduct = false;
for (ProductAndQuantity pq : pqArray)
{
 
if (pq.product.getProductID() == product.getProductID())
{
pq.quantity++;
pq.totalAmount += pq.product.getPrice(); 
addedSameProduct = true;
break;
}
}
if (!addedSameProduct)
{
ProductAndQuantity pq{product, 1, product.getPrice()}; pqArray.push_back(pq);
}
}
string paymentMethod{};
std::cout << "Enter payment method: "; std::cin >> paymentMethod;
// generate the current date as order date 
const time_t now = time(nullptr);
const tm *timeInfo = localtime(&now); char buffer[80];
strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo); string orderDate = buffer;
// add these products to the order history 
for (ProductAndQuantity pq : pqArray)
{
const int orderID = static_cast<int>(time(nullptr) % 10000);
Order newOrder(orderID, &pq.product, pq.quantity, pq.totalAmount, "Pending", paymentMethod, orderDate);
orderHistory.push_back(newOrder);
}

void Customer::viewOrderHistory() const
{
// create a table and display the product name, it's quantity in order, amount against this order, status, and order date
std::cout << "Order History" << std::endl; std::cout << "	" << std::endl;
std::cout << "Product" << std::setw(10) << "Quantity" << std::setw(10) << "Amount" << std::setw(10) << "Status" << std::setw(10) << "Order Date" << std::endl;
 
std::cout << "	" << std::endl;
for (Order order : orderHistory)
{
std::cout << std::left << std::setw(10) << order.getProduct()->getName() << std::setw(10) << order.getQuantity() << std::setw(10) << order.getAmount() << std::setw(10) << order.getStatus() << std::setw(10) << order.getOrderDate() << std::endl;
}
std::cout << "	" << std::endl;
}
void Customer ::review(string reviewText, int rating)
{
std::cout << "Enter the product ID to add review from the following: " << std::endl;
// create a table and display the product ID, and product name
std::cout << "Product ID" << std::setw(10) << "Product Name" << std::endl; std::cout << "	" << std::endl;
for (Order order : orderHistory)
{
const Product *product = order.getProduct();
std::cout << std::left << std::setw(10) << product->getProductID() << std::setw(10) << product-
>getName() << std::endl;
}
std::cout << "	" << std::endl;
int productID{}; std::cin >> productID; std::cin.ignore();
// checking if the product ID is valid, if so, adding review bool validProductId = false;
Review review; review.addReview(std::move(reviewText), rating); for (Order order : orderHistory)
{
if (order.getProduct()->getProductID() == productID)
{
order.getProduct()->addReview(review);
std::cout << "Review added successfully!" << std::endl; validProductId = true;
break;
}
}
 
if (!validProductId)
{
std::cout << "Invalid product ID. Please try again." << std::endl;
}
}
