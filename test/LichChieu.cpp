#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

class LichChieu {
private:
    struct LichChiTiet {
        string GioChieu;   // Giờ chiếu (hh:mm-dd/mm/yyyy)
        string TenPhim;    // Tên phim
        string GiaVe;      // Giá vé
    };

    vector<LichChiTiet> DanhSachLichChieu; // Vector chứa các lịch chiếu

public:
    LichChieu() {
        DocLichChieu(); // Đọc thông tin lịch chiếu từ file
    }

    // Hàm kiểm tra năm nhuận
    bool KiemTraNamNhuan(int nam) const {
        return (nam % 4 == 0 && (nam % 100 != 0 || nam % 400 == 0));
    }

    // Hàm kiểm tra tính hợp lệ của giờ chiếu (hh:mm-dd/mm/yyyy)
    bool KiemTraGioChieu(const string& gioChieu) const {
        if (gioChieu.length() != 16) return false;
        if (gioChieu[2] != ':' || gioChieu[5] != '-' || gioChieu[8] != '/' || gioChieu[11] != '/')
            return false;

        // Kiểm tra giờ và phút
        int gio = stoi(gioChieu.substr(0, 2));
        int phut = stoi(gioChieu.substr(3, 2));
        if (gio < 0 || gio > 23 || phut < 0 || phut > 59) return false;

        // Kiểm tra ngày tháng năm
        int ngay = stoi(gioChieu.substr(6, 2));
        int thang = stoi(gioChieu.substr(9, 2));
        int nam = stoi(gioChieu.substr(12, 4));
        if (thang < 1 || thang > 12) return false;

        // Số ngày trong tháng
        int soNgayTrongThang[] = {31, (KiemTraNamNhuan(nam) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (ngay < 1 || ngay > soNgayTrongThang[thang - 1]) return false;

        return true;
    }

    // Hàm kiểm tra tính hợp lệ của giá vé
    bool KiemTraGiaVe(const string& giaVe) const {
        if (giaVe.empty() || giaVe[0] == '0') return false;  // Giá vé không được bắt đầu bằng 0
        for (char c : giaVe) {
            if (!isdigit(c)) return false;  // Kiểm tra xem giá vé có phải số không
        }
        return true;
    }

    // Hàm đọc lịch chiếu từ file
    void DocLichChieu() {
        ifstream file("LichChieu.txt");
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            LichChiTiet lich;
            lich.GioChieu = line.substr(line.find(":") + 2);
            getline(file, line);
            lich.TenPhim = line.substr(line.find(":") + 2);
            getline(file, line);
            lich.GiaVe = line.substr(line.find(":") + 2);
            DanhSachLichChieu.push_back(lich);
        }
    }

    // Hàm lưu lịch chiếu vào file
    void LuuLichChieu() {
        ofstream file("LichChieu.txt");
        for (const auto& lich : DanhSachLichChieu) {
            file << "Gio chieu    : " << lich.GioChieu << endl;
            file << "Ten phim    : " << lich.TenPhim << endl;
            file << "Gia ve      : " << lich.GiaVe << endl;
            file << endl;
        }
    }

    // Hàm thêm lịch chiếu
    void ThemLichChieu(const string& gioChieu, const string& tenPhim, const string& giaVe) {
        if (!KiemTraGioChieu(gioChieu) || !KiemTraGiaVe(giaVe)) {
            cout << "Thong tin khong hop le. Vui long kiem tra lai." << endl << endl;
            return;
        }

        for (const auto& lich : DanhSachLichChieu) {
            if (lich.GioChieu == gioChieu) {
                cout << "Lich chieu da ton tai." << endl << endl;
                return;
            }
        }

        LichChiTiet lichMoi = {gioChieu, tenPhim, giaVe};
        DanhSachLichChieu.push_back(lichMoi);
        LuuLichChieu();
        cout << "Da them lich chieu thanh cong!" << endl << endl;
    }

    // Hàm xóa lịch chiếu
    void XoaLichChieu(const string& gioChieu) {
        for (size_t i = 0; i < DanhSachLichChieu.size(); ++i) {
            if (DanhSachLichChieu[i].GioChieu == gioChieu) {
                DanhSachLichChieu.erase(DanhSachLichChieu.begin() + i);
                LuuLichChieu();
                cout << "Da xoa lich chieu thanh cong!" << endl << endl;
                return;
            }
        }
        cout << "Khong tim thay lich chieu." << endl << endl;
    }

    /// Hàm sửa thông tin lịch chiếu
void SuaLichChieu(const string& gioChieuCu, const string& gioChieuMoi, const string& tenPhimMoi, const string& giaVeMoi) {
    if (!KiemTraGioChieu(gioChieuMoi) || !KiemTraGiaVe(giaVeMoi)) {
        cout << "Thong tin khong hop le. Vui long kiem tra lai." << endl << endl;
        return;
    }

    // Kiểm tra xem giờ chiếu mới đã tồn tại trong danh sách hay chưa
    for (const auto& lich : DanhSachLichChieu) {
        if (lich.GioChieu == gioChieuMoi && gioChieuMoi != gioChieuCu) {
            cout << "Lich chieu moi da ton tai!" << endl << endl;
            return;
        }
    }

    // Tìm và sửa thông tin lịch chiếu nếu tìm thấy giờ chiếu cũ
    for (size_t i = 0; i < DanhSachLichChieu.size(); ++i) {
        if (DanhSachLichChieu[i].GioChieu == gioChieuCu) {
            // Sửa thông tin của lịch chiếu
            DanhSachLichChieu[i].GioChieu = gioChieuMoi; // Sửa giờ chiếu
            DanhSachLichChieu[i].TenPhim = tenPhimMoi;  // Sửa tên phim
            DanhSachLichChieu[i].GiaVe = giaVeMoi;      // Sửa giá vé

            // Lưu lại danh sách lịch chiếu sau khi sửa
            LuuLichChieu();
            cout << "Da sua lich chieu thanh cong!" << endl << endl;
            return;
        }
    }

    // Nếu không tìm thấy lịch chiếu với giờ chiếu cũ
    cout << "Khong tim thay lich chieu co gio chieu cu: " << gioChieuCu << endl << endl;
}


    // Hàm tìm kiếm lịch chiếu
    void TimLichChieu(const string& dauVao) {
        bool timThay = false;
        for (const auto& lich : DanhSachLichChieu) {
            if (lich.GioChieu == dauVao || lich.TenPhim == dauVao || lich.GiaVe == dauVao) {
                HienLichChieu(lich);
                timThay = true;
            }
        }
        if (!timThay) {
            cout << "Khong tim thay lich chieu." << endl << endl;
        }
    }

    // Hàm hiển thị tất cả lịch chiếu
    void HienTatCaLichChieu() {
        if (DanhSachLichChieu.empty()) {
            cout << "Danh sach lich chieu rong!" << endl << endl;
            return;
        }
        for (const auto& lich : DanhSachLichChieu) {
            HienLichChieu(lich);
        }
    }

    // Hàm hiển thị thông tin một lịch chiếu
    void HienLichChieu(const LichChiTiet& lich) const {
        cout << "Gio chieu    : " << lich.GioChieu << endl;
        cout << "Ten phim    : " << lich.TenPhim << endl;
        cout << "Gia ve      : " << lich.GiaVe << endl;
        cout << endl;
    }
};

int main() {
    LichChieu lc;
    string luaChon, gioChieu, tenPhim, giaVe;
    do {
        cout << "Quan ly lich chieu\n";
        cout << "1. Tim lich chieu\n2. Them lich chieu\n3. Xoa lich chieu\n4. Sua lich chieu\n5. Xem lich chieu\n6. Thoat\n";
        cout << "Chon chuc nang: ";
        getline(cin, luaChon);

        if (luaChon == "1") {
            cout << "Tim lich chieu theo (Gio chieu/Ten phim/Gia ve): ";
            getline(cin, gioChieu);
            lc.TimLichChieu(gioChieu);
        }
        else if (luaChon == "2") {
            cout << "Them gio chieu (hh:mm-dd/mm/yyyy): ";
            getline(cin, gioChieu);
            cout << "Them ten phim: ";
            getline(cin, tenPhim);
            cout << "Them gia ve: ";
            getline(cin, giaVe);
            lc.ThemLichChieu(gioChieu, tenPhim, giaVe);
        }
        else if (luaChon == "3") {
            cout << "Nhap gio chieu cua lich chieu muon xoa: ";
            getline(cin, gioChieu);
            lc.XoaLichChieu(gioChieu);
        }
        else if (luaChon == "4") {
            string gioChieuMoi, tenPhimMoi, giaVeMoi;
            cout << "Nhap gio chieu cu: ";
            getline(cin, gioChieu);
            cout << "Nhap gio chieu moi: ";
            getline(cin, gioChieuMoi);
            cout << "Nhap ten phim moi: ";
            getline(cin, tenPhimMoi);
            cout << "Nhap gia ve moi: ";
            getline(cin, giaVeMoi);
            lc.SuaLichChieu(gioChieu, gioChieuMoi, tenPhimMoi, giaVeMoi);
        }
        else if (luaChon == "5") {
            lc.HienTatCaLichChieu();
        }
        else if (luaChon != "6") {
            cout << "Lua chon khong hop le, vui long thu lai.\n\n";
        }

    } while (luaChon != "6");

    cout << "Thoat chuong trinh...";
    return 0;
}
