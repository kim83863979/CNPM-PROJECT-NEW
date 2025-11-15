#include "Admin.h"   
#include "Student.h" 
#include "Account.h" 

#include <iostream>  
#include <string>    
#include <vector>    
using namespace std;


Admin::Admin(const string& id, const string& name, int level) {
    this->adminID = id;
    this->fullName = name;
    this->adminLevel = level;
}

string Admin::getFullName() const {
    return this->fullName;
}

/**
 * 1. TÌM KIẾM TÀI KHOẢN SINH VIÊN
 */
void Admin::searchStudentAccount(const vector<Student>& dsSinhVien) {
    string idCanTim;
    cout << "+---------------------------------------+" << endl;
    cout << "|           TIM KIEM SINH VIEN          |" << endl;
    cout << "+---------------------------------------+" << endl;
    cout << "Nhap Ma So Sinh Vien (MSSV) can tim: ";

    getline(cin, idCanTim);

    int index = findStudentIndex(dsSinhVien, idCanTim);

    if (index != -1) {
        cout << "--- Tim Thay Sinh Vien ---" << endl;
        cout << "MSSV:         " << dsSinhVien[index].studentID << endl;
        cout << "Ho ten:       " << dsSinhVien[index].fullName << endl;
        cout << "Lop:          " << dsSinhVien[index].className << endl;
        cout << "Chuyen nganh: " << dsSinhVien[index].major << endl;
        cout << "Trang thai:   " << dsSinhVien[index].status << endl;
    } else {
        cout << "Loi: Khong tim thay sinh vien voi MSSV \"" << idCanTim << "\"." << endl;
    }
    
    cout << "Nhan Enter de tiep tuc...";
    cin.get(); 
}


/**
 * 2. TẠO TÀI KHOẢN SINH VIÊN MỚI
 */
void Admin::createStudentAccount(vector<Student>& dsSinhVien, vector<Account>& dsTaiKhoan) {
    Student svMoi;
    Account tkMoi;

    cout << "+---------------------------------------+" << endl;
    cout << "|         TAO TAI KHOAN MOI             |" << endl;
    cout << "+---------------------------------------+" << endl;

    while (true) {
        cout << "Nhap MSSV (Ma So Sinh Vien): ";
        getline(cin, svMoi.studentID);

        int index = findStudentIndex(dsSinhVien, svMoi.studentID);
        
        if (index != -1) {
            cout << "Loi: MSSV \"" << svMoi.studentID << "\" da ton tai. Vui long nhap lai." << endl;
        } else {
            break; 
        }
    }
    
    cout << "Nhap Ho va Ten: ";
    getline(cin, svMoi.fullName);
    cout << "Nhap Lop: ";
    getline(cin, svMoi.className);
    cout << "Nhap Chuyen nganh: ";
    getline(cin, svMoi.major);
    svMoi.status = "Dang hoc"; 

    tkMoi.accountID = svMoi.studentID;
    tkMoi.username = svMoi.studentID;
    tkMoi.role = "Student";
    cout << "Nhap Mat khau mac dinh: ";
    getline(cin, tkMoi.password);

    dsSinhVien.push_back(svMoi);
    dsTaiKhoan.push_back(tkMoi);

    cout << "==> Da tao tai khoan cho sinh vien " << svMoi.fullName << " thanh cong." << endl;
    cout << "Nhan Enter de tiep tuc...";
    cin.get();
}


/**
 * 3. XÓA TÀI KHOẢN SINH VIÊN
 */
