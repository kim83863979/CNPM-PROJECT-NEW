#pragma once
#include <string>
#include <vector>
#include "Timetable.h"
#include "Score.h"
#include "Account.h"
#include "ConsoleUI.h"

class Student {
private:
    std::string id;
    std::string name;
    std::string phone;
    std::string email;

    // --- THONG TIN SINH VIEN CHI TIET ---
    std::string dateOfBirth;
    std::string gender;
    std::string className;
    std::string major;
    std::string course;
    std::string academicStatus;
    // ------------------------------------

    std::string linkedAccountID;
    Account* account;

    std::vector<Timetable> schedule;
    std::vector<Score> scores;

public:
    Student();

    // Constructor full thong tin (10 truong thong tin + Account*)
    Student(const std::string& id, const std::string& name, const std::string& phone,
        const std::string& email, const std::string& dob, const std::string& gender,
        const std::string& cls, const std::string& major, const std::string& course,
        const std::string& status, Account* acc = nullptr);

    // constructor from file fields
    Student(const std::vector<std::string>& fields);

    void setAccount(Account* acc);
    void setLinkedAccountID(const std::string& accID);

    Account* getAccount() const;
    std::string getAccountID() const;

    void viewProfile() const;
    void updateProfile();
    void viewSchedule() const;
    void viewScores() const;
    bool changePassword(const std::string& oldPass, const std::string& newPass);

    void addScore(const Score& sc);
    void addTimetable(const Timetable& t);
    const std::vector<Score>& getScores() const;
    const std::vector<Timetable>& getSchedule() const;

    std::string toFileString() const;

    std::string getID() const;
    std::string getName() const;
    std::string getPhone() const;
    std::string getEmail() const;
    std::string getDateOfBirth() const;
    std::string getGender() const;
    std::string getClassName() const;
    std::string getMajor() const;
    std::string getCourse() const;
    std::string getAcademicStatus() const;
};
