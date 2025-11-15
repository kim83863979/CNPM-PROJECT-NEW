// Score.h
#ifndef SCORE_H
#define SCORE_H

#include <string>

class Score {
private:
    std::string scoreID;
    std::string courseName;
    float score;
    std::string status;

public:
    Score(const std::string& id, const std::string& name, float scr, const std::string& stat);
    void display() const;

    std::string getScoreID() const;
    std::string getCourseName() const;
    float getScore() const;
    std::string getStatus() const;
};

#endif