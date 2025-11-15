#pragma once
#include <string>
using namespace std;

class Timetable {
private:
    string courseName;
    string day;
    string time;

public:
    Timetable();
    Timetable(string c, string d, string t);
    void display();
};