#pragma once
#include <string>
using namespace std;

class Score {
private:
    string subject;
    double grade;

public:
    Score();
    Score(string subject, double grade);
    void display();
};
