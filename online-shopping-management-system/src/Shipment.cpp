#include "Shipment.h" 
#include <iostream> 
#include <ctime> 
#include <random> 
#include <sstream>
 #include <iomanip>
void Shipment::generateTrackingNumber() {
// Generate a random tracking number with format: SHP-XXXXXXXX 
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(10000000, 99999999); std::stringstream ss;
ss << "SHP-" << distrib(gen);
 
trackingNo = ss.str();
std::cout << "Tracking number generated: " << trackingNo << std::endl;
}
void Shipment::updateStatus(const string& newStatus) { status = newStatus;
std::cout << "Shipment status updated to: " << status << std::endl;
// If the status is "Delivered", update the actual delivery date 
if (newStatus == "Delivered") {
const time_t now = time(nullptr);
const tm* currentTime = localtime(&now); std::stringstream ss;
ss << (currentTime->tm_year + 1900) << "-"
<< std::setw(2) << std::setfill('0') << (currentTime->tm_mon + 1) << "-"
<< std::setw(2) << std::setfill('0') << currentTime->tm_mday;

actualDeliveryDate = ss.str();
std::cout << "Actual delivery date updated to: " << actualDeliveryDate << std::endl;
}
// Notify customer about the status update notifyCustomer();
}
void Shipment::calculateEstimatedDelivery() { const time_t now = time(nullptr);
const tm* currentTime = localtime(&now); std::stringstream ssShipment;
ssShipment << (currentTime->tm_year + 1900) << "-"
<< std::setw(2) << std::setfill('0') << (currentTime->tm_mon + 1) << "-"
<< std::setw(2) << std::setfill('0') << currentTime->tm_mday; shipmentDate = ssShipment.str();
// Calculate estimated delivery (shipment date + 3-5 days based on carrier) 
int deliveryDays = 3; // Default
if (carrier == "Express") { deliveryDays = 2;
} else if (carrier == "Standard") { deliveryDays = 5;
} else if (carrier == "Economy") { deliveryDays = 7;
}
// Add delivery days to the current date
const time_t estimatedTime = now + (deliveryDays * 24 * 60 * 60);
 
const tm* estimatedTm = localtime(&estimatedTime); std::stringstream ssEstimated;
ssEstimated << (estimatedTm->tm_year + 1900) << "-"
<< std::setw(2) << std::setfill('0') << (estimatedTm->tm_mon + 1) << "-"
<< std::setw(2) << std::setfill('0') << estimatedTm->tm_mday; 
estimatedDeliveryDate = ssEstimated.str();
std::cout << "Shipment date: " << shipmentDate << std::endl;
std::cout << "Estimated delivery date: " << estimatedDeliveryDate << std::endl;
}
void Shipment::notifyCustomer() const
{
std::cout << "Notification sent to customer:" << std::endl; std::cout << "	" << std::endl;
std::cout << "Shipment ID: " << shipmentID << std::endl; std::cout << "Order ID: " << orderID << std::endl;
std::cout << "Tracking Number: " << trackingNo << std::endl; std::cout << "Status: " << status << std::endl;
if (!estimatedDeliveryDate.empty()) {
std::cout << "Estimated Delivery: " << estimatedDeliveryDate << std::endl;
}
if (!actualDeliveryDate.empty()) {
std::cout << "Actual Delivery: " << actualDeliveryDate << std::endl;
}
std::cout << "Shipping Address: " << shippingAddress << std::endl; std::cout << "	" << std::endl;
}
