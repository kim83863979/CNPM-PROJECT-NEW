#pragma once
#include <string>
#include <vector>

class Score {
private:
    std::string scoreID;
    std::string courseName;
    float scoreValue = 0.0f;  // Khởi tạo an toàn
    std::string status;        // e.g., "Approved" / "Pending"

public:
    Score() = default;
    Score(const std::string& id, const std::string& name, float val, const std::string& stat);
    Score(const std::vector<std::string>& fields); // constructor từ vector<string> khi load file

    void display() const;

    std::string getScoreID() const;
    std::string getCourseName() const;
    float getScore() const;
    std::string getStatus() const;

    std::string toFileString() const;
};

