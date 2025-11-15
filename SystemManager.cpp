#include "SystemManager.h"

// Bao gồm các thư viện chuẩn cho I/O
#include <fstream>  // Để đọc/ghi file (ifstream, ofstream)
#include <sstream>  // Để phân tích chuỗi (stringstream)
#include <iostream> // Chỉ dùng nếu cần debug (nên dùng ConsoleUI::showMessage)

SystemManager::SystemManager() : DATA_FILE("student_data.txt")
{
    this->currentUser = nullptr;
}

// Vòng lặp chính của chương trình.
*/
    void SystemManager::run()
{
    loadData(); // (I/O 1.1) Tải dữ liệu khi khởi động
    ConsoleUI::showMessage("CHAO MUNG DEN VOI HE THONG QUAN LY SINH VIEN");

    while (true)
    {
        bool loggedIn = handleLogin(); // (Controller 2.2) Bắt đầu luồng đăng nhập

        if (!loggedIn)
        {
            // Nếu handleLogin() trả về false (do sai 5 lần)
            ConsoleUI::showMessage("Dang nhap that bai qua 5 lan. Thoat chuong trinh.");
            break; // Thoát khỏi vòng lặp 'while(true)'
        }

        // Nếu đăng nhập thành công, kiểm tra vai trò
        if (currentUser->getRole() == "Student")
        {
            showStudentMenu(); // (Controller 2.4)
        }
        else if (currentUser->getRole() == "Admin")
        {
            showAdminMenu(); // (Controller 2.4)
        }

        // Sau khi showStudentMenu() hoặc showAdminMenu() kết thúc (nghĩa là user chọn 0. Đăng xuất)
        handleLogout(); // (Controller 2.3)

        // Hỏi người dùng muốn thoát hẳn hay đăng nhập lại
        string choice = ConsoleUI::promptInput("Ban co muon thoat khoi he thong? (y/n): ");
        if (choice == "y" || choice == "Y")
        {
            break; // Thoát khỏi vòng lặp 'while(true)'
        }
        // Nếu chọn 'n', vòng lặp tiếp tục và quay lại màn hình handleLogin()
    }

    // Trước khi chương trình kết thúc
    ConsoleUI::showMessage("Dang luu du lieu... Cam on da su dung!");
    saveData(); // (I/O 1.2) Lưu tất cả thay đổi
}

/**
 * @brief (Controller 2.2) Xử lý đăng nhập, kiểm tra 5 lần sai.
 */
bool SystemManager::handleLogin()
{
    for (int attempts = 0; attempts < 5; ++attempts)
    {
        ConsoleUI::displayLoginScreen();                                    // Gọi hàm của Người 2
        std::pair<string, string> creds = ConsoleUI::getLoginCredentials(); // Gọi hàm của Người 2

        string username = creds.first;
        string password = creds.second;

        // 1. Tìm trong danh sách Sinh viên
        for (auto &student : allStudents)
        {
            // Lấy tài khoản của sinh viên VÀ gọi hàm login() của Người 1
            if (student.getAccount().getAccountID() == username && student.getAccount().login(username, password))
            {
                this->currentUser = &student.getAccount(); // Lưu trạng thái đăng nhập
                ConsoleUI::showMessage("Dang nhap thanh cong voi vai tro: SINH VIEN");
                return true; // Đăng nhập thành công
            }
        }

        // 2. Tìm trong danh sách Admin
        for (auto &admin : allAdmins)
        {
            // Lấy tài khoản của admin VÀ gọi hàm login() của Người 1
            if (admin.getAccount().getAccountID() == username && admin.getAccount().login(username, password))
            {
                this->currentUser = &admin.getAccount(); // Lưu trạng thái đăng nhập
                ConsoleUI::showMessage("Dang nhap thanh cong voi vai tro: QUAN TRI VIEN");
                return true; // Đăng nhập thành công
            }
        }

        // Nếu không tìm thấy hoặc sai mật khẩu
        ConsoleUI::showMessage("LOI: Ten dang nhap hoac mat khau khong dung. Con lai " + std::to_string(4 - attempts) + " lan thu.");
    }

    return false; // Trả về false nếu thất bại cả 5 lần
}

/**
 * @brief (Controller 2.3) Xử lý đăng xuất.
 */
void SystemManager::handleLogout()
{
    this->currentUser = nullptr; // Xóa trạng thái đăng nhập
    ConsoleUI::showMessage("Da dang xuat thanh cong.");
}

/**
 * @brief (Controller 2.4) Hiển thị và xử lý menu Student.
 */
