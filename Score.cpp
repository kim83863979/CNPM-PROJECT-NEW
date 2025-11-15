#include "Score.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

Score::Score(string id, string name, float scr, string stat)
    : scoreID(id),
    courseName(name),
    score(scr),
    status(stat)
{ }
void Score::display() const {
    cout << "| " << left << setw(30) << this->courseName;
    if (this->status == "Pending") {
        cout << "| " << left << setw(15) << "Pending approval" << " |" << endl;
    }
    else {
        cout << "| " << left << setw(15) << fixed << setprecision(1) << this->score << " |" << endl;
    }
}

string Score::getScoreID() const { return this->scoreID; }
string Score::getCourseName() const { return this->courseName; }
float Score::getScore() const { return this->score; }
string Score::getStatus() const { return this->status; }