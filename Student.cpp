
#include "Student.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include "ConsoleUI.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

// Khởi tạo tường minh linkedAccountID
Student::Student() : id(""), name(""), phone(""), email(""),
dateOfBirth(""), gender(""), className(""), major(""),
course(""), academicStatus(""), linkedAccountID(""), account(nullptr) {
}

// Constructor đầy đủ thông tin (10 trường)
Student::Student(const std::string& id, const std::string& name, const std::string& phone,
    const std::string& email, const std::string& dob, const std::string& gender,
    const std::string& cls, const std::string& major, const std::string& course,
    const std::string& status, Account* acc)
    : id(id), name(name), phone(phone), email(email),
    dateOfBirth(dob), gender(gender), className(cls), major(major),
    course(course), academicStatus(status), account(acc) {
}

Student::Student(const std::vector<std::string>& fields) {
    // expected: id,name,phone,email,dob,gender,className,major,course,status,accountID (11 truong)
    if (fields.size() >= 11) {
        id = fields[0];
        name = fields[1];
        phone = fields[2];
        email = fields[3];
        dateOfBirth = fields[4];
        gender = fields[5];
        className = fields[6];
        major = fields[7];
        course = fields[8];
        academicStatus = fields[9];
        linkedAccountID = fields[10];
    }
    else if (fields.size() >= 5) {
        // Compatibility for old file format (only 5 fields)
        id = fields[0];
        name = fields[1];
        phone = fields[2];
        email = fields[3];
        linkedAccountID = fields[4];
        dateOfBirth = gender = className = major = course = academicStatus = "";
    }
    account = nullptr;
}

void Student::setAccount(Account* acc) { account = acc; }
void Student::setLinkedAccountID(const std::string& accID) { linkedAccountID = accID; }

Account* Student::getAccount() const { return account; }
std::string Student::getAccountID() const { return account ? account->getAccountID() : linkedAccountID; }

void Student::viewProfile() const {
    ConsoleUI::clearScreen();
    cout << "\n============================================================\n";
    cout << "               THONG TIN CA NHAN SINH VIEN\n";
    cout << "============================================================\n";
    cout << "  ID              : " << id << endl;
    cout << "  Ho va Ten       : " << name << endl;
    cout << "  Ngay sinh       : " << dateOfBirth << endl;
    cout << "  Gioi tinh       : " << gender << endl;
    cout << "  Lop             : " << className << endl;
    cout << "  Chuyen nganh    : " << major << endl;
    cout << "  Khoa hoc        : " << course << endl;
    cout << "  Tinh trang HT   : " << academicStatus << endl;
    cout << "------------------------------------------------------------\n";
    cout << "  SDT             : " << phone << endl;
    cout << "  Email           : " << email << endl;
    cout << "============================================================\n";
    ConsoleUI::pressEnterToContinue();
}

void Student::updateProfile() {
    ConsoleUI::clearScreen();
    cout << "\n--- Cap nhat thong tin lien he ---\n";

    // Bắt buộc nhập SDT trước, không cho bỏ qua
    std::string newPhone;
    while (true) {
        newPhone = ConsoleUI::promptInput("Nhap SDT moi (Hien tai: " + phone + ")");

        if (newPhone.empty()) {
            ConsoleUI::showMessage("SDT khong duoc de trong. Vui long nhap lai.");
            continue;
        }
        // Optional: loại bỏ khoảng trắng đầu/cuối
        size_t first = newPhone.find_first_not_of(" \t\r\n");
        size_t last = newPhone.find_last_not_of(" \t\r\n");
        if (first == std::string::npos) {
            ConsoleUI::showMessage("SDT khong hop le. Vui long nhap lai.");
            continue;
        }
        newPhone = newPhone.substr(first, last - first + 1);
        break;
    }
    phone = newPhone;

    // Sau khi SDT hợp lệ -> tiếp tục nhập Email (bắt buộc, kiểm tra cơ bản)
    std::string newEmail;
    while (true) {
        newEmail = ConsoleUI::promptInput("Nhap Email moi (Hien tai: " + email + ")");
        if (newEmail.empty()) {
            ConsoleUI::showMessage("Email khong duoc de trong. Vui long nhap lai.");
            continue;
        }
        // Kiểm tra cơ bản dạng email: phải có '@' và '.'
        if (newEmail.find('@') == std::string::npos || newEmail.find('.') == std::string::npos) {
            ConsoleUI::showMessage("Email khong hop le. Vui long nhap lai.");
            continue;
        }
        // Trim khoảng trắng
        size_t first = newEmail.find_first_not_of(" \t\r\n");
        size_t last = newEmail.find_last_not_of(" \t\r\n");
        if (first == std::string::npos) {
            ConsoleUI::showMessage("Email khong hop le. Vui long nhap lai.");
            continue;
        }
        newEmail = newEmail.substr(first, last - first + 1);
        break;
    }
    email = newEmail;

    ConsoleUI::showMessage("Cap nhat thanh cong!");
}

