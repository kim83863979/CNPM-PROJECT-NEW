// ConsoleUI.cpp
#include "ConsoleUI.h"  
#include <string>
#include <limits>

using namespace std;

// 1. XÓA MÀN HÌNH (hỗ trợ cả Windows và Linux)
void ConsoleUI::clearScreen() {
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear"); // Linux/Mac
    #endif
}

// 2. DỪNG MÀN HÌNH - NHẤN ENTER ĐỂ TIẾP TỤC
void ConsoleUI::pressEnterToContinue() {
    cout << "\n  Nhan Enter de tiep tuc...";
    cin.get(); // Đợi người dùng nhấn Enter
}

// 3. HIỂN THỊ MÀN HÌNH ĐĂNG NHẬP
void ConsoleUI::displayLoginScreen() {
    clearScreen();
    cout << "============================================================" << endl;
    cout << "     CHAO MUNG DEN VOI HE THONG QUAN LY SINH VIEN" << endl;
    cout << "============================================================" << endl;
    cout << endl;
    cout << "                 [ DANG NHAP HE THONG ]" << endl;
    cout << endl;
}

// 4. NHẬN THÔNG TIN ĐĂNG NHẬP
void ConsoleUI::getLoginCredentials(string& username, string& password) {
    cout << "  Nhap Student ID / Admin ID: ";
    cin >> username;
    cin.ignore(); // Xóa ký tự \n còn lại trong bộ đệm
    cout << "  Nhap mat khau: ";
    cin >> password;
}

// 5. HIỂN THỊ MENU SINH VIÊN
void ConsoleUI::displayStudentMenu(const string& studentName, const string& studentID) {
    clearScreen();
    cout << "============================================================" << endl;
    cout << "                    MENU SINH VIEN" << endl;
    cout << "============================================================" << endl;
    cout << "  Xin chao, " << studentName << " (ID: " << studentID << ")" << endl;
    cout << endl;
    cout << "  1. Xem thong tin ca nhan" << endl;
    cout << "  2. Cap nhat thong tin (SDT, Email)" << endl;
    cout << "  3. Xem thoi khoa bieu" << endl;
    cout << "  4. Xem diem hoc tap" << endl;
    cout << "  5. Doi mat khau" << endl;
    cout << "  0. Dang xuat" << endl;
    cout << "------------------------------------------------------------" << endl;
}

// 6. NHẬN LỰA CHỌN CỦA SINH VIÊN (0-5)
int ConsoleUI::getStudentChoice() {
    int choice;
    cout << "  Chon chuc nang (0-5): ";
    
    // Kiểm tra nhập sai (không phải số, hoặc ngoài khoảng 0-5)
    while (!(cin >> choice) || choice < 0 || choice > 5) {
        cout << "  >>> Loi: Vui long nhap so tu 0 den 5!" << endl;
        cin.clear(); // Xóa lỗi
        cin.ignore(10000, '\n'); // Xóa bộ đệm
        cout << "  Chon chuc nang (0-5): ";
    }
    
    cin.ignore(); // Xóa \n sau khi nhập số
    return choice;
}

// 7. HIỂN THỊ MENU ADMIN
void ConsoleUI::displayAdminMenu(const string& adminName) {
    clearScreen();
    cout << "============================================================" << endl;
    cout << "                  MENU QUAN TRI VIEN" << endl;
    cout << "============================================================" << endl;
    cout << "  Xin chao, " << adminName << endl;
    cout << endl;
    cout << "  1. Tim kiem tai khoan sinh vien" << endl;
    cout << "  2. Tao tai khoan sinh vien moi" << endl;
    cout << "  3. Xoa tai khoan sinh vien" << endl;
    cout << "  4. Xem danh sach sinh vien" << endl;
    cout << "  5. Doi mat khau" << endl;
    cout << "  0. Dang xuat" << endl;
    cout << "------------------------------------------------------------" << endl;
}

// 8. NHẬN LỰA CHỌN CỦA ADMIN (0-5)
int ConsoleUI::getAdminChoice() {
    int choice;
    cout << "  Chon chuc nang (0-5): ";
    
    while (!(cin >> choice) || choice < 0 || choice > 5) {
        cout << "  >>> Loi: Vui long nhap so tu 0 den 5!" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "  Chon chuc nang (0-5): ";
    }
    
    cin.ignore();
    return choice;
}

// 9. HIỂN THỊ THÔNG BÁO (lỗi, thành công, cảnh báo)
void ConsoleUI::showMessage(const string& message) {
    cout << "\n  >>> " << message << " <<<" << endl;
    pressEnterToContinue();
}

// 10. NHẬN INPUT CHUỖI TỪ NGƯỜI DÙNG (dùng cho cập nhật)
string ConsoleUI::promptInput(const string& promptMessage) {
    string input;
    cout << "  " << promptMessage << ": ";
    cin.ignore(); // Bỏ qua \n còn lại (nếu có)
    getline(cin, input);
    return input;
}