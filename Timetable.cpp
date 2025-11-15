#include "Timetable.h"
#include <iostream>
using namespace std;

Timetable::Timetable() {}

Timetable::Timetable(string c, string d, string t)
    : courseName(c), day(d), time(t) {
}

void Timetable::display() {
    cout << courseName << " | " << day << " | " << time << endl;
}
