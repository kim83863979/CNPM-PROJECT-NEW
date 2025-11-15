#include "Account.h"
#include <string>
#include <cctype> 

using namespace std;
Account::Account(std::string user, std::string pass, std::string role)
    : username(user),
    password(pass), 
    role(role)
{ }

string Account::getUsername() const { return this->username; }
string Account::getRole() const { return this->role; }

string Account::getPassword() const { return this->password; }

bool Account::login(const string& user, const string& pass) {
    return (this->username == user && this->password == pass);
}

void Account::logout() {
    // Khong can lam gi
}

bool Account::changePassword(const string& oldPass, const string& newPass) {
    if (!checkPassword(oldPass)) { return false; }
    if (!isValidNewPassword(newPass)) { return false; }
    this->password = newPass;
    return true;
}

bool Account::checkPassword(const string& pass) {
    return (this->password == pass);
}

bool Account::isValidNewPassword(const string& newPass) {
    if (newPass.length() < 8) { return false; }
    bool hasNumber = false;
    bool hasSpecial = false;
    string specialChars = "!@#$%^&*()_+-=[]{};:,.<>?";

    for (int i = 0; i < newPass.length(); i++) {
        char ch = newPass[i];
        if (isdigit(ch)) { hasNumber = true; }
        if (specialChars.find(ch) != string::npos) { hasSpecial = true; }
    }
    return hasNumber && hasSpecial;
}