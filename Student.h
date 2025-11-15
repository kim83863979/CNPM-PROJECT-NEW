// Student.h
#ifndef STUDENT_H
#define STUDENT_H

#include "Account.h"      // Đã có
#include "Score.h"        // THÊM DÒNG NÀY
#include "Timetable.h"    // THÊM DÒNG NÀY
#include <string>
#include <vector>

class Student : public Account {
private:
    std::string fullName;
    std::string dateOfBirth;
    std::string gender;
    std::string className;
    std::string major;
    std::string phone;
    std::string email;
    std::string address;
    std::vector<Score> scores;
    std::vector<Timetable> timetable;

public:
    Student(const std::string& user, const std::string& pass,
            const std::string& name, const std::string& dob, const std::string& gender,
            const std::string& className, const std::string& major,
            const std::string& phone, const std::string& email, const std::string& address);

    void viewProfile() const;
    void updateProfile();
    void viewSchedule() const;
    void viewScores() const;

    std::string getFullName() const;
    std::string getClassName() const;
    std::string getPhone() const;
    std::string getEmail() const;

    void setPhone(const std::string& p);
    void setEmail(const std::string& e);
    void setAddress(const std::string& a);

    void addScore(const Score& s);
    void addTimetable(const Timetable& t);
};

#endif