void Student::viewSchedule() const {
    ConsoleUI::clearScreen();
    cout << "\n--- Thoi khoa bieu ---\n";
    if (schedule.empty()) {
        cout << "Chua co khoa hoc nao.\n";
        ConsoleUI::pressEnterToContinue();
        return;
    }
    cout << "------------------------------------------------------------\n";
    cout << "| " << std::left << std::setw(20) << "MON HOC"
        << "| " << std::setw(8) << "THU"
        << "| " << std::setw(8) << "GIO"
        << "| " << std::setw(8) << "PHONG" << " |\n";
    cout << "------------------------------------------------------------\n";
    for (const auto& t : schedule) t.display();
    cout << "------------------------------------------------------------\n";
    ConsoleUI::pressEnterToContinue();
}

void Student::viewScores() const {
    ConsoleUI::clearScreen();
    cout << "\n--- Diem hoc tap ---\n";
    if (scores.empty()) {
        cout << "Chua co diem.\n";
        ConsoleUI::pressEnterToContinue();
        return;
    }
    cout << "------------------------------------------------------------\n";
    cout << "| " << std::left << std::setw(25) << "MON HOC"
        << "| " << std::setw(8) << "DIEM"
        << "| " << std::setw(12) << "TRANG THAI" << " |\n";
    cout << "------------------------------------------------------------\n";
    for (const auto& s : scores) s.display();
    cout << "------------------------------------------------------------\n";
    ConsoleUI::pressEnterToContinue();
}

bool Student::changePassword(const string& oldPass, const string& newPass) {
    if (!account) {
        ConsoleUI::showMessage("Khong co account lien ket!");
        return false;
    }
    if (account->changePassword(oldPass, newPass)) {
        ConsoleUI::showMessage("Doi mat khau thanh cong!");
        return true;
    }
    ConsoleUI::showMessage("Doi mat khau khong thanh cong!");
    return false;
}

void Student::addScore(const Score& sc) { scores.push_back(sc); }
void Student::addTimetable(const Timetable& t) { schedule.push_back(t); }
const std::vector<Score>& Student::getScores() const { return scores; }
const std::vector<Timetable>& Student::getSchedule() const { return schedule; }

std::string Student::toFileString() const {
    // studentID,name,phone,email,dob,gender,className,major,course,status,accountID (11 truong)
    std::string aid = account ? account->getAccountID() : linkedAccountID;
    return id + "," + name + "," + phone + "," + email + "," +
        dateOfBirth + "," + gender + "," + className + "," + major + "," +
        course + "," + academicStatus + "," + aid;
}

std::string Student::getID() const { return id; }
std::string Student::getName() const { return name; }
std::string Student::getPhone() const { return phone; }
std::string Student::getEmail() const { return email; }

// Định nghĩa các hàm Getter mới:
std::string Student::getDateOfBirth() const { return dateOfBirth; }
std::string Student::getGender() const { return gender; }
std::string Student::getClassName() const { return className; }
std::string Student::getMajor() const { return major; }
std::string Student::getCourse() const { return course; }
std::string Student::getAcademicStatus() const { return academicStatus; }
