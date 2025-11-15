// Timetable.h
#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <string>

class Timetable {
private:
    std::string timetableID;
    std::string courseName;
    std::string dayOfWeek;
    std::string time;
    std::string room;

public:
    Timetable(const std::string& id, const std::string& name, 
              const std::string& day, const std::string& t, const std::string& r);
    void display() const;

    std::string getTimetableID() const;
    std::string getCourseName() const;
    std::string getDayOfWeek() const;
    std::string getTime() const;
    std::string getRoom() const;
};

#endif