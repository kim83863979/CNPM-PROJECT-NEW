#pragma once
#include <string>
#include <vector>
#include "Timetable.h"
#include "Score.h"
using namespace std;

class Student {
private:
    string id;
    string name;
    string phone;
    string email;

public:
    vector<Timetable> schedule;
    vector<Score> scores;

    Student();
    Student(string id, string name, string phone, string email);

    void viewProfile();
    void updateProfile();
    void viewSchedule();
    void viewScores();

    string getID();
    string getName();
};
