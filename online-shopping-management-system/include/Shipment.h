#ifndef SHIPMENT_H 
#define SHIPMENT_H 
#include <string> 
using namespace std;

class Shipment{
 
int shipmentID, orderID;
string trackingNo, carrier, shipmentDate, estimatedDeliveryDate, actualDeliveryDate,status, shippingAddress;
public:
Shipment(): shipmentID(0), orderID(0){}; 
void generateTrackingNumber();
void updateStatus(const string& newStatus); 
void calculateEstimatedDelivery();
void notifyCustomer() const;
};
#endif
