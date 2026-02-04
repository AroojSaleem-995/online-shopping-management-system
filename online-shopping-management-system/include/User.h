#ifndef USER_H 
#define USER_H 
#include <string> 
using namespace std; 
class User
{
int userID;
string name, email, password, contact; 
bool isRegistered;
public:
virtual ~User() = default;
User() : userID(0), isRegistered(false) {};
User(int id, const string &name, const string &email, const string &password, const string &contact) : userID(id), name(name), email(email), password(password), contact(contact), isRegistered(true) {}
string getName() const;
bool login(const string &inputEmail, const string &inputPassword); 
void logout() const;
void viewProfile() const; 
void Register();
};
#endif
