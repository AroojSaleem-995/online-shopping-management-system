#ifndef ORDER_H 
#define ORDER_H 
#include "Product.h" 
#include <string> 
using namespace std; 
class Order
{
int orderID, quantity; 
Product *product; 
double totalAmount;
string status, paymentMethod, orderDate; 
public:
Order() : orderID(0), quantity(0), product(nullptr), totalAmount(0.0) {};
Order(int id, Product *product, int quantity, double totalAmount, string status, string paymentMethod, string orderDate); 
Product *getProduct() const; 
double getAmount() const;
int getQuantity() const; 
string getStatus();
string getOrderDate();
 
void generateInvoice(); 
void cancelOrder();
void updateStatus(string newStatus);
};
#endif
