#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class HoaDon {
private:
    struct HoaDonItem {
        string GioChieuSoGhe; // Giờ chiếu + Số ghế (ví dụ: "10:00-20/11/2024+1")
        string CCCD;          // CCCD nhân viên
        double ThanhTien;     // Thành tiền
    };

    vector<HoaDonItem> HoaDonList; // Danh sách các hóa đơn

public:
    HoaDon() {
        DocHoaDon(); // Đọc dữ liệu từ file HoaDon.txt
    }

    // Đọc dữ liệu từ file HoaDon.txt
    void DocHoaDon() {
    ifstream file("HoaDon.txt");
    string line;
    
    while (getline(file, line)) {
        if (line.empty()) continue;

        HoaDonItem item;

        // Đọc thông tin "Gio Chieu + So Ghe"
        if (line.find("Gio Chieu + So Ghe:") != string::npos) {
            item.GioChieuSoGhe = line.substr(line.find(":") + 2); // Lấy thông tin giờ chiếu + số ghế
        }
        
        // Đọc thông tin "CCCD"
        getline(file, line);
        if (line.find("CCCD") != string::npos) {
            item.CCCD = line.substr(line.find(":") + 2);  // Lấy thông tin CCCD nhân viên
        }
        
        // Đọc thông tin "Thanh Tien"
        getline(file, line);
        if (line.find("Thanh Tien") != string::npos) {
            stringstream ss(line.substr(line.find(":") + 2)); // Bỏ qua phần "Thanh Tien:"
            ss >> item.ThanhTien;  // Lấy giá trị thành tiền
        }

        // Đảm bảo rằng item được thêm vào danh sách nếu có đủ thông tin
        HoaDonList.push_back(item);
    }
}


    // Lưu dữ liệu vào file HoaDon.txt
    void LuuHoaDon() {
        ofstream file("HoaDon.txt");
        for (const auto& item : HoaDonList) {
            file << "Gio Chieu + So Ghe: " << item.GioChieuSoGhe << endl;
            file << "CCCD         : " << item.CCCD << endl;
            file << "Thanh Tien   : " << item.ThanhTien << endl;
            file << endl;
        }
    }

    // Kiểm tra vé có tồn tại trong file Ve.txt (dựa vào Giờ chiếu và Số ghế)
    bool KiemTraVe(const string& GioChieuSoGhe) {
        ifstream file("Ve.txt");
        string line;
        bool timThay = false;

        while (getline(file, line)) {
            if (line.find("Gio chieu+So ghe: " + GioChieuSoGhe) != string::npos) {
                timThay = true;
                break; // Tìm thấy vé
            }
        }

        file.close();
        return timThay;
    }

    // Kiểm tra sự tồn tại của nhân viên trong file NhanVien.txt (dựa vào CCCD)
    bool KiemTraNhanVien(const string& CCCD) {
        ifstream file("NhanVien.txt");
        string line;
        bool timThay = false;

        while (getline(file, line)) {
            if (line.find("CCCD         : " + CCCD) != string::npos) {
                timThay = true;
                break; // Tìm thấy CCCD nhân viên
            }
        }

        file.close();
        return timThay;
    }

    // Kiểm tra giờ chiếu + số ghế có tồn tại trong file HoaDon.txt hay không
    bool KiemTraHoaDon(const string& GioChieuSoGhe) {
        ifstream file("HoaDon.txt");
        string line;
        while (getline(file, line)) {
            if (line.find("Gio Chieu + So Ghe: " + GioChieuSoGhe) != string::npos) {
                return true; // Tồn tại hóa đơn với giờ chiếu + số ghế này
            }
        }
        return false;
    }

    // Tính thành tiền (giá vé + giá dịch vụ)
    double TinhThanhTien(const string& GioChieuSoGhe) {
        double giaVe = LayGiaVe(GioChieuSoGhe);
        double giaDichVu = LayGiaDichVu(GioChieuSoGhe);
        return giaVe + giaDichVu; // Thành tiền = giá vé + giá dịch vụ
    }

    double LayGiaVe(const string& GioChieuSoGhe) {
        string gioChieu = GioChieuSoGhe.substr(0, GioChieuSoGhe.find("+"));

        ifstream file("LichChieu.txt");
        string line;
        while (getline(file, line)) {
            if (line.find("Gio chieu    : " + gioChieu) != string::npos) {
                while (getline(file, line)) {
                    if (line.find("Gia ve      :") != string::npos) {
                        stringstream ss(line.substr(line.find(":") + 2));
                        double giaVe;
                        ss >> giaVe;
                        return giaVe;
                    }
                }
            }
        }
        return 0.0;
    }

    double LayGiaDichVu(const string& GioChieuSoGhe) {
        ifstream file("Ve.txt");
        string line;
        while (getline(file, line)) {
            if (line.find("Gio chieu+So ghe: " + GioChieuSoGhe) != string::npos) {
                while (getline(file, line)) {
                    if (line.find("Ten dich vu:") != string::npos) {
                        string dichVu = line.substr(line.find(":") + 2);
                        return LayGiaDichVuTheoTen(dichVu);
                    }
                }
            }
        }
        return 0.0;
    }

    double LayGiaDichVuTheoTen(const string& tenDichVu) {
        ifstream file("DichVu.txt");
        string line;
        while (getline(file, line)) {
            if (line.find("Ten dich vu  : " + tenDichVu) != string::npos) {
                while (getline(file, line)) {
                    if (line.find("Gia dich vu  :") != string::npos) {
                        stringstream ss(line.substr(line.find(":") + 2));
                        double giaDichVu;
                        ss >> giaDichVu;
                        return giaDichVu;
                    }
                }
            }
        }
        return 0.0;
    }

    // Thêm hóa đơn mới
    void ThemHoaDon(const string& GioChieuSoGhe, const string& CCCD) {
        if (KiemTraHoaDon(GioChieuSoGhe)) {
            cout << "Hoa don da ton tai!" << endl << endl;
            return;
        }

        if (!KiemTraVe(GioChieuSoGhe)) {
            cout << "Khong tim thay thong tin ve!" << endl << endl;
            return;
        }

        if (!KiemTraNhanVien(CCCD)) {
            cout << "Khong tim thay nhan vien!" << endl << endl;
            return;
        }

        HoaDonItem newItem;
        newItem.GioChieuSoGhe = GioChieuSoGhe;
        newItem.CCCD = CCCD;
        newItem.ThanhTien = TinhThanhTien(GioChieuSoGhe);

        HoaDonList.push_back(newItem);
        LuuHoaDon();
        cout << "Them hoa don thanh cong!" << endl << endl;
    }

    // Sửa hóa đơn
    void SuaHoaDon(const string& GioChieuSoGhe, const string& GioChieuSoGheMoi, const string& CCCD) {
        for (auto& item : HoaDonList) {
            if (item.GioChieuSoGhe == GioChieuSoGheMoi && GioChieuSoGhe != GioChieuSoGheMoi) {
                cout << "Hoa don voi Gio Chieu + So Ghe nay da ton tai!" << endl << endl;
                return;
            }
        }
        if (!KiemTraVe(GioChieuSoGheMoi)) {
            cout << "Khong tim thay thong tin ve!" << endl << endl;
            return;
        }
        if (!KiemTraNhanVien(CCCD)) {
            cout << "Khong tim thay nhan vien!" << endl << endl;
            return;
        }
        for (auto& item : HoaDonList) {
            if (item.GioChieuSoGhe == GioChieuSoGhe) {
            	item.GioChieuSoGhe = GioChieuSoGheMoi;
                item.CCCD = CCCD;
                item.ThanhTien = TinhThanhTien(GioChieuSoGheMoi);
                LuuHoaDon();
                cout << "Sua hoa don thanh cong!" << endl << endl;
                return;
            }
        }
        cout << "Khong tim thay hoa don!" << endl << endl;
    }

    // Xem danh sách hóa đơn
    void XemHoaDon() {
        if (HoaDonList.empty()) {
            cout << "Khong co hoa don nao!" << endl << endl;
            return;
        }

        for (const auto& item : HoaDonList) {
            cout << "Gio chieu+So ghe: " << item.GioChieuSoGhe << endl;
            cout << "CCCD         : " << item.CCCD << endl;
            cout << "Thanh tien   : " << item.ThanhTien << endl;
            cout << endl;
        }
    }

    // Tìm hóa đơn theo các tiêu chí
    void TimHoaDon(const string& dauVao) {
        bool timThay = false;
        for (const auto& item : HoaDonList) {
            if (item.GioChieuSoGhe == dauVao || item.CCCD == dauVao) {
                cout << "Gio chieu+So ghe: " << item.GioChieuSoGhe << endl;
                cout << "CCCD         : " << item.CCCD << endl;
                cout << "Thanh tien   : " << item.ThanhTien << endl;
                cout << endl;
                timThay = true;
            }
        }
        if (!timThay) {
            cout << "Khong tim thay hoa don!" << endl << endl;
        }
    }

    // Xóa hóa đơn theo giờ chiếu + số ghế
    void XoaHoaDon(const string& GioChieuSoGhe) {
        for (auto it = HoaDonList.begin(); it != HoaDonList.end(); ++it) {
            if (it->GioChieuSoGhe == GioChieuSoGhe) {
                HoaDonList.erase(it);
                LuuHoaDon();
                cout << "Xoa hoa don thanh cong!" << endl << endl;
                return;
            }
        }
        cout << "Khong tim thay hoa don de xoa!" << endl << endl;
    }
};

