
#include "SystemManager.h"
#include "ConsoleUI.h"
#include "Score.h"
#include "Timetable.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <limits> // Cần thiết cho cin.ignore
#include <memory>

SystemManager::SystemManager()
    : DATA_FILE("student_data.txt"), currentUserID(""), currentUserRole("") {
    // optional: reserve to reduce reallocations
    allAccounts.reserve(2000);
    allStudents.reserve(2000);
    allAdmins.reserve(200);
}

Account* SystemManager::findAccountByID(const std::string& accID) {
    for (auto& a : allAccounts) if (a && a->getAccountID() == accID) return a.get();
    return nullptr;
}

Student* SystemManager::findStudentByAccountID(const std::string& accID) {
    for (auto& s : allStudents) {
        std::string aid = s.getAccountID();
        if (aid == accID) return &s;
    }
    return nullptr;
}

Admin* SystemManager::findAdminByAccountID(const std::string& accID) {
    for (auto& a : allAdmins) {
        std::string aid = a.getAccountID();
        if (aid == accID) return &a;
    }
    return nullptr;
}

// Định nghĩa hàm liên kết mới
void SystemManager::linkStudentsToAccounts() {
    // Liên kết Students
    for (auto& s : allStudents) {
        // Chỉ liên kết khi chưa có con trỏ account và có linkedAccountID hợp lệ
        if (!s.getAccount() && !s.getAccountID().empty()) {
            std::string aid = s.getAccountID();
            Account* acc = findAccountByID(aid);
            if (acc) s.setAccount(acc);
        }
    }
    // Liên kết Admins
    for (auto& a : allAdmins) {
        if (!a.getAccount() && !a.getAccountID().empty()) {
            std::string aid = a.getAccountID();
            Account* acc = findAccountByID(aid);
            if (acc) a.setAccount(acc);
        }
    }
}

void SystemManager::run() {
    loadData();
    ConsoleUI::showMessage("CHAO MUNG DEN VOI HE THONG QUAN LY SINH VIEN");

    while (true) {
        if (!handleLogin()) {
            ConsoleUI::showMessage("Dang nhap that bai qua 5 lan. Thoat chuong trinh.");
            break;
        }

        if (currentUserRole == "Student") showStudentMenu();
        else if (currentUserRole == "Admin") showAdminMenu();

        handleLogout();

        // [FIX I/O] Chỉ cần gọi promptInput, nó sẽ xử lý getline
        std::string choice = ConsoleUI::promptInput("Ban co muon thoat khoi he thong? (y/n)");
        if (choice == "y" || choice == "Y") break;
    }

    ConsoleUI::showMessage("Dang luu du lieu... Cam on da su dung!");
    saveData();
}

bool SystemManager::handleLogin() {
    for (int attempt = 0; attempt < 5; ++attempt) {
        ConsoleUI::displayLoginScreen();
        std::string username, password;
        ConsoleUI::getLoginCredentials(username, password);

        // Check accounts
        for (auto& accPtr : allAccounts) {
            if (accPtr && accPtr->login(username, password)) {
                // determine role: student or admin
                if (findStudentByAccountID(username)) currentUserRole = "Student";
                else if (findAdminByAccountID(username)) currentUserRole = "Admin";
                else currentUserRole = accPtr->getRole(); // fallback

                currentUserID = username;
                ConsoleUI::showMessage("Dang nhap thanh cong voi vai tro: " + currentUserRole);
                return true;
            }
        }

        ConsoleUI::showMessage("LOI: Ten dang nhap hoac mat khau khong dung. Con lai " + std::to_string(4 - attempt) + " lan thu.");
    }
    return false;
}

void SystemManager::handleLogout() {
    currentUserID = "";
    currentUserRole = "";
    ConsoleUI::showMessage("Da dang xuat thanh cong.");
}

void SystemManager::showStudentMenu() {
    Student* studentPtr = findStudentByAccountID(currentUserID);
    if (!studentPtr) {
        ConsoleUI::showMessage("LOI NGHIEM TRONG: Khong tim thay du lieu sinh vien.");
        return;
    }

    bool running = true;
    while (running) {
        ConsoleUI::displayStudentMenu(studentPtr->getName(), studentPtr->getID());
        int choice = ConsoleUI::getStudentChoice();

        switch (choice) {
        case 1: studentPtr->viewProfile(); break;
        case 2:
            studentPtr->updateProfile();
            saveData();
            break;
        case 3: studentPtr->viewSchedule(); break;
        case 4: studentPtr->viewScores(); break;
        case 5: {
            std::string oldp = ConsoleUI::promptInput("Nhap mat khau cu");
            std::string newp = ConsoleUI::promptInput("Nhap mat khau moi");
            Account* acc = studentPtr->getAccount();
            if (acc && acc->changePassword(oldp, newp)) {
                ConsoleUI::showMessage("Doi mat khau thanh cong!");
                saveData();
            }
            else {
                ConsoleUI::showMessage("Doi mat khau khong thanh cong!");
            }
            break;
        }
        case 0: running = false; break;
        default: ConsoleUI::showMessage("Lua chon khong hop le"); break;
        }
    }
}

