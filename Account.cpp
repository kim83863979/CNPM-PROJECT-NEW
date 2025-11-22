#include "Account.h"
#include <cctype>
#include <algorithm>

Account::Account(const std::string& id, const std::string& pass, const std::string& role)
    : accountID(id), password(pass), role(role) {
}

std::string Account::getAccountID() const { return accountID; }
std::string Account::getRole() const { return role; }
std::string Account::getPasswordForSave() const { return password; }

bool Account::login(const std::string& id, const std::string& pass) {
    if (accountID == id && password == pass) {
        loggedIn = true;
        return true;
    }
    return false;
}

void Account::logout() {
    loggedIn = false;
}

bool Account::checkPassword(const std::string& pass) const {
    return password == pass;
}

bool Account::isValidNewPassword(const std::string& newPass) const {
    if (newPass.size() < 8) return false;
    bool hasDigit = false, hasSpecial = false;
    std::string special = "!@#$%^&*()_+-=[]{};:,.<>?/\\|";
    for (char ch : newPass) {
        if (std::isdigit(static_cast<unsigned char>(ch))) hasDigit = true;
        if (special.find(ch) != std::string::npos) hasSpecial = true;
    }
    return hasDigit && hasSpecial;
}

bool Account::changePassword(const std::string& oldPass, const std::string& newPass) {
    if (!checkPassword(oldPass)) return false;
    if (!isValidNewPassword(newPass)) return false;
    password = newPass;
    return true;
}

std::string Account::toFileString() const {
    return accountID + "," + password + "," + role;
}

