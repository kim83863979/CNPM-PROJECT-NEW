#include "Student.h"
#include <iostream>
using namespace std;

int main() {
    Student st("S01", "Nguyen Van A", "0909000000", "a@gmail.com");

    st.schedule.push_back(Timetable("Toan", "Thu 2", "7:30"));
    st.schedule.push_back(Timetable("Ly", "Thu 3", "9:30"));

    st.scores.push_back(Score("Toan", 9.0));
    st.scores.push_back(Score("Ly", 8.5));

    st.viewProfile();
    st.viewSchedule();
    st.viewScores();

    return 0;
}
