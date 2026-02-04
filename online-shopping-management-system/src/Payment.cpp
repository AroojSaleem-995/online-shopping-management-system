#include "Payment.h" 
#include <iostream> 
#include <ctime> 
#include <random> 
#include <sstream> 
#include <iomanip> 
#include <utility>
bool Payment::processPayment(const double amount, const string& paymentDetails) {
// Validate payment details first
if (!validatePaymentDetails(paymentDetails)) {
 
std::cout << "Payment failed: Invalid payment details." << std::endl; 
paymentStatus = "Failed";
return false;
}

// Set the payment amount 
totalAmount = amount;
// Generate a transaction ID (random for this implementation) 
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(100000, 999999); transactionID = distrib(gen);
// Generate a payment ID if not already set 
if (paymentID == 0) {
paymentID = distrib(gen);
}
// Set the payment date to the current date 
const time_t now = time(nullptr);
const tm* currentTime = localtime(&now); 
std::stringstream ss;
ss << (currentTime->tm_year + 1900) << "-"
<< std::setw(2) << std::setfill('0') << (currentTime->tm_mon + 1) << "-"
<< std::setw(2) << std::setfill('0') << currentTime->tm_mday; 
paymentDate = ss.str();
// Set payment status to successful paymentStatus = "Completed";
// Display payment confirmation
std::cout << "Payment processed successfully." << std::endl; std::cout << "Payment ID: " << paymentID << std::endl; std::cout << "Transaction ID: " << transactionID << std::endl; std::cout << "Date: " << paymentDate << std::endl;
std::cout << "Amount: $" << std::fixed << std::setprecision(2) << totalAmount << std::endl; return true;
}
bool Payment::validatePaymentDetails(const string& paymentDetails) {
// Let's assume the payment details string has this format:
// "method:card-number:expiry:cvv"
// e.g., "credit:1234567890123456:12/25:123"
std::stringstream ss(paymentDetails); std::string method, cardNumber, expiry, cvv;
 
// Parse the payment details 
getline(ss, method, ':'); 
getline(ss, cardNumber, ':'); 
getline(ss, expiry, ':');
getline(ss, cvv, ':');
// Basic validation checks
if (method != "credit" && method != "debit") { std::cout << "Invalid payment method." << std::endl; return false;
}
if (method == "credit" || method == "debit") {
// Check card number length (should be 16 digits) 
if (cardNumber.length() != 16) {
std::cout << "Invalid card number length." << std::endl; return false;
}
// Check if the card number contains only digits 
for (const char c : cardNumber) {
if (!isdigit(c)) {
std::cout << "Card number should contain only digits." << std::endl; return false;
}
}
// Check the expiry format (should be MM/YY) 
if (expiry.length() != 5 || expiry[2] != '/') {
std::cout << "Invalid expiry date format." << std::endl; return false;
}
// Check CVV (should be 3 digits) 
if (cvv.length() != 3) {
std::cout << "Invalid CVV length." << std::endl; return false;
}
for (const char c : cvv) { if (!isdigit(c)) {
std::cout << "CVV should contain only digits." << std::endl; return false;
}
}
}
return true;
}
