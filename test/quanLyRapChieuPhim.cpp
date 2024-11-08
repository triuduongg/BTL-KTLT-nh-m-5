#include <iostream>
#include <vector>
#include <string>

using namespace std;
// Lop Quay
class Quay {
private:
    int soQuay;
    string leTan;
    string tinhTrang;

public:
    // Constructor
    Quay(int so, string leTan, string tinhTrang) {
        this->soQuay = so;
        this->leTan = leTan;
        this->tinhTrang = tinhTrang;
    }

    // Ham hien thi thong tin quay
    void hienThiThongTin() {
        cout << "So Quay: " << soQuay << endl;
        cout << "Le Tan: " << leTan << endl;
        cout << "Tinh Trang: " << tinhTrang << endl;
    }
};

// Lop Chi nhanh
class ChiNhanh {
private:
    int soChiNhanh;
    string nguoiQuanLy;
    string diaChi;

public:
    // Constructor
    ChiNhanh(int so, string quanLy, string diaChi) {
        this->soChiNhanh = so;
        this->nguoiQuanLy = quanLy;
        this->diaChi = diaChi;
    }

    // Ham hien thi thong tin chi nhanh
    void hienThiThongTin() {
        cout << "So Chi Nhanh: " << soChiNhanh << endl;
        cout << "Nguoi Quan Ly: " << nguoiQuanLy << endl;
        cout << "Dia Chi: " << diaChi << endl;
    }
};

int main() {
    // T?o các vector d? luu tr? qu?y và chi nhánh
    vector<Quay> danhSachQuay;
    vector<ChiNhanh> danhSachChiNhanh;

    int luaChon;
    do {
        cout << "\n==== Quan Ly Rap Chieu Phim ====" << endl;
        cout << "1. Them Quay" << endl;
        cout << "2. Hien Thi Danh Sach Quay" << endl;
        cout << "3. Them Chi Nhanh" << endl;
        cout << "4. Hien Thi Danh Sach Chi Nhanh" << endl;
        cout << "5. Thoat" << endl;
        cout << "Lua chon cua ban: ";
        cin >> luaChon;

        if (luaChon == 1) {
            int soQuay;
            string leTan, tinhTrang;
            cout << "Nhap so quay: ";
            cin >> soQuay;
            cin.ignore(); // Xóa ký t? newline còn l?i
            cout << "Nhap ten le tan: ";
            getline(cin, leTan);
            cout << "Nhap tinh trang quay: ";
            getline(cin, tinhTrang);

            Quay q(soQuay, leTan, tinhTrang);
            danhSachQuay.push_back(q);
            cout << "Da them quay thanh cong!" << endl;
        }
        else if (luaChon == 2) {
            cout << "\n--- Danh Sach Quay ---" << endl;
            for (auto &quay : danhSachQuay) {
                quay.hienThiThongTin();
                cout << "-----------------------" << endl;
            }
        }
        else if (luaChon == 3) {
            int soChiNhanh;
            string nguoiQuanLy, diaChi;
            cout << "Nhap so chi nhanh: ";
            cin >> soChiNhanh;
            cin.ignore(); // Xóa ký t? newline còn l?i
            cout << "Nhap ten nguoi quan ly: ";
            getline(cin, nguoiQuanLy);
            cout << "Nhap dia chi chi nhanh: ";
            getline(cin, diaChi);

            ChiNhanh cn(soChiNhanh, nguoiQuanLy, diaChi);
            danhSachChiNhanh.push_back(cn);
            cout << "Da them chi nhanh thanh cong!" << endl;
        }
        else if (luaChon == 4) {
            cout << "\n--- Danh Sach Chi Nhanh ---" << endl;
            for (auto &chiNhanh : danhSachChiNhanh) {
                chiNhanh.hienThiThongTin();
                cout << "----------------------------" << endl;
            }
        }
        else if (luaChon == 5) {
            cout << "Cam on ban da su dung chuong trinh!" << endl;
        }
        else {
            cout << "Lua chon khong hop le. Vui long thu lai." << endl;
        }

    } while (luaChon != 5);

    return 0;
}

