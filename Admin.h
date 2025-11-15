#pragma once

#include <string>
#include <vector>
#include "Student.h" 
#include "Account.h" 

class Admin {
private:
    std::string adminID;
    std::string fullName;
    int adminLevel;

    int findStudentIndex(const std::vector<Student>& dsSinhVien, const std::string& id);

    int findAccountIndex(const std::vector<Account>& dsTaiKhoan, const std::string& id);

public:
    Admin(const std::string& id, const std::string& name, int level);

    std::string getFullName() const;
    
    // 1. TÌM KIẾM TÀI KHOẢN SINH VIÊN
    void searchStudentAccount(const std::vector<Student>& dsSinhVien);

    // 2. TẠO TÀI KHOẢN SINH VIÊN MỚI
    void createStudentAccount(std::vector<Student>& dsSinhVien, std::vector<Account>& dsTaiKhoan);

    // 3. XÓA TÀI KHOẢN SINH VIÊN
    void deleteStudentAccount(std::vector<Student>& dsSinhVien, std::vector<Account>& dsTaiKhoan);

    // 4. HIỂN THỊ DANH SÁCH SINH VIÊN
    void displayStudentList(const std::vector<Student>& dsSinhVien);

    // 5. CẬP NHẬT MẬT KHẨU ADMIN
    void updatePassword();
};