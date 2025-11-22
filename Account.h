#pragma once
#include <string>

class Account {
private:
    std::string accountID;
    std::string password;
    std::string role;
    bool loggedIn = false;

    bool isValidNewPassword(const std::string& newPass) const;

public:
    Account() = default;
    Account(const std::string& id, const std::string& pass, const std::string& role);

    std::string getAccountID() const;
    std::string getRole() const;
    std::string getPasswordForSave() const;

    bool login(const std::string& id, const std::string& pass);
    void logout();

    bool changePassword(const std::string& oldPass, const std::string& newPass);
    bool checkPassword(const std::string& pass) const;

    std::string toFileString() const;
};