void Admin::deleteStudentAccount(vector<Student>& dsSinhVien, vector<Account>& dsTaiKhoan) {
    string idCanXoa;
    cout << "+---------------------------------------+" << endl;
    cout << "|             XOA TAI KHOAN             |" << endl;
    cout << "+---------------------------------------+" << endl;
    cout << "Nhap MSSV cua tai khoan can xoa: ";

    getline(cin, idCanXoa);

    int sv_index = findStudentIndex(dsSinhVien, idCanXoa);
    int tk_index = findAccountIndex(dsTaiKhoan, idCanXoa);

    if (sv_index == -1 || tk_index == -1) {
        cout << "Loi: Khong tim thay sinh vien hoac tai khoan voi MSSV \"" << idCanXoa << "\"." << endl;
        cout << "Nhan Enter de tiep tuc...";
        cin.get();
        return; 
    }

    cout << "Tim thay sinh vien: " << dsSinhVien[sv_index].fullName << endl;
    cout << "Ban co chac chan muon xoa tai khoan nay? (c/k): ";
    string xacNhan;
    getline(cin, xacNhan);

    if (xacNhan == "c" || xacNhan == "C") {
        dsSinhVien.erase(dsSinhVien.begin() + sv_index);
        dsTaiKhoan.erase(dsTaiKhoan.begin() + tk_index);
        
        cout << "==> Da xoa tai khoan thanh cong." << endl;
    } else {
        cout << "==> Da huy bo thao tac xoa." << endl;
    }
    cout << "Nhan Enter de tiep tuc...";
    cin.get();
}


/**
 * 4. HIỂN THỊ DANH SÁCH SINH VIÊN
 */
void Admin::displayStudentList(const vector<Student>& dsSinhVien) {
    cout << "+---------------------------------------------------+" << endl;
    cout << "|               DANH SACH SINH VIEN                 |" << endl;
    cout << "+---------------------------------------------------+" << endl;

    if (dsSinhVien.empty()) {
        cout << "Chua co sinh vien nao trong he thong." << endl;
        cout << "Nhan Enter de tiep tuc...";
        cin.get();
        return;
    }

    cout << "MSSV\t\tHo Ten\t\t\tLop\t\tChuyen Nganh" << endl;
    cout << "-----------------------------------------------------" << endl;

    for (int i = 0; i < dsSinhVien.size(); ++i) {
        cout << dsSinhVien[i].studentID << "\t"
             << dsSinhVien[i].fullName << "\t\t"
             << dsSinhVien[i].className << "\t\t"
             << dsSinhVien[i].major << endl;
    }
    
    cout << "+---------------------------------------------------+" << endl;
    cout << "Nhan Enter de tiep tuc...";
    cin.get(); 
}


/**
 * 5. CẬP NHẬT MẬT KHẨU ADMIN
 */
void Admin::updatePassword() {
    string matKhauHienTai, matKhauMoi, xacNhanMK;
    
    cout << "+---------------------------------------+" << endl;
    cout << "|         DOI MAT KHAU ADMIN            |" << endl;
    cout << "+---------------------------------------+" << endl;
    
    cout << "Nhap mat khau hien tai: ";
    getline(cin, matKhauHienTai);
    
    cout << "Nhap mat khau moi (it nhat 8 ky tu): ";
    getline(cin, matKhauMoi);
    cout << "Xac nhan mat khau moi: ";
    getline(cin, xacNhanMK);

    if (matKhauMoi != xacNhanMK) {
        cout << "Loi: Mat khau xac nhan khong khop." << endl;
        cout << "Nhan Enter de tiep tuc...";
        cin.get();
        return;
    }

    if (matKhauMoi.length() < 8) {
        cout << "Loi: Mat khau moi phai co it nhat 8 ky tu." << endl;
        cout << "Nhan Enter de tiep tuc...";
        cin.get();
        return;
    }

    cout << "==> Doi mat khau thanh cong." << endl;
    cout << "Nhan Enter de tiep tuc...";
    cin.get();
}


// --- TRIỂN KHAI CÁC HÀM TRỢ GIÚP (PRIVATE) ---

/**
 * 1. Tìm sinh viên bằng ID, trả về CHỈ SỐ (index)
 * Dùng vòng lặp for đơn giản.
 */
int Admin::findStudentIndex(const vector<Student>& dsSinhVien, const string& id) {
    for (int i = 0; i < dsSinhVien.size(); ++i) {
        if (dsSinhVien[i].studentID == id) {
            return i; 
        }
    }
    return -1; 
}

/**
 * 2. Tìm tài khoản bằng ID, trả về CHỈ SỐ (index)
 */
int Admin::findAccountIndex(const vector<Account>& dsTaiKhoan, const string& id) {
    for (int i = 0; i < dsTaiKhoan.size(); ++i) {
        if (dsTaiKhoan[i].accountID == id) {
            return i; 
        }
    }
    return -1; 