void SystemManager::showStudentMenu()
{
    // Phải tìm đối tượng Student đầy đủ từ con trỏ currentUser (chỉ là Account)
    Student *currentStudent = nullptr;
    for (auto &student : allStudents)
    {
        if (student.getAccount().getAccountID() == this->currentUser->getAccountID())
        {
            currentStudent = &student;
            break;
        }
    }

    if (currentStudent == nullptr)
    {
        ConsoleUI::showMessage("LOI NGHIEM TRONG: Khong tim thay du lieu sinh vien tuong ung.");
        return;
    }

    bool keepMenuOpen = true;
    while (keepMenuOpen)
    {
        ConsoleUI::displayStudentMenu(currentStudent->getFullName()); // Gọi hàm Người 2
        int choice = ConsoleUI::getStudentChoice();                   // Gọi hàm Người 2

        switch (choice)
        {
        case 1:
            currentStudent->viewProfile();
            break; // Gọi hàm Người 3
        case 2:
            currentStudent->updateProfile();
            break; // Gọi hàm Người 3
        case 3:
            currentStudent->viewSchedule();
            break; // Gọi hàm Người 3
        case 4:
            currentStudent->viewScores();
            break; // Gọi hàm Người 3
        case 5:
            currentStudent->updatePassword();
            break; // Gọi hàm Người 3
        case 0:
            keepMenuOpen = false; // Thoát vòng lặp menu
            break;
        default:
            ConsoleUI::showMessage("Lua chon khong hop le. Vui long chon tu 0-5.");
        }
    }
}

/**
 * @brief (Controller 2.4) Hiển thị và xử lý menu Admin.
 */
void SystemManager::showAdminMenu()
{
    // Tìm đối tượng Admin đầy đủ
    Admin *currentAdmin = nullptr;
    for (auto &admin : allAdmins)
    {
        if (admin.getAccount().getAccountID() == this->currentUser->getAccountID())
        {
            currentAdmin = &admin;
            break;
        }
    }

    if (currentAdmin == nullptr)
    {
        ConsoleUI::showMessage("LOI NGHIEM TRONG: Khong tim thay du lieu admin tuong ung.");
        return;
    }

    bool keepMenuOpen = true;
    while (keepMenuOpen)
    {
        ConsoleUI::displayAdminMenu(currentAdmin->getFullName()); // Gọi hàm Người 2
        int choice = ConsoleUI::getAdminChoice();                 // Gọi hàm Người 2

        switch (choice)
        {
        case 1:
            currentAdmin->searchStudentAccount(allStudents);
            break; // Gọi hàm Người 4
        case 2:
            currentAdmin->createStudentAccount(allStudents);
            break; // Gọi hàm Người 4
        case 3:
            currentAdmin->deleteStudentAccount(allStudents);
            break; // Gọi hàm Người 4
        case 4:
            currentAdmin->displayStudentList(allStudents);
            break; // Gọi hàm Người 4
        case 5:
            currentAdmin->updatePassword();
            break; // Gọi hàm Người 4
        case 0:
            keepMenuOpen = false; // Thoát vòng lặp menu
            break;
        default:
            ConsoleUI::showMessage("Lua chon khong hop le. Vui long chon tu 0-5.");
        }
    }
}

// --- PHẦN I/O (PHỨC TẠP NHẤT) ---

/**
 * @brief (I/O 1.2) Ghi tất cả dữ liệu từ vector vào file text.
 * YÊU CẦU: Các lớp (Người 1, 3, 4) phải cung cấp hàm `toFileString()`
 * để chuyển đối tượng thành chuỗi theo định dạng đã thống nhất.
 */
void SystemManager::saveData()
{
    std::ofstream file(DATA_FILE); // Mở file để ghi (sẽ GHI ĐÈ toàn bộ)
    if (!file.is_open())
    {
        ConsoleUI::showMessage("LOI HE THONG: Khong the mo file " + DATA_FILE + " de luu du lieu.");
        return;
    }

    // 1. Lưu [ACCOUNTS]
    file << "[ACCOUNTS]\n";
    for (const auto &student : allStudents)
    {
        file << student.getAccount().toFileString() << "\n"; // Giả định: "SV001,pass123,Student"
    }
    for (const auto &admin : allAdmins)
    {
        file << admin.getAccount().toFileString() << "\n"; // Giả định: "admin,adminpass,Admin"
    }

    // 2. Lưu [STUDENTS]
    file << "[STUDENTS]\n";
    for (const auto &student : allStudents)
    {
        file << student.toFileString() << "\n"; // Giả định: "SV001,Nguyen Van A,01/01/2000,..."
    }

    // 3. Lưu [ADMINS]
    file << "[ADMINS]\n";
    for (const auto &admin : allAdmins)
    {
        file << admin.toFileString() << "\n"; // Giả định: "admin,Quan Tri Vien,1"
    }

    // 4. Lưu [SCORES] (Phải lưu kèm ID sinh viên)
    file << "[SCORES]\n";
    for (const auto &student : allStudents)
    {
        string studentID = student.getStudentID();
        for (const auto &score : student.getScores())
        {                                                             // Người 3 phải có hàm getScores()
            file << studentID << "," << score.toFileString() << "\n"; // Giả định: "SV001,CS101,8.5,Passed"
        }
    }

    // 5. Lưu [TIMETABLES] (Tương tự Scores)
    file << "[TIMETABLES]\n";
    for (const auto &student : allStudents)
    {
        string studentID = student.getStudentID();
        for (const auto &item : student.getSchedule())
        {                                                            // Người 3 phải có hàm getSchedule()
            file << studentID << "," << item.toFileString() << "\n"; // Giả định: "SV001,CS101,Mon,07:30,A101"
        }
    }

    file.close();
}

