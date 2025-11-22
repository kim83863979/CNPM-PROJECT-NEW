#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Student.h"
#include "Account.h"

class Admin {
private:
    std::string adminID;
    std::string fullName;
    int adminLevel = 0;
    std::string linkedAccountID;
    Account* account = nullptr;

public:
    // [FIX] Định nghĩa constructor mặc định tường minh để đảm bảo khởi tạo bộ nhớ
    Admin() : adminID(""), fullName(""), adminLevel(0), linkedAccountID(""), account(nullptr) {}

    Admin(const std::vector<std::string>& fields); // from file
    Admin(const std::string& id, const std::string& name, int level, Account* acc = nullptr);

    void setAccount(Account* acc);
    Account* getAccount() const;
    std::string getAccountID() const;

    std::string getFullName() const;
    std::string getAdminID() const;

    // Admin actions
    void searchStudentAccount(const std::vector<Student>& dsSinhVien) const;
    void createStudentAccount(std::vector<Student>& dsSinhVien, std::vector<std::unique_ptr<Account>>& dsTaiKhoan);
    void deleteStudentAccount(std::vector<Student>& dsSinhVien, std::vector<std::unique_ptr<Account>>& dsTaiKhoan);
    void displayStudentList(const std::vector<Student>& dsSinhVien) const;
    bool updatePassword(); // interactive via console

    std::string toFileString() const;
};
