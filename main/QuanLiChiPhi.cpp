#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <regex>  // Thêm thư viện regex để kiểm tra định dạng tháng
#include <iomanip> // Thêm thư viện để định dạng dữ liệu

using namespace std;

class ChiPhi {
private:
    // Cấu trúc chi phí theo tháng
    struct ChiPhiItem {
        string month;  // Tháng chi (mm/yyyy)
        double totalExpense;  // Tổng tiền chi (tính từ lương các nhân viên)
    };

    vector<ChiPhiItem> chiPhiList;  // Danh sách chi phí theo tháng

    // Đọc lương từ file NhanVien.txt và tính tổng chi phí cho tháng
    double docLuong() {
        ifstream file("NhanVien.txt");
        if (!file) {
            return 0.0;
        }

        string line;
        double totalExpense = 0.0;
        while (getline(file, line)) {
            if (line.find("Luong") != string::npos) {
                size_t pos = line.find(":");
                if (pos != string::npos) {
                    string luongStr = line.substr(pos + 1);
                    luongStr.erase(0, luongStr.find_first_not_of(" "));
                    double luong = stod(luongStr);
                    totalExpense += luong;  // Cộng dồn vào tổng chi phí
                }
            }
        }
        file.close();
        return totalExpense;  // Trả về tổng chi phí
    }

    // Kiểm tra định dạng tháng "mm/yyyy"
    bool kiemTraThang(const string& month) {
        // Biểu thức chính quy kiểm tra định dạng tháng (mm/yyyy)
        regex pattern(R"(\b(0[1-9]|1[0-2])\/\d{4}\b)");
        return regex_match(month, pattern);  // Kiểm tra xem chuỗi có khớp với định dạng không
    }

public:
    // Constructor khởi tạo
    ChiPhi() {}

    // Hàm thêm chi phí cho tháng
    void themChiPhi(const string& month) {
        // Kiểm tra định dạng tháng
        if (!kiemTraThang(month)) {
            cout << "Thang chi khong hop le! Vui long nhap theo dinh dang mm/yyyy!" << endl << endl;
            return;
        }

        // Tính chi phí cho tháng
        double totalExpense = docLuong();
        
        // Ghi dữ liệu vào file ChiPhi.txt
        ofstream file("ChiPhi.txt", ios::app);
        if (!file) {
            cout << "Khong the mo file de ghi!" << endl << endl;
            return;
        }
        file << "Thang chi: " << month << endl;
        file << "Tien chi: " << fixed << setprecision(2) << totalExpense << endl;
        file << endl;
        file.close();

        cout << "Them chi phi cho thang " << month << " thanh cong!" << endl << endl;
    }

    // Hàm tìm chi phí theo tháng
    void timChiPhi(const string& month) {
        ifstream file("ChiPhi.txt");
        if (!file) {
            cout << "Khong the mo file de doc!" << endl << endl;
            return;
        }

        string line;
        bool found = false;
        while (getline(file, line)) {
            if (line.find("Thang chi: " + month) != string::npos) {
                cout << line << endl;
                if (getline(file, line)) {
                    cout << line << endl;
                }
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Khong tim thay chi phi cho thang " << month << endl << endl;
        }

        file.close();
    }

    // Hàm xóa chi phí theo tháng
    void xoaChiPhi(const string& month) {
        ifstream file("ChiPhi.txt");
        if (!file) {
            cout << "Khong the mo file de doc!" << endl << endl;
            return;
        }

        ofstream tempFile("TempChiPhi.txt");
        if (!tempFile) {
            cout << "Khong the mo file tam de ghi!" << endl << endl;
            return;
        }

        string line;
        bool found = false;
        while (getline(file, line)) {
            if (line.find("Thang chi: " + month) != string::npos) {
                found = true;
                // Bỏ qua dòng này và dòng tiếp theo
                getline(file, line);
            } else {
                tempFile << line << endl;
            }
        }

        file.close();
        tempFile.close();

        remove("ChiPhi.txt");
        rename("TempChiPhi.txt", "ChiPhi.txt");

        if (found) {
            cout << "Xoa chi phi cho thang " << month << " thanh cong!" << endl << endl;
        } else {
            cout << "Khong tim thay chi phi cho thang " << month << endl << endl;
        }
    }

    // Hàm hiển thị tất cả các chi phí đã thêm
    void hienThiChiPhi() {
        ifstream file("ChiPhi.txt");
        if (!file) {
            cout << "Khong the mo file de doc!" << endl << endl;
            return;
        }

        string line;
        if (file.peek() == ifstream::traits_type::eof()) {
            cout << "Chua co chi phi nao!" << endl << endl;
            return;
        }

        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    }
};

void QuanLiChiPhi() {
    ChiPhi cp;
    string luaChon;
    string month;

        cout << "Quan li chi phi" << endl;
        cout << "1. Them chi phi" << endl;
        cout << "2. Tim chi phi" << endl;
        cout << "3. Xoa chi phi" << endl;
        cout << "4. Xem tat ca chi phi" << endl;
        cout << "Nhap bat ki de quay lai" << endl;
        cout << "Nhap lua chon: ";
        getline(cin, luaChon);

        if (luaChon == "1") {
            cout << "Nhap Thang chi (mm/yyyy) de them: ";
            getline(cin, month);
            cp.themChiPhi(month);
        } else if (luaChon == "2") {
            cout << "Nhap Thang chi (mm/yyyy) de tim: ";
            getline(cin, month);
            cp.timChiPhi(month);
        } else if (luaChon == "3") {
            cout << "Nhap Thang chi (mm/yyyy) de xoa: ";
            getline(cin, month);
            cp.xoaChiPhi(month);
        } else if (luaChon == "4") {
            cp.hienThiChiPhi();
        } else {
            cout  << endl;
        }

}
