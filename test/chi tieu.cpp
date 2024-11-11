#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>

using namespace std;

class ChiTieu {
private:
    int tongLuongNhanVien;
    const int tienThueMatBang = 30000000; // Ti?n thuê m?t b?ng c? d?nh

public:
    ChiTieu() : tongLuongNhanVien(0) {}

    bool kiemTraDinhDangThangNam(const string& thangNam) {
        regex pattern("^(0[1-9]|1[0-2])/\\d{4}$"); // Ð?nh d?ng mm/yyyy v?i tháng t? 01-12
        if (!regex_match(thangNam, pattern)) {
            cerr << "Dinh dang khong hop le. Vui long nhap theo dinh dang mm/yyyy (VD: 02/2024)." << endl;
            return false;
        }
        return true;
    }

    void docDuLieuLuongNhanVien(const string& tenFile, const string& thangNam) {
        ifstream file(tenFile);
        if (!file) {
            cerr << "Khong the mo file: " << tenFile << endl;
            return;
        }

        string dong;
        regex pattern("Thang lam viec: (\\d{2}/\\d{4}) - Luong thang: ([\\d,]+) VND");
        smatch match;

        while (getline(file, dong)) {
            if (regex_search(dong, match, pattern) && match[1] == thangNam) {
                string luongStr = match[2];
                luongStr.erase(remove(luongStr.begin(), luongStr.end(), ','), luongStr.end()); // Lo?i b? d?u ph?y
                tongLuongNhanVien += stoi(luongStr);
            }
        }
        file.close();
    }

    int tinhTongChiTieu() const {
        return tongLuongNhanVien + tienThueMatBang;
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

    void inChiTieu(const string& thangNam) const {
        cout << "Chi tieu thang " << thangNam << ":" << endl;
        cout << "  Tong luong nhan vien: " << dinhDangTien(tongLuongNhanVien) << " VND" << endl;
        cout << "  Tien thue mat bang: " << dinhDangTien(tienThueMatBang) << " VND" << endl;
        cout << "  Tong chi tieu: " << dinhDangTien(tinhTongChiTieu()) << " VND" << endl;
    }

    void luuChiTieuVaoFile(const string& thangNam) const {
        ofstream file("chitieu.txt", ios::app); // M? file ? ch? d? ghi b? sung (append)
        if (!file) {
            cerr << "Khong the mo file chitieu.txt de ghi." << endl;
            return;
        }

        file << "Chi tieu thang " << thangNam << ":\n";
        file << "  Tong luong nhan vien: " << dinhDangTien(tongLuongNhanVien) << " VND\n";
        file << "  Tien thue mat bang: " << dinhDangTien(tienThueMatBang) << " VND\n";
        file << "  Tong chi tieu: " << dinhDangTien(tinhTongChiTieu()) << " VND\n";
        file << "-----------------------------------\n";

        file.close();
        cout << "Da luu chi tieu vao file chitieu.txt.\n";
    }
};

int main() {
    string thangNam;
    ChiTieu chiTieu;
    
    do {
        cout << "Nhap thang va nam (mm/yyyy): ";
        cin >> thangNam;
    } while (!chiTieu.kiemTraDinhDangThangNam(thangNam));

    chiTieu.docDuLieuLuongNhanVien("soluongnhanvien.txt", thangNam);
    chiTieu.inChiTieu(thangNam);
    chiTieu.luuChiTieuVaoFile(thangNam);

    return 0;
}

