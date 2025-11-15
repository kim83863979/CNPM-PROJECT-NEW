#pragma once
#ifndef SCORE_H
#define SCORE_H

#include <string>

using namespace std;

class Score {
private:
    string scoreID;
    string courseName;
    float score;
    string status;

public:
    Score(string id, string name, float scr, string stat);
    void display() const;

    string getScoreID() const;
    string getCourseName() const;
    float getScore() const;
    string getStatus() const;
};

#endif