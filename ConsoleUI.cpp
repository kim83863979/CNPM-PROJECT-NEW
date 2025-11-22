
#include "ConsoleUI.h"
#include <iostream>
#include <limits>

void ConsoleUI::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\x1B[2J\x1B[H";
#endif
}

void ConsoleUI::pressEnterToContinue() {
    std::cout << "\n  Nhan Enter de tiep tuc...";

    // 1. Nếu có trạng thái lỗi trên cin thì xóa trạng thái đó
    if (std::cin.fail() || std::cin.eof()) {
        std::cin.clear();
    }

    // 2. Tiêu thụ mọi ký tự đang có sẵn trong bộ đệm nhập (nếu có)
    //    (in_avail() trả về số ký tự có sẵn, không chặn)
    std::streambuf* buf = std::cin.rdbuf();
    while (buf->in_avail() > 0) {
        int c = buf->sbumpc();
        if (c == EOF) break;
    }

    // 3. Chờ người dùng nhấn Enter (đọc một dòng)
    std::string temp;
    std::getline(std::cin, temp);
}

void ConsoleUI::displayLoginScreen() {
    clearScreen();
    std::cout << "============================================================\n";
    std::cout << "     CHAO MUNG DEN VOI HE THONG QUAN LY SINH VIEN\n";
    std::cout << "============================================================\n\n";
    std::cout << "                 [ DANG NHAP HE THONG ]\n\n";
}

void ConsoleUI::getLoginCredentials(std::string& username, std::string& password) {
    std::cout << "  Nhap Student ID / Admin ID: ";
    std::cin >> username;
    std::cout << "  Nhap mat khau: ";
    std::cin >> password;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void ConsoleUI::displayStudentMenu(const std::string& studentName, const std::string& studentID) {
    clearScreen();
    std::cout << "============================================================\n";
    std::cout << "                    MENU SINH VIEN\n";
    std::cout << "============================================================\n";
    std::cout << "  Xin chao, " << studentName << " (ID: " << studentID << ")\n\n";
    std::cout << "  1. Xem thong tin ca nhan\n";
    std::cout << "  2. Cap nhat thong tin (SDT, Email)\n";
    std::cout << "  3. Xem thoi khoa bieu\n";
    std::cout << "  4. Xem diem hoc tap\n";
    std::cout << "  5. Doi mat khau\n";
    std::cout << "  0. Dang xuat\n";
    std::cout << "------------------------------------------------------------\n";
}

int ConsoleUI::getStudentChoice() {
    while (true) {
        std::string line = promptInput("Chon chuc nang (0-5)");
        if (line.empty()) {
            std::cout << "  >>> Loi: Vui long nhap so tu 0 den 5!\n";
            continue;
        }
        try {
            int choice = std::stoi(line);
            if (choice >= 0 && choice <= 5) return choice;
        }
        catch (...) { /* fallthrough */ }
        std::cout << "  >>> Loi: Vui long nhap so tu 0 den 5!\n";
    }
}

void ConsoleUI::displayAdminMenu(const std::string& adminName) {
    clearScreen();
    std::cout << "============================================================\n";
    std::cout << "                  MENU QUAN TRI VIEN\n";
    std::cout << "============================================================\n";
    std::cout << "  Xin chao, " << adminName << "\n\n";
    std::cout << "  1. Tim kiem tai khoan sinh vien\n";
    std::cout << "  2. Tao tai khoan sinh vien moi\n";
    std::cout << "  3. Xoa tai khoan sinh vien\n";
    std::cout << "  4. Xem danh sach sinh vien\n";
    std::cout << "  5. Doi mat khau\n";
    std::cout << "  0. Dang xuat\n";
    std::cout << "------------------------------------------------------------\n";
}

int ConsoleUI::getAdminChoice() {
    while (true) {
        std::string line = promptInput("Chon chuc nang (0-5)");
        if (line.empty()) {
            std::cout << "  >>> Loi: Vui long nhap so tu 0 den 5!\n";
            continue;
        }
        try {
            int choice = std::stoi(line);
            if (choice >= 0 && choice <= 5) return choice;
        }
        catch (...) { /* fallthrough */ }
        std::cout << "  >>> Loi: Vui long nhap so tu 0 den 5!\n";
    }
}

void ConsoleUI::showMessage(const std::string& message) {
    std::cout << "\n  >>> " << message << " <<<\n";
    pressEnterToContinue();
}

std::string ConsoleUI::promptInput(const std::string& promptMessage) {
    std::string input;
    std::cout << "  " << promptMessage << ": ";
    std::getline(std::cin, input);
    return input;
}