/**
 * @brief (I/O 1.1) Đọc file text và nạp vào các vector.
 * YÊU CẦU: Các lớp (Người 1, 3, 4) phải cung cấp hàm dựng (Constructor)
 * nhận `vector<string>` để tạo đối tượng từ dữ liệu đã phân tích.
 */
void SystemManager::loadData()
{
    std::ifstream file(DATA_FILE);
    if (!file.is_open())
    {
        ConsoleUI::showMessage("Thong bao: Khong tim thay file du lieu. Mot file moi se duoc tao khi thoat.");
        return;
    }

    string line;
    string currentSection = "";
    vector<Account> tempAccounts; // Vector tạm để lưu Account

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue; // Bỏ qua dòng trống

        // 1. Kiểm tra xem có phải là tiêu đề section không
        if (line[0] == '[' && line.back() == ']')
        {
            currentSection = line;
            continue;
        }

        // 2. Phân tích (parse) dòng dữ liệu
        std::stringstream ss(line);
        string field;
        vector<string> fields;
        while (std::getline(ss, field, ','))
        { // Giả sử dùng dấu phẩy (,)
            fields.push_back(field);
        }

        if (fields.empty())
            continue;

        // 3. Tạo đối tượng dựa trên section hiện tại
        try
        {
            if (currentSection == "[ACCOUNTS]")
            {
                // Giả định: Constructor Account(id, pass, role) (Người 1)
                tempAccounts.push_back(Account(fields[0], fields[1], fields[2]));
            }
            else if (currentSection == "[STUDENTS]")
            {
                // Giả định: Constructor Student(vector<string> fields) (Người 3)
                allStudents.push_back(Student(fields));
            }
            else if (currentSection == "[ADMINS]")
            {
                // Giả định: Constructor Admin(vector<string> fields) (Người 4)
                allAdmins.push_back(Admin(fields));
            }
            else if (currentSection == "[SCORES]")
            {
                string studentID = fields[0];
                vector<string> scoreData(fields.begin() + 1, fields.end()); // Dữ liệu điểm bắt đầu từ fields[1]
                // Giả định: Constructor Score(vector<string> fields) (Người 1)
                Score newScore(scoreData);

                // Tìm sinh viên và thêm điểm
                for (auto &student : allStudents)
                {
                    if (student.getStudentID() == studentID)
                    {
                        student.addScore(newScore); // Người 3 phải có hàm addScore()
                        break;
                    }
                }
            }
            else if (currentSection == "[TIMETABLES]")
            {
                string studentID = fields[0];
                vector<string> scheduleData(fields.begin() + 1, fields.end());
                // Giả định: Constructor Timetable(vector<string> fields) (Người 1)
                Timetable newItem(scheduleData);

                // Tìm sinh viên và thêm lịch học
                for (auto &student : allStudents)
                {
                    if (student.getStudentID() == studentID)
                    {
                        student.addTimetable(newItem); // Người 3 phải có hàm addTimetable()
                        break;
                    }
                }
            }
        }
        catch (const std::exception &e)
        {
            ConsoleUI::showMessage("LOI: Du lieu trong file bi hong hoac khong dung dinh dang tai dong: " + line);
        }
    } // Hết vòng lặp while(getline)

    // 4. Gán Account (từ vector tạm) vào các đối tượng Student và Admin
    for (auto &student : allStudents)
    {
        for (const auto &acc : tempAccounts)
        {
            if (student.getAccountID() == acc.getAccountID())
            {
                student.setAccount(acc); // Người 3 phải có hàm setAccount()
                break;
            }
        }
    }
    for (auto &admin : allAdmins)
    {
        for (const auto &acc : tempAccounts)
        {
            if (admin.getAccountID() == acc.getAccountID())
            {
                admin.setAccount(acc); // Người 4 phải có hàm setAccount()
                break;
            }
        }
    }

    file.close();
    ConsoleUI::showMessage("Da tai du lieu tu file thanh cong.");
}