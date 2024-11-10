#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

class KhachHang {
private:
    struct KhachHangChiTiet {
        string SoDT;        // Số điện thoại (kiểu string)
        string Ten;         // Tên khách hàng (kiểu string)
        string GioiTinh;    // Giới tính (kiểu string)
    };

    vector<KhachHangChiTiet> DanhSachKhachHang;  // Vector chứa danh sách khách hàng

public:
    KhachHang() {
        DocKhachHang();  // Đọc thông tin khách hàng từ file
    }

    // Hàm kiểm tra tính hợp lệ của số điện thoại (SDT phải có định dạng 0XXXXXXXXX)
    bool KiemTraSoDT(const string& soDT) const {
        if (soDT.size() != 10 || soDT[0] != '0' || !isdigit(soDT[1])) {
            return false;
        }
        for (size_t i = 1; i < soDT.size(); ++i) {
            if (!isdigit(soDT[i])) {
                return false;
            }
        }
        return true;
    }

    // Kiểm tra giới tính hợp lệ (Nam, Nu, Khac)
    bool KiemTraGioiTinh(const string& gioiTinh) const {
        return gioiTinh == "Nam" || gioiTinh == "Nu" || gioiTinh == "Khac";
    }

    // Đọc thông tin khách hàng từ file
    void DocKhachHang() {
        ifstream file("KhachHang.txt");
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;  // Bỏ qua dòng trống

            KhachHangChiTiet khachHang;

            // Đọc "So DT: ... "
            if (line.find("So DT:") != string::npos) {
                khachHang.SoDT = line.substr(line.find(":") + 2);  // Lấy thông tin sau dấu ": "
            }

            // Đọc "Ten: ..."
            getline(file, line);
            if (line.find("Ten:") != string::npos) {
                khachHang.Ten = line.substr(line.find(":") + 2);  // Lấy thông tin sau dấu ": "
            }

            // Đọc "Gioi tinh: ..."
            getline(file, line);
            if (line.find("Gioi tinh:") != string::npos) {
                khachHang.GioiTinh = line.substr(line.find(":") + 2);  // Lấy thông tin sau dấu ": "
            }

            DanhSachKhachHang.push_back(khachHang);  // Thêm khách hàng vào danh sách

            // Đọc dòng trống giữa các khách hàng (nếu có)
            getline(file, line);
        }
    }

    // Lưu danh sách khách hàng vào file
    void LuuKhachHang() {
        ofstream file("KhachHang.txt");
        for (const auto& khachHang : DanhSachKhachHang) {
            file << "So DT: " << khachHang.SoDT << endl;
            file << "Ten: " << khachHang.Ten << endl;
            file << "Gioi tinh: " << khachHang.GioiTinh << endl;
            file << endl;  // Thêm một dòng trống giữa các khách hàng
        }
    }

    // Hàm thêm khách hàng mới
    void ThemKhachHang(const string& soDT, const string& ten, const string& gioiTinh) {
        if (!KiemTraSoDT(soDT) || !KiemTraGioiTinh(gioiTinh)) {
            cout << "Thong tin khong hop le. Vui long kiem tra lai." << endl << endl;
            return;
        }

        // Kiểm tra nếu khách hàng đã tồn tại trong danh sách
        for (auto& khachHang : DanhSachKhachHang) {
            if (khachHang.SoDT == soDT) {
                cout << "Khach hang da ton tai." << endl << endl;
                return;
            }
        }

        // Nếu khách hàng chưa tồn tại, thêm khách hàng mới vào danh sách
        KhachHangChiTiet khachHangMoi = {soDT, ten, gioiTinh};
        DanhSachKhachHang.push_back(khachHangMoi);
        LuuKhachHang();  // Lưu lại thông tin vào file
        cout << "Da them khach hang thanh cong!" << endl << endl;
    }

    // Hàm xóa khách hàng
    void XoaKhachHang(const string& soDT) {
        for (size_t i = 0; i < DanhSachKhachHang.size(); ++i) {
            if (DanhSachKhachHang[i].SoDT == soDT) {
                DanhSachKhachHang.erase(DanhSachKhachHang.begin() + i);
                LuuKhachHang();  // Lưu lại thông tin vào file
                cout << "Da xoa khach hang thanh cong!" << endl << endl;
                return;
            }
        }
        cout << "Khong tim thay khach hang." << endl << endl;
    }

    // Hàm sửa thông tin khách hàng
    void SuaKhachHang(const string& soDTCu, const string& soDTMoi, const string& tenMoi, const string& gioiTinhMoi) {
        if (!KiemTraSoDT(soDTMoi) || !KiemTraGioiTinh(gioiTinhMoi)) {
            cout << "Thong tin khong hop le. Vui long kiem tra lai." << endl << endl;
            return;
        }

        // Kiểm tra xem số điện thoại mới có giống số điện thoại cũ không
        if (soDTCu == soDTMoi) {
            cout << "So dien thoai moi khong thay doi, chi sua ten va gioi tinh!" << endl << endl;
            for (size_t i = 0; i < DanhSachKhachHang.size(); ++i) {
                if (DanhSachKhachHang[i].SoDT == soDTCu) {
                    DanhSachKhachHang[i].Ten = tenMoi;
                    DanhSachKhachHang[i].GioiTinh = gioiTinhMoi;
                    LuuKhachHang();  // Lưu lại thông tin vào file
                    cout << "Da sua ten va gioi tinh thanh cong!" << endl << endl;
                    return;
                }
            }
        } else {
            // Nếu số điện thoại mới khác số điện thoại cũ, kiểm tra xem số điện thoại mới đã tồn tại chưa
            for (const auto& khachHang : DanhSachKhachHang) {
                if (khachHang.SoDT == soDTMoi) {
                    cout << "So dien thoai moi da ton tai trong danh sach!" << endl << endl;
                    return;
                }
            }

            // Nếu không trùng, tiến hành sửa số điện thoại, tên và giới tính
            for (size_t i = 0; i < DanhSachKhachHang.size(); ++i) {
                if (DanhSachKhachHang[i].SoDT == soDTCu) {
                    DanhSachKhachHang[i].SoDT = soDTMoi;
                    DanhSachKhachHang[i].Ten = tenMoi;
                    DanhSachKhachHang[i].GioiTinh = gioiTinhMoi;
                    LuuKhachHang();  // Lưu lại thông tin vào file
                    cout << "Da sua khach hang thanh cong!" << endl << endl;
                    return;
                }
            }
            cout << "Khong tim thay khach hang cu." << endl << endl;
        }
    }

    // Hàm tìm kiếm khách hàng theo số điện thoại, tên hoặc giới tính
    void TimKhachHang(const string& dauVao) {
        bool timThay = false;

        for (const auto& khachHang : DanhSachKhachHang) {
            if (khachHang.SoDT == dauVao || khachHang.Ten == dauVao || khachHang.GioiTinh == dauVao) {
                HienKhachHang(khachHang);
                timThay = true;
            }
        }

        if (!timThay) {
            cout << "Khong tim thay khach hang." << endl << endl;
        }
    }

    // Hàm hiển thị tất cả khách hàng
    void HienTatCaKhachHang() {
        if (DanhSachKhachHang.empty()) {
            cout << "Danh sach khach hang rong!" << endl << endl;
            return;
        }
        for (const auto& khachHang : DanhSachKhachHang) {
            HienKhachHang(khachHang);
        }
    }

    // Hàm hiển thị thông tin một khách hàng
    void HienKhachHang(const KhachHangChiTiet& khachHang) const {
        cout << "So DT    : " << khachHang.SoDT << endl;
        cout << "Ten      : " << khachHang.Ten << endl;
        cout << "Gioi tinh: " << khachHang.GioiTinh << endl;
        cout << endl;
    }
};

