#pragma once
#include <vector>
#include <string>
#include "ConsoleUI.h"  
#include "Student.h"   
#include "Admin.h"      
#include "Account.h"   
#include "Score.h"      
#include "Timetable.h"
using namespace std;


class Student;
class Admin;
class Account;

class SystemManager {

public:
    //Khởi tạo giá trị ban đầu cho hệ thống.
    SystemManager();

    void run();

private:
    //PHẦN 1: I/O (Lưu trữ)

    void loadData();//Tải dữ liệu từ file 'student_data.txt' vào các vector.

    void saveData();//Ghi dữ liệu từ các vector vào file 'student_data.txt'

    // PHẦN 2: CONTROLLER (Điều khiển) 

    bool handleLogin();//Xử lý luồng đăng nhập, bao gồm kiểm tra 5 lần sai.

    void handleLogout();//Xử lý đăng xuất (đặt currentUser về null).

    void showStudentMenu();//Hiển thị và xử lý vòng lặp menu cho Student.

    void showAdminMenu();//Hiển thị và xử lý vòng lặp menu cho Admin.

    // PHẦN 3: STATE (Trạng thái & Dữ liệu) 

    // Tên file text cố định để lưu/tải dữ liệu.
    const string DATA_FILE;

    Account* currentUser;
 
    vector<Student> allStudents;
    
    vector<Admin> allAdmins;
};

