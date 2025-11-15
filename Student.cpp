#include "Student.h"
#include <iostream>
using namespace std;

Student::Student() {}

Student::Student(string id, string name, string phone, string email)
    : id(id), name(name), phone(phone), email(email) {
}

void Student::viewProfile() {
    cout << "\n===== THONG TIN SINH VIEN =====\n";
    cout << "ID: " << id << endl;
    cout << "Ho Ten: " << name << endl;
    cout << "So DT: " << phone << endl;
    cout << "Email: " << email << endl;
}

void Student::updateProfile() {
    cout << "\nNhap SDT moi: ";
    cin >> phone;

    cout << "Nhap Email moi: ";
    cin >> email;

    cout << "Cap nhat thanh cong!\n";
}

void Student::viewSchedule() {
    cout << "\n===== THOI KHOA BIEU =====\n";
    if (schedule.empty()) {
        cout << "(Khong co mon hoc!)\n";
        return;
    }
    for (auto& x : schedule)
        x.display();
}

void Student::viewScores() {
    cout << "\n===== DIEM SO =====\n";
    if (scores.empty()) {
        cout << "(Khong co diem!)\n";
        return;
    }
    for (auto& x : scores)
        x.display();
}

string Student::getID() { return id; }
string Student::getName() { return name; }
