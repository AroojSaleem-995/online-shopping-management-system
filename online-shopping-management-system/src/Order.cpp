#include "Order.h"
#include <iostream>
Order::Order(const int id, Product *product, const int quantity, const double totalAmount, string status, string paymentMethod,
string orderDate)
{
this->orderID = id;
 
this->product = product; this->quantity = quantity;
this->totalAmount = totalAmount; this->status = std::move(status);
this->paymentMethod = std::move(paymentMethod); this->orderDate = std::move(orderDate);
}
Product *Order::getProduct() const
{
return product;
}
double Order::getAmount() const
{
return totalAmount;
}
int Order::getQuantity() const
{
return quantity;
}
string Order::getStatus()
{
return status;
}
string Order::getOrderDate()
{
return orderDate;
}
// Generate invoice for the order 
void Order::generateInvoice()
{
std::cout << "================ INVOICE ================" << std::endl;
std::cout << "Order ID: " << orderID << std::endl; std::cout << "Date: " << orderDate << std::endl; std::cout << "Status: " << status << std::endl;
std::cout << "Payment Method: " << paymentMethod << std::endl; std::cout << "	" << std::endl;
// Display products if available
if (product != nullptr && quantity > 0)
{
std::cout << "Products:" << std::endl;
 
for (int i = 0; i < quantity; i++)
{
const double price = product->getPrice(); totalAmount += price;
}
}
std::cout << "Total Amount: $" << totalAmount << std::endl;
std::cout << "=========================================" << std::endl;
}
// Cancel the order
void Order::cancelOrder()
{
if (status == "Shipped" || status == "Delivered")
{
std::cout << "Cannot cancel order. Order has already been " << status << "." << std::endl;
}
else
{
status = "Cancelled";
std::cout << "Order #" << orderID << " has been cancelled." << std::endl;
}
}
// Update order status
void Order::updateStatus(string newStatus)
{
// Valid statuses could be: Processing, Confirmed, Shipped, Delivered, Canceled status = std::move(newStatus);
std::cout << "Order #" << orderID << " status updated to: " << status << std::endl;
}