int main() {
    KhachHang khachHang;
    string luaChon, soDT, ten, gioiTinh, soDTMoi, tenMoi, gioiTinhMoi;

    do {
        cout << "Quan ly khach hang\n";
        cout << "1. Tim khach hang\n2. Them khach hang\n3. Xoa khach hang\n4. Sua khach hang\n5. Xem khach hang\n6. Thoat\n";
        cout << "Chon chuc nang: ";
        getline(cin, luaChon);

        if (luaChon == "1") {
            cout << "Tim khach hang theo (so DT/ten/gioi tinh): ";
            getline(cin, soDT);
            khachHang.TimKhachHang(soDT);
        }
        else if (luaChon == "2") {
            cout << "Them so DT: ";
            getline(cin, soDT);
            cout << "Them ten: ";
            getline(cin, ten);
            cout << "Them gioi tinh (Nam, Nu, Khac): ";
            getline(cin, gioiTinh);
            khachHang.ThemKhachHang(soDT, ten, gioiTinh);
        }
        else if (luaChon == "3") {
            cout << "Nhap so DT muon xoa: ";
            getline(cin, soDT);
            khachHang.XoaKhachHang(soDT);
        }
        else if (luaChon == "4") {
            cout << "Nhap so DT cu: ";
            getline(cin, soDT);
            cout << "Nhap so DT moi: ";
            getline(cin, soDTMoi);
            cout << "Nhap ten moi: ";
            getline(cin, tenMoi);
            cout << "Nhap gioi tinh moi (Nam, Nu, Khac): ";
            getline(cin, gioiTinhMoi);
            khachHang.SuaKhachHang(soDT, soDTMoi, tenMoi, gioiTinhMoi);
        }
        else if (luaChon == "5") {
            khachHang.HienTatCaKhachHang();
        }
        else if (luaChon == "6") {
            cout << "Thoat chuong trinh...";
        }
        else {
            cout << "Lua chon khong hop le, vui long thu lai.\n\n";
        }

    } while (luaChon != "6");

    return 0;
}
