#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

using namespace std;

class Account {
private:
    string username;
    string password;
    string role;
    bool isValidNewPassword(const string& newPass);

public:
    Account(string user, string pass, string role);
    string getUsername() const;
    string getRole() const;

    string getPassword() const;
    //Day la ham khong an toan, nhung can thiet de saveData

    bool login(const string& user, const string& pass);
    void logout();
    bool changePassword(const string& oldPass, const string& newPass);
    bool checkPassword(const string& pass);
};

#endif