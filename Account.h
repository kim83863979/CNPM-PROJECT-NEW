// Account.h
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
private:
    std::string username;
    std::string password;
    std::string role;

    bool isValidNewPassword(const std::string& newPass) const;

public:
    Account(const std::string& user, const std::string& pass, const std::string& r);
    
    std::string getUsername() const;
    std::string getRole() const;
    std::string getPassword() const;

    bool login(const std::string& user, const std::string& pass);
    void logout();
    bool changePassword(const std::string& oldPass, const std::string& newPass);
    bool checkPassword(const std::string& pass) const;
};

#endif