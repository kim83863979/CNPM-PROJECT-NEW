#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Account.h"
#include "Student.h"
#include "Admin.h"

class SystemManager {
private:
    std::vector<std::unique_ptr<Account>> allAccounts;
    std::vector<Student> allStudents;
    std::vector<Admin> allAdmins;

    std::string DATA_FILE;
    std::string currentUserID;
    std::string currentUserRole; // "Student" or "Admin"

    // helpers
    Student* findStudentByAccountID(const std::string& accID);
    Admin* findAdminByAccountID(const std::string& accID);
    Account* findAccountByID(const std::string& accID);

    // Hàm mới để liên kết con trỏ sau khi vector ổn định
    void linkStudentsToAccounts();

public:
    SystemManager();
    void run();

    bool handleLogin();
    void handleLogout();

    void showStudentMenu();
    void showAdminMenu();

    void saveData();
    void loadData();
};
