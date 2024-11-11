#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>

using namespace std;

class DoanhThu {
private:
    int soLuongVe;
    int soLuongDoAn;
    int giaVe;
    int giaDoAn;

public:
    DoanhThu() : soLuongVe(0), soLuongDoAn(0), giaVe(0), giaDoAn(0) {}

    bool kiemTraDinhDangThangNam(const string& thangNam) {
        regex pattern("^(0[1-9]|1[0-2])/\\d{4}$"); // Ð?nh d?ng mm/yyyy v?i tháng t? 01-12
        if (!regex_match(thangNam, pattern)) {
            cerr << "Dinh dang khong hop le. Vui long nhap theo dinh dang mm/yyyy (VD: 02/2024)." << endl;
            return false;
        }
        return true;
    }

    void docDuLieuVe(const string& tenFile, const string& thangNam) {
        ifstream file(tenFile);
        if (!file) {
            cerr << "Khong the mo file: " << tenFile << endl;
            return;
        }

        string dong;
        regex pattern("(\\d{2}/\\d{4}) : (\\d+) ve \\((\\d+) VND/ 1 ve\\)");
        smatch match;

        while (getline(file, dong)) {
            if (regex_search(dong, match, pattern) && match[1] == thangNam) {
                soLuongVe = stoi(match[2]);
                giaVe = stoi(match[3]);
                break;
            }
        }
        file.close();
    }

    void docDuLieuDoAn(const string& tenFile, const string& thangNam) {
        ifstream file(tenFile);
        if (!file) {
            cerr << "Khong the mo file: " << tenFile << endl;
            return;
        }

        string dong;
        regex pattern("(\\d{2}/\\d{4}) : (\\d+) do an \\((\\d+) VND/ 1 do an\\)");
        smatch match;

        while (getline(file, dong)) {
            if (regex_search(dong, match, pattern) && match[1] == thangNam) {
                soLuongDoAn = stoi(match[2]);
                giaDoAn = stoi(match[3]);
                break;
            }
        }
        file.close();
    }

    int tinhDoanhThuVe() const {
        return soLuongVe * giaVe;
    }

    int tinhDoanhThuDoAn() const {
        return soLuongDoAn * giaDoAn;
    }

    int tinhTongDoanhThu() const {
        return tinhDoanhThuVe() + tinhDoanhThuDoAn();
    }

    string dinhDangTien(int soTien) const {
        stringstream ss;
        ss << soTien;
        string strTien = ss.str();
        int n = strTien.length();
        
        // Thêm d?u ch?m t? bên ph?i sang trái c? m?i 3 ch? s?
        for (int i = n - 3; i > 0; i -= 3) {
            strTien.insert(i, ".");
        }
        
        return strTien;
    }

    void inDoanhThu(const string& thangNam) const {
        cout << "Doanh thu thang " << thangNam << ":" << endl;
        cout << "  Doanh thu ve: " << dinhDangTien(tinhDoanhThuVe()) << " VND" << endl;
        cout << "  Doanh thu do an: " << dinhDangTien(tinhDoanhThuDoAn()) << " VND" << endl;
        cout << "  Tong doanh thu: " << dinhDangTien(tinhTongDoanhThu()) << " VND" << endl;
    }

    void luuDoanhThuVaoFile(const string& thangNam) const {
        ofstream file("doanhthu.txt", ios::app); // M? file ? ch? d? ghi b? sung (append)
        if (!file) {
            cerr << "Khong the mo file doanhthu.txt de ghi." << endl;
            return;
        }

        file << "Doanh thu thang " << thangNam << ":\n";
        file << "  Doanh thu ve: " << dinhDangTien(tinhDoanhThuVe()) << " VND\n";
        file << "  Doanh thu do an: " << dinhDangTien(tinhDoanhThuDoAn()) << " VND\n";
        file << "  Tong doanh thu: " << dinhDangTien(tinhTongDoanhThu()) << " VND\n";
        file << "-----------------------------------\n";

        file.close();
        cout << "Da luu doanh thu vao file doanhthu.txt.\n";
    }
};

int main() {
    string thangNam;
    DoanhThu doanhThu;
    
    do {
        cout << "Nhap thang va nam (mm/yyyy): ";
        cin >> thangNam;
    } while (!doanhThu.kiemTraDinhDangThangNam(thangNam));

    doanhThu.docDuLieuVe("soluongve.txt", thangNam);
    doanhThu.docDuLieuDoAn("soluongdoan.txt", thangNam);
    doanhThu.inDoanhThu(thangNam);
    doanhThu.luuDoanhThuVaoFile(thangNam);

    return 0;
}

