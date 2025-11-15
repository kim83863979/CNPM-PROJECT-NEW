#pragma once
#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <string>

using namespace std;

class Timetable {
private:
    string timetableID;
    string courseName;
    string dayOfWeek;
    string time;
    string room;

public:
    Timetable(string id, string name, string day, string time, string room);
    void display() const;

    string getTimetableID() const;
    string getCourseName() const;
    string getDayOfWeek() const;
    string getTime() const;
    string getRoom() const;
};

#endif