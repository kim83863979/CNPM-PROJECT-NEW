#pragma once
#include <string>

class ConsoleUI {
public:
    static void displayLoginScreen();
    static void getLoginCredentials(std::string& username, std::string& password);
    static void displayStudentMenu(const std::string& studentName, const std::string& studentID);
    static int getStudentChoice();
    static void displayAdminMenu(const std::string& adminName);
    static int getAdminChoice();
    static void showMessage(const std::string& message);
    static std::string promptInput(const std::string& promptMessage);
    static void clearScreen();
    static void pressEnterToContinue();
};


