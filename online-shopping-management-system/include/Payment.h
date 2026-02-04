#ifndef PAYMENT_H 
#define PAYMENT_H 
#include <string> 
using namespace std; 
class Payment{
int paymentID, orderID, transactionID; 
string paymentDate, paymentStatus; 
double totalAmount;
public:
Payment(): paymentID(0), orderID(0), transactionID(0), totalAmount(0.0){}; 
bool processPayment(double amount, const string& paymentDetails);
bool validatePaymentDetails(const string& paymentDetails);
};
#endif
