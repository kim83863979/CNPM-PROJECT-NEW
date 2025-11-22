
#include "Admin.h"
#include "ConsoleUI.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm> // Cần cho std::all_of
#include <cctype>    // Cần cho isspace
#include <memory>

Admin::Admin(const std::vector<std::string>& fields) {
    // expected: adminID,fullName,level,accountID
    if (fields.size() >= 4) {
        adminID = fields[0];
        fullName = fields[1];
        try { adminLevel = std::stoi(fields[2]); }
        catch (...) { adminLevel = 0; }
        linkedAccountID = fields[3];
    }
    account = nullptr;
}

Admin::Admin(const std::string& id, const std::string& name, int level, Account* acc)
    : adminID(id), fullName(name), adminLevel(level), account(acc) {
}

void Admin::setAccount(Account* acc) { account = acc; }
Account* Admin::getAccount() const { return account; }
std::string Admin::getAccountID() const { return account ? account->getAccountID() : linkedAccountID; }

std::string Admin::getFullName() const { return fullName; }
std::string Admin::getAdminID() const { return adminID; }

void Admin::searchStudentAccount(const std::vector<Student>& dsSinhVien) const {
    std::string id = ConsoleUI::promptInput("Nhap ID sinh vien can tim");
    for (const auto& s : dsSinhVien) {
        if (s.getID() == id) {
            s.viewProfile();
            return;
        }
    }
    ConsoleUI::showMessage("Khong tim thay sinh vien voi ID: " + id);
}

void Admin::createStudentAccount(std::vector<Student>& dsSinhVien, std::vector<std::unique_ptr<Account>>& dsTaiKhoan) {
    ConsoleUI::clearScreen();
    std::cout << "\n--- TAO TAI KHOAN SINH VIEN MOI ---\n";

    // 1. INPUT: Nhập tất cả dữ liệu (ConsoleUI xử lý nhập và newline)
    std::string sid = ConsoleUI::promptInput("Nhap ID sinh vien moi (SVxxx)");
    std::string name = ConsoleUI::promptInput("Nhap Ho va Ten");
    std::string dob = ConsoleUI::promptInput("Nhap Ngay sinh (dd/mm/yyyy)");
    std::string gender = ConsoleUI::promptInput("Nhap Gioi tinh");
    std::string cls = ConsoleUI::promptInput("Nhap Lop hoc");
    std::string major = ConsoleUI::promptInput("Nhap Chuyen nganh");
    std::string course = ConsoleUI::promptInput("Nhap Khoa hoc (VD: K17)");
    std::string status = ConsoleUI::promptInput("Nhap Tinh trang hoc tap (VD: Active)");
    std::string phone = ConsoleUI::promptInput("Nhap SDT");
    std::string email = ConsoleUI::promptInput("Nhap Email");
    std::string accID = ConsoleUI::promptInput("Nhap accountID cho sinh vien (username)");
    std::string pass = ConsoleUI::promptInput("Nhap mat khau (>=8 ky tu, co so & ky tu dac biet)");

    // Kiểm tra ID không được rỗng/chỉ là dấu cách
    auto is_blank = [](const std::string& s) {
        return s.empty() || std::all_of(s.begin(), s.end(), [](char c) { return std::isspace(static_cast<unsigned char>(c)); });
        };

    if (is_blank(sid) || is_blank(accID)) {
        ConsoleUI::showMessage("LOI: ID sinh vien hoac AccountID khong duoc de trong!");
        return;
    }

    // 2. LOGIC: Tạo đối tượng

    // A. Tạo Student mới
    dsSinhVien.emplace_back(sid, name, phone, email, dob, gender, cls, major, course, status, (Account*)nullptr);

    // B. Gán linkedAccountID cho Student mới
    dsSinhVien.back().setLinkedAccountID(accID);

    // C. Tạo Account mới
    dsTaiKhoan.emplace_back(std::make_unique<Account>(accID, pass, "Student"));

    // 3. OUTPUT: Hiển thị kết quả
    ConsoleUI::showMessage("Tao tai khoan sinh vien thanh cong!");
}

void Admin::deleteStudentAccount(std::vector<Student>& dsSinhVien, std::vector<std::unique_ptr<Account>>& dsTaiKhoan) {
    std::string sid = ConsoleUI::promptInput("Nhap ID sinh vien can xoa");
    for (auto it = dsSinhVien.begin(); it != dsSinhVien.end(); ++it) {
        if (it->getID() == sid) {
            std::string aid = it->getAccountID();
            dsSinhVien.erase(it);
            // xoa account
            for (auto it2 = dsTaiKhoan.begin(); it2 != dsTaiKhoan.end(); ++it2) {
                if ((*it2) && (*it2)->getAccountID() == aid) { dsTaiKhoan.erase(it2); break; }
            }
            ConsoleUI::showMessage("Da xoa sinh vien va account lien quan.");
            return;
        }
    }
    ConsoleUI::showMessage("Khong tim thay sinh vien de xoa.");
}

void Admin::displayStudentList(const std::vector<Student>& dsSinhVien) const {
    std::cout << "\n--- Danh sach sinh vien ---\n";

    // Header (Sử dụng độ rộng tối ưu để tránh tràn)
    std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------\n";
    std::cout << "| " << std::left << std::setw(8) << "ID"
        << "| " << std::setw(20) << "Ho Ten"
        << "| " << std::setw(12) << "Ngay Sinh"
        << "| " << std::setw(8) << "Gioi Tinh"
        << "| " << std::setw(10) << "Lop"
        << "| " << std::setw(25) << "Chuyen Nganh"
        << "| " << std::setw(10) << "Khoa hoc"
        << "| " << std::setw(15) << "Tinh trang" << " |\n";
    std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------\n";

    // Danh sách (Body)
    for (const auto& s : dsSinhVien) {
        std::cout << "| " << std::left << std::setw(8) << s.getID()
            << "| " << std::setw(20) << s.getName()
            << "| " << std::setw(12) << s.getDateOfBirth()
            << "| " << std::setw(8) << s.getGender()
            << "| " << std::setw(10) << s.getClassName()
            << "| " << std::setw(25) << s.getMajor()
            << "| " << std::setw(10) << s.getCourse()
            << "| " << std::setw(15) << s.getAcademicStatus() << " |\n";
    }
    std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------\n";

    ConsoleUI::pressEnterToContinue();
}

bool Admin::updatePassword() {
    if (!account) {
        ConsoleUI::showMessage("Khong co account admin lien ket!");
        return false;
    }
    std::string oldp = ConsoleUI::promptInput("Nhap mat khau cu");
    std::string newp = ConsoleUI::promptInput("Nhap mat khau moi");
    if (account->changePassword(oldp, newp)) {
        ConsoleUI::showMessage("Doi mat khau thanh cong!");
        return true;
    }
    ConsoleUI::showMessage("Doi mat khau khong thanh cong!");
    return false;
}

std::string Admin::toFileString() const {
    // adminID,fullName,level,accountID
    std::string aid = account ? account->getAccountID() : linkedAccountID;
    return adminID + "," + fullName + "," + std::to_string(adminLevel) + "," + aid;
}
