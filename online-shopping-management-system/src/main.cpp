#include <iostream>
#include "User.h" 
#include "Admin.h" 
#include "Customer.h" 
#include <vector> 
#include <fstream> 
#include <sstream>
#include "Product.h"
using namespace std;


bool isLoggedIn = false; 
bool isAdmin = false;
 
std::vector<std::string> splitter(const std::string &s, char delim)
{
std::vector<std::string> result; std::stringstream ss(s);
std::string item;


while (getline(ss, item, delim))
{
result.push_back(item);
}


return result;
}


vector<Product> getShop()
{
vector<Product> shopProducts;
std::ifstream shopFile("database/shop.dat"); if (!shopFile)
{
std::cout << "Shop is unavailable, please try again later." << std::endl; return shopProducts;
}


if (shopFile.peek() == std::ifstream::traits_type::eof())
 
{
std::cout << "Shop is empty." << std::endl; return shopProducts;
}


std::string line;
int productID = 0, stockQuantity{}; string name, description;
double price{};
vector<Review> reviews; int productsLoaded = 0;
while (getline(shopFile, line))
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

size_t authorStart = line.find("Author: "); size_t ratingStart = line.find("Rating: ");
size_t commentStart = line.find("Comment: ");


reviewID = stoi(line.substr(11, commentStart - 12));
comment = line.substr(commentStart + 9, ratingStart - commentStart - 10); 
rating = stoi(line.substr(ratingStart + 8, authorStart - ratingStart - 9)); 
author = line.substr(authorStart + 8);

Review review(reviewID, comment, rating, author); 
reviews.push_back(review);
}
else if (line.find("	") == 0)
 
Product product(productID, name, description, price, stockQuantity, reviews); 
shopProducts.push_back(product);
productID = 0; reviews.clear();
}

shopFile.close();


return shopProducts;
}


User *handleLogin()
{
User *user;
bool exitLogin = false; int attempts = 0;
bool loggedIn = false; do
{
std::cout << "1. Login as Admin" << std::endl; std::cout << "2. Login as Customer" << std::endl; std::cout << "3. Go Back" << std::endl;

int choice; std::cin >> choice;
 
std::cin.ignore(); switch (choice)
{
case 1:
user = new Admin(); break;
case 2:
user = new Customer(); break;
case 3:
exitLogin = true; continue;
default:
std::cout << "Invalid choice. Please try again." << std::endl; continue;
}


std::string email, password; std::cout << "Enter email: "; std::getline(std::cin, email); std::cout << "Enter password: "; std::getline(std::cin, password);
loggedIn = user->login(email, password);


if (loggedIn)
{
 
exitLogin = true;
isLoggedIn = true; if (choice == 1)
{
isAdmin = true;
}
break;
}
attempts++;


} while (!exitLogin && attempts < 3);


if (loggedIn)
{
return user;
}


if (attempts >= 3)
{
std::cout << "Too many failed attempts. Returning to main menu." << std::endl;
}
return nullptr;
}


void handleRegistration()
{
 
User *user;


std::cout << "1. Register as Admin" << std::endl; std::cout << "2. Register as Customer" << std::endl; std::cout << "3. Go Back" << std::endl;
int choice;
std::cin >> choice; std::cin.ignore();
switch (choice)
{
case 1:
user = new Admin(); break;
case 2:
user = new Customer(); break;
case 3:
return; default:
std::cout << "Invalid choice. Please try again." << std::endl; return;
}
user->Register();
}


int main()
 
{
std::cout << "Welcome to the Online Shopping System!" << std::endl; std::cout << "	" << std::endl;
vector<Product> shopProducts = getShop(); bool appRunning = true;

do
{
std::cout << "1. Browse Products" << std::endl; std::cout << "2. Login" << std::endl;
std::cout << "3. Register" << std::endl; if (isLoggedIn)
{
std::cout << "4. Logout" << std::endl;
}


std::cout << "0. Exit" << std::endl;


int choice; std::cin >> choice; std::cin.ignore();

User *loggedInUser = nullptr;


switch (choice)
{
 
case 2:
{
if (!isLoggedIn)
{
loggedInUser = handleLogin();
}
else
{
std::cout << "You are already logged in." << std::endl;
}


if (loggedInUser)
{
if (isAdmin)
{
Admin *admin = dynamic_cast<Admin *>(loggedInUser);


std::string firstName = splitter(admin->getName(), ' ')[0]; string localStoragePath = "database/" + firstName + ".dat"; admin->setPath(localStoragePath);

admin->manageInventory();
}
else
{
Customer *customer = dynamic_cast<Customer *>(loggedInUser);
 
bool exitCustomer = false; do
{
std::cout << "1. Browse Products" << std::endl; std::cout << "2. Add to cart" << std::endl;
std::cout << "3. View Cart" << std::endl; std::cout << "4. Place Order" << std::endl;
std::cout << "5. View Order History" << std::endl; std::cout << "0. Logout" << std::endl;

int customerChoice;
std::cin >> customerChoice; std::cin.ignore();

switch (customerChoice)
{
case 1:
customer->browseProducts(shopProducts); break;
case 2:
int productID;
std::cout << "Enter Product ID to add to cart: "; std::cin >> productID;
for (const Product &product : shopProducts)
{
if (product.getProductID() == productID)
 
{
customer->addToCart(product); break;
}
}
break; 
case 3:
customer->viewCart();
break;

case 4:
customer->placeOrder(); break;
case 5:
customer->viewOrderHistory(); break;
case 0:
std::cout << "Logging out..." << std::endl; customer->logout();
isLoggedIn = false; exitCustomer = true; break;

default:
std::cout << "Invalid choice. Please try again." << std::endl; break;
 
}
} while (!exitCustomer);
}
}
else
{
std::cout << "Login failed. Please try again." << std::endl;
}
break;
}
case 3:
{
if (!isLoggedIn)
{
handleRegistration();
}
else
{
std::cout << "You are already logged in." << std::endl;
}
break;
}
case 1:
{
for (const Product &product : shopProducts)
{
 
product.displayInfo();
std::cout << "	" << std::endl;
}


std::cout << " ======================================= " << std::endl;


break;
}


case 0:
std::cout << "Exiting the application. Goodbye!" << std::endl; appRunning = false;
break; default:
std::cout << "Invalid choice. Please try again." << std::endl; break;
}
} while (appRunning);


return 0;
}
