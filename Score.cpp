#include "Score.h"
#include <iostream>
using namespace std;

Score::Score() {}

Score::Score(string subject, double grade)
    : subject(subject), grade(grade) {
}

void Score::display() {
    cout << subject << ": " << grade << endl;
}
