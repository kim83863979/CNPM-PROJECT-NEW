// Admin.h
#ifndef ADMIN_H
#define ADMIN_H

#include "Account.h"
#include <string>
#include <vector>

class Student; // Forward declaration

class Admin : public Account {
public:
    Admin(const std::string& user, const std::string& pass);

    void searchStudentAccount(const std::vector<Student*>& students) const;
    void createStudentAccount(std::vector<Student*>& students, 
                             std::vector<Account*>& accounts);
    void deleteStudentAccount(std::vector<Student*>& students, 
                             std::vector<Account*>& accounts);
    void displayStudentList(const std::vector<Student*>& students) const;
};

#endif