void QuanLiHoaDon() {
    HoaDon hd;

    string luaChon;
    string gioChieuSoGhe, cccd, GioChieuSoGheMoi;
    double thanhTien;

    	cout << "Quan li hoa don" << endl;
        cout << "1. Tim hoa don" << endl;
        cout << "2. Them hoa don" << endl;
        cout << "3. Xoa hoa don" << endl;
        cout << "4. Sua hoa don" << endl;
        cout << "5. Xem hoa don" << endl;
        cout << "Nhap bat ki de quay lai" << endl;
        cout << "Nhap lua chon: ";
        getline(cin, luaChon);

        if (luaChon == "1") {
            cout << "Nhap (Gio chieu+So ghe/CCCD) de tim: ";
            getline(cin, gioChieuSoGhe);
            hd.TimHoaDon(gioChieuSoGhe);
        } else if (luaChon == "2") {
            cout << "Nhap Gio Chieu + So Ghe de them: ";
            getline(cin, gioChieuSoGhe);
            cout << "Nhap CCCD de them: ";
            getline(cin, cccd);
            hd.ThemHoaDon(gioChieuSoGhe, cccd);
        } else if (luaChon == "3") {
        	cout << "Nhap Gio Chieu + So Ghe can xoa: ";
            getline(cin, gioChieuSoGhe);
            hd.XoaHoaDon(gioChieuSoGhe);
        } else if (luaChon == "4") {
        	cout << "Nhap Gio Chieu + So Ghe: ";
            getline(cin, gioChieuSoGhe);
            cout << "Nhap Gio Chieu + So Ghe Moi: ";
            getline(cin, GioChieuSoGheMoi);
            cout << "Nhap CCCD: ";
            getline(cin, cccd);
            hd.SuaHoaDon(gioChieuSoGhe, GioChieuSoGheMoi, cccd);
        } else if (luaChon == "5") {
             hd.XemHoaDon();
        } else {
        	cout << endl;
		}

}
