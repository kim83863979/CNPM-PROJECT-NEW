#include "Score.h"
#include <iostream>
#include <iomanip>

Score::Score(const std::string& id, const std::string& name, float val, const std::string& stat)
    : scoreID(id), courseName(name), scoreValue(val), status(stat) {
}

Score::Score(const std::vector<std::string>& fields) {
    // expected: scoreID, courseName, scoreValue, status
    if (fields.size() >= 4) {
        scoreID = fields[0];
        courseName = fields[1];
        try {
            scoreValue = std::stof(fields[2]);
        }
        catch (...) { scoreValue = 0.0f; } // fallback an toàn
        status = fields[3];
    }
    else {
        // fallback khi vector không đủ dữ liệu
        scoreID = "";
        courseName = "";
        scoreValue = 0.0f;
        status = "";
    }
}

void Score::display() const {
    std::cout << "| " << std::left << std::setw(25) << courseName
        << "| " << std::setw(8) << std::fixed << std::setprecision(1) << scoreValue
        << "| " << std::setw(12) << status << " |\n";
}

std::string Score::getScoreID() const { return scoreID; }
std::string Score::getCourseName() const { return courseName; }
float Score::getScore() const { return scoreValue; }
std::string Score::getStatus() const { return status; }

std::string Score::toFileString() const {
    return scoreID + "," + courseName + "," + std::to_string(scoreValue) + "," + status;
}
