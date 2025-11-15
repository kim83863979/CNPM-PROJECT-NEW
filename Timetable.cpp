#include "Timetable.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

Timetable::Timetable(std::string id, std::string name, std::string day, std::string time, std::string room)
    : timetableID(id),
    courseName(name),
    dayOfWeek(day),
    time(time),
    room(room)
{ }

void Timetable::display() const {
    cout << "| " << left << setw(20) << this->dayOfWeek;
    cout << "| " << left << setw(15) << this->time;
    cout << "| " << left << setw(30) << this->courseName;
    cout << "| " << left << setw(10) << this->room << " |" << endl;
}

string Timetable::getTimetableID() const { return this->timetableID; }
string Timetable::getCourseName() const { return this->courseName; }
string Timetable::getDayOfWeek() const { return this->dayOfWeek; }
string Timetable::getTime() const { return this->time; }
string Timetable::getRoom() const { return this->room; }