void SystemManager::showAdminMenu() {
    Admin* adminPtr = findAdminByAccountID(currentUserID);
    if (!adminPtr) {
        ConsoleUI::showMessage("LOI NGHIEM TRONG: Khong tim thay du lieu admin.");
        return;
    }

    bool running = true;
    while (running) {
        ConsoleUI::displayAdminMenu(adminPtr->getFullName());
        int choice = ConsoleUI::getAdminChoice();

        switch (choice) {
        case 1:
            adminPtr->searchStudentAccount(allStudents);
            break;
        case 2:
            adminPtr->createStudentAccount(allStudents, allAccounts);
            linkStudentsToAccounts();
            adminPtr = findAdminByAccountID(currentUserID);
            saveData();
            break;
        case 3:
            adminPtr->deleteStudentAccount(allStudents, allAccounts);
            linkStudentsToAccounts();
            adminPtr = findAdminByAccountID(currentUserID);
            saveData();
            break;
        case 4:
            adminPtr->displayStudentList(allStudents);
            break;
        case 5:
            if (adminPtr->updatePassword()) saveData();
            break;
        case 0: running = false; break;
        default: ConsoleUI::showMessage("Lua chon khong hop le"); break;
        }
    }
}

void SystemManager::saveData() {
    std::ofstream file(DATA_FILE);
    if (!file.is_open()) {
        ConsoleUI::showMessage("LOI: Khong the mo file de luu du lieu.");
        return;
    }

    file << "[ACCOUNTS]\n";
    for (auto& accPtr : allAccounts) if (accPtr) file << accPtr->toFileString() << "\n";

    file << "[STUDENTS]\n";
    for (auto& s : allStudents) file << s.toFileString() << "\n";

    file << "[ADMINS]\n";
    for (auto& a : allAdmins) file << a.toFileString() << "\n";

    file << "[SCORES]\n";
    for (auto& s : allStudents) {
        for (auto& sc : s.getScores()) {
            file << s.getID() << "," << sc.toFileString() << "\n";
        }
    }

    file << "[TIMETABLES]\n";
    for (auto& s : allStudents) {
        for (auto& t : s.getSchedule()) {
            file << s.getID() << "," << t.toFileString() << "\n";
        }
    }

    file.close();
}

void SystemManager::loadData() {
    allAccounts.clear();
    allStudents.clear();
    allAdmins.clear();

    std::ifstream file(DATA_FILE);
    if (!file.is_open()) {
        ConsoleUI::showMessage("Thong bao: Khong tim thay file du lieu.");
        return;
    }

    std::string line, section;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        if (line.front() == '[' && line.back() == ']') { section = line; continue; }

        std::stringstream ss(line);
        std::vector<std::string> fields;
        std::string temp;
        // Xu ly dau phay
        while (std::getline(ss, temp, ',')) fields.push_back(temp);
        if (fields.empty()) continue;

        if (section == "[ACCOUNTS]" && fields.size() >= 3) {
            allAccounts.emplace_back(std::make_unique<Account>(fields[0], fields[1], fields[2]));
        }
        else if (section == "[STUDENTS]") {
            // Student constructor tu dong xu ly so luong fields (5 hoac 11)
            allStudents.emplace_back(fields);
        }
        else if (section == "[ADMINS]") {
            allAdmins.emplace_back(fields);
        }
        else if (section == "[SCORES]" && fields.size() >= 4) {
            // fields: studentID, scoreID, courseName, score, status
            std::string studentID = fields[0];
            std::vector<std::string> scoreData(fields.begin() + 1, fields.end());
            Score sc(scoreData);
            for (auto& s : allStudents) {
                if (s.getID() == studentID) { s.addScore(sc); break; }
            }
        }
        else if (section == "[TIMETABLES]" && fields.size() >= 6) {
            // fields: studentID, timetableID, courseName, day,time,room
            std::string studentID = fields[0];
            std::vector<std::string> tData(fields.begin() + 1, fields.end());
            Timetable t(tData);
            for (auto& s : allStudents) {
                if (s.getID() == studentID) { s.addTimetable(t); break; }
            }
        }
    }

    // Liên kết tài khoản
    linkStudentsToAccounts();

    file.close();
    ConsoleUI::showMessage("Da tai du lieu tu file thanh cong.");
}
