// SystemManager.h
#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include "Student.h"
#include "Admin.h"
#include <vector>
#include <string>

class SystemManager {
private:
    std::vector<Student*> students;
    std::vector<Admin*> admins;
    std::vector<Account*> allAccounts;
    Account* currentUser;

    void loadData();
    void saveData() const;

public:
    SystemManager();
    ~SystemManager();

    void run();
    bool handleLogin();
    void handleLogout();
    void showStudentMenu();
    void showAdminMenu();
    Account* findAccount(const std::string& id) const;
};

#endif
