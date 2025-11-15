// ConsoleUI.h
#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <string>
using namespace std;

class ConsoleUI {
public:
    // Hiển thị màn hình đăng nhập
    static void displayLoginScreen();

    // Nhận thông tin đăng nhập
    static void getLoginCredentials(string& username, string& password);

    // Hiển thị menu sinh viên
    static void displayStudentMenu(const string& studentName, const string& studentID);

    // Nhận lựa chọn của sinh viên
    static int getStudentChoice();

    // Hiển thị menu admin
    static void displayAdminMenu(const string& adminName);

    // Nhận lựa chọn của admin
    static int getAdminChoice();

    // Hiển thị thông báo
    static void showMessage(const string& message);

    // Nhận input từ người dùng
    static string promptInput(const string& promptMessage);

    // Xóa màn hình (tùy hệ điều hành)
    static void clearScreen();

    // Dừng màn hình chờ nhấn Enter
    static void pressEnterToContinue();
};

#endif