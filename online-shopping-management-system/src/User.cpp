#include "User.h" 
#include <iostream> 
#include <fstream>
#include <ctime>
string User::getName() const
{
return name;
}
bool User::login(const string &inputEmail, const string &inputPassword)
{
std::ifstream userFile("database/users.dat"); if (!userFile)
{
std::cout << "User database is unavailable, please try again later." << std::endl;
 
return false;
}
string line;
int currentUserID;
string currentEmail, currentPassword, currentContact, currentName; bool userFound = false;
while (getline(userFile, line))
{
if (line.find("UserID: ") == 0)
{
currentUserID = stoi(line.substr(8));
}
else if (line.find("Email: ") == 0)
{
currentEmail = line.substr(7);
}
else if (line.find("Password: ") == 0)
{
currentPassword = line.substr(10);
}
else if (line.find("Name: ") == 0)
{
currentName = line.substr(6);
}
else if (line.find("Contact: ") == 0)
{
currentContact = line.substr(9);
}
else if (line.find("	") == 0)
{
// End of user data
if (currentEmail == inputEmail)
{
userFound = true;
if (currentPassword == inputPassword)
{
std::cout << "Login successful!" << std::endl;
std::cout << "Welcome, " << currentName << "!" << std::endl; userFile.close();
this->userID = currentUserID;
 
this->name = currentName; this->email = currentEmail;
this->password = currentPassword; this->contact = currentContact; this->isRegistered = true;
return true;
}
else
{
std::cout << "Wrong password! Please try again." << std::endl; userFile.close();
return false;
}
}
currentEmail.clear(); currentPassword.clear(); currentName.clear();
}
}
if (!userFound)
{
std::cout << "User with email " << inputEmail << " does not exist." << std::endl;
}
userFile.close(); 
return false;
}
void User::logout() const
{
std::cout << "User " << this->name << " has been logged out." << std::endl;
}
void User::viewProfile() const
{
std::cout << "User Profile" << std::endl; std::cout << "	" << std::endl;
std::cout << "User ID: " << userID << std::endl; std::cout << "Name: " << name << std::endl; 
std::cout << "Email: " << email << std::endl; std::cout << "Contact: " << contact << std::endl;
}
void User::Register()
 
{
std::cout << "Enter email: "; std::getline(std::cin, email);

// First check if the database directory exists 
if (system("mkdir -p database") != 0)
{
std::cout << "Error creating database directory." << std::endl; 
return;
}
// Check if user already exists
std::ifstream userFile("database/users.dat"); 
if (userFile)
{
string line;
string storedEmail;
while (getline(userFile, line))
{
if (line.find("Email: ") == 0)
{
storedEmail = line.substr(7); // Skip "Email: "

if (storedEmail == email)
{
std::endl;
}
}
 
std::cout << "User with email " << email << " already exists. Please login!" << userFile.close(); 
return;
 
}
userFile.close();
}
std::cout << "Enter password: "; 
std::getline(std::cin, password); 
std::cout << "Enter full name: "; 
std::getline(std::cin, name);
std::cout << "Enter contact number: "; 
std::getline(std::cin, contact);
userID = static_cast<int>(time(nullptr) % 10000);
 
isRegistered = true;
// Open file in append mode
std::ofstream outFile("database/users.dat", std::ios::app); if (!outFile)
{
std::cout << "Error opening user database for writing." << std::endl; return;
}
// Write user data in text format
outFile << "UserID: " << userID << "\n"; 
outFile << "Name: " << name << "\n"; 
outFile << "Email: " << email << "\n"; 
outFile << "Password: " << password << "\n"; 
outFile << "Contact: " << contact << "\n"; 
outFile << "	\n";
std::cout << "Registration successful!" << std::endl; 
std::cout << "Please login now " << std::endl; 
outFile.close();
}
