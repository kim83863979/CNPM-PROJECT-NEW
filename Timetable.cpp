#include "Timetable.h"
#include <iostream>
#include <iomanip>

Timetable::Timetable(const std::string& id, const std::string& name,
    const std::string& day, const std::string& t,
    const std::string& r)
    : timetableID(id), courseName(name), dayOfWeek(day), time(t), room(r) {
}

Timetable::Timetable(const std::vector<std::string>& fields) {
    // expected: timetableID, courseName, dayOfWeek, time, room
    if (fields.size() >= 5) {
        timetableID = fields[0];
        courseName = fields[1];
        dayOfWeek = fields[2];
        time = fields[3];
        room = fields[4];
    }
}

void Timetable::display() const {
    std::cout << "| " << std::left << std::setw(20) << courseName
        << "| " << std::setw(8) << dayOfWeek
        << "| " << std::setw(8) << time
        << "| " << std::setw(8) << room << " |\n";
}

std::string Timetable::getTimetableID() const { return timetableID; }
std::string Timetable::getCourseName() const { return courseName; }
std::string Timetable::getDayOfWeek() const { return dayOfWeek; }
std::string Timetable::getTime() const { return time; }
std::string Timetable::getRoom() const { return room; }

std::string Timetable::toFileString() const {
    return timetableID + "," + courseName + "," + dayOfWeek + "," + time + "," + room;
}

