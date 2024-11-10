#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Ve {
private:
    struct VeChiTiet {
        string GioChieuSoGhe;  // Kết hợp giờ chiếu và số ghế, dạng "hh:mm-dd/mm/yyyy+S"
        string TenDichVu;      // Tên dịch vụ
        string SoDT;           // Số điện thoại khách hàng
    };

    vector<VeChiTiet> DanhSachVe;  // Danh sách các vé

public:
    Ve() {
        DocVe();  // Đọc các vé từ file Ve.txt
    }

    bool KiemTraGioChieu(const string& gioChieu) {
        ifstream file("LichChieu.txt");
        string line;
        bool timThay = false;

        while (getline(file, line)) {
            if (line.find("Gio chieu") != string::npos) {
                string gioChieuFile = line.substr(line.find(":") + 2);  // Lấy giờ chiếu
                if (gioChieuFile == gioChieu) {
                    timThay = true;
                    break;
                }
            }
        }

        file.close();
        return timThay;
    }

    // Kiểm tra số ghế có hợp lệ không (có trong file Ghe.txt)
    bool KiemTraSoGhe(const string& soGhe) {
        ifstream file("Ghe.txt");
        string line;
        bool timThay = false;

        while (getline(file, line)) {
            if (line.find("So ghe") != string::npos) {
                string soGheFile = line.substr(line.find(":") + 2);  // Lấy số ghế
                if (soGheFile == soGhe) {
                    timThay = true;
                    break;
                }
            }
        }

        file.close();
        return timThay;
    }
    // Kiểm tra giờ chiếu và số ghế có hợp lệ không
    bool KiemTraGioChieuSoGhe(const string& gioChieuSoGhe) {
        // Tách giờ chiếu và số ghế
        size_t pos = gioChieuSoGhe.find('+');
        if (pos == string::npos) return false;

        string gioChieu = gioChieuSoGhe.substr(0, pos);
        string soGhe = gioChieuSoGhe.substr(pos + 1);

        return KiemTraGioChieu(gioChieu) && KiemTraSoGhe(soGhe);
    }

    // Kiểm tra tên dịch vụ có hợp lệ không (kiểm tra trong file DichVu.txt)

    bool KiemTraTenDichVu(const string& dv) {
        ifstream file("DichVu.txt");
        string line;
        bool timThay = false;

        while (getline(file, line)) {
            if (line.find("Ten dich vu") != string::npos) {
                string tenDichVu = line.substr(line.find(":") + 2);
                if (tenDichVu == dv) {
                    timThay = true;
                    break;
                }
            }
        }

        file.close();
        return timThay;
    }
    // Kiểm tra số điện thoại khách hàng có hợp lệ không (kiểm tra trong file KhachHang.txt)

    bool KiemTraSoDT(const string& sdt) {
        ifstream file("KhachHang.txt");
        string line;
        bool timThay = false;

        while (getline(file, line)) {
            if (line.find("So DT") != string::npos) {
                string SDT = line.substr(line.find(":") + 2);  
                if (SDT == sdt) {
                    timThay = true;
                    break;
                }
            }
        }

        file.close();
        return timThay;
    }
    void TimGheConTrong(const string& gioChieuSoGhe) {
    vector<string> ghesDaDat;  // Danh sách các ghế đã đặt
    vector<string> tatCaGhe;   // Danh sách tất cả các ghế

    // Tách giờ chiếu và số ghế từ tham số gioChieuSoGhe
    size_t pos = gioChieuSoGhe.find('+');
    if (pos == string::npos) {
        cout << endl;
        return;
    }

    string gioChieu = gioChieuSoGhe.substr(0, pos);   // Lấy giờ chiếu
    string soGheCanTim = gioChieuSoGhe.substr(pos + 1); // Lấy số ghế cần tìm

    // Đọc các vé đã đặt từ Ve.txt và tìm ghế đã đặt cho giờ chiếu
    ifstream fileVe("Ve.txt");
    string line;
    while (getline(fileVe, line)) {
        // Tìm các vé có giờ chiếu tương ứng
        if (line.find("Gio chieu+So ghe:") != string::npos) {
            string gioChieuSoGheTrongVe = line.substr(line.find(":") + 2);  // Tách giờ chiếu + số ghế
            if (gioChieuSoGheTrongVe.find(gioChieu) != string::npos) {
                // Lưu lại các số ghế đã đặt
                size_t posVe = gioChieuSoGheTrongVe.find('+');
                string soGhe = gioChieuSoGheTrongVe.substr(posVe + 1);
                ghesDaDat.push_back(soGhe);  // Thêm số ghế vào danh sách
            }
        }
    }
    fileVe.close();

    // Đọc tất cả ghế từ Ghe.txt
    ifstream fileGhe("Ghe.txt");
    while (getline(fileGhe, line)) {
        if (line.find("So ghe:") != string::npos) {
            string soGhe = line.substr(line.find(":") + 2);  // Tách số ghế
            tatCaGhe.push_back(soGhe);
        }
    }
    fileGhe.close();

    // Liệt kê các ghế còn trống (ngoài số ghế đã đặt)
    bool timThayGheConTrong = false;
    cout << "Danh sach ghe trong: ";
    for (const string& ghe : tatCaGhe) {
        // Nếu ghế chưa được đặt (không có trong danh sách ghế đã đặt)
        if (find(ghesDaDat.begin(), ghesDaDat.end(), ghe) == ghesDaDat.end()) {
            cout << ghe << " ";
            timThayGheConTrong = true;
        }
    }
    // Nếu không tìm thấy ghế còn trống
    if (!timThayGheConTrong) {
        cout << "Da dat het.";
    }
    cout << endl;
}

    // Đọc file Ve.txt
    void DocVe() {
        ifstream file("Ve.txt");
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;  // Bỏ qua dòng trống

            VeChiTiet ve;
            // Đọc "Gio chieu+So ghe: ..."
            if (line.find("Gio chieu+So ghe:") != string::npos) {
                ve.GioChieuSoGhe = line.substr(line.find(":") + 2);  // Lấy thông tin sau dấu ": "
            }

            // Đọc "Ten dich vu: ..."
            getline(file, line);
            if (line.find("Ten dich vu:") != string::npos) {
                ve.TenDichVu = line.substr(line.find(":") + 2);  // Lấy thông tin sau dấu ": "
            }

            // Đọc "So DT: ..."
            getline(file, line);
            if (line.find("So DT:") != string::npos) {
                ve.SoDT = line.substr(line.find(":") + 2);  // Lấy thông tin sau dấu ": "
            }

            DanhSachVe.push_back(ve);  // Thêm vé vào danh sách
        }
    }

    // Lưu thông tin vào file Ve.txt
    void LuuVe() {
        ofstream file("Ve.txt");
        for (const auto& ve : DanhSachVe) {
            file << "Gio chieu+So ghe: " << ve.GioChieuSoGhe << endl;
            file << "Ten dich vu: " << ve.TenDichVu << endl;
            file << "So DT: " << ve.SoDT << endl;
            file << endl;  // Thêm dòng trống giữa các vé
        }
    }

    // Hàm thêm vé mới
void ThemVe(const string& gioChieuSoGhe, const string& tenDichVu, const string& soDT) {
    if (!KiemTraGioChieuSoGhe(gioChieuSoGhe)) {
        cout << "Gio chieu hoac so ghe khong hop le!" << endl << endl;
        return;
    }

    if (!KiemTraSoDT(soDT)) {
        cout << "So dien thoai khach hang khong hop le!" << endl << endl;
        return;
    }

    if (!KiemTraTenDichVu(tenDichVu)) {
            cout << "Ten dich vu khong hop le!" << endl << endl;
            return;
        }

    // Kiểm tra vé đã tồn tại trong hệ thống chưa
    for (const auto& ve : DanhSachVe) {
        if (ve.GioChieuSoGhe == gioChieuSoGhe) {
            cout << "Ve da ton tai!" << endl << endl;
            return;
        }
    }

    VeChiTiet veMoi = {gioChieuSoGhe, tenDichVu, soDT};
    DanhSachVe.push_back(veMoi);  // Thêm vé mới vào danh sách
    LuuVe();  // Lưu lại thông tin vào file
    cout << "Da them ve thanh cong!" << endl << endl;
}


    // Hàm sửa vé
    // Hàm sửa vé
void SuaVe(const string& gioChieuSoGheCu, const string& gioChieuSoGheMoi, const string& tenDichVuMoi, const string& soDTMoi) {
    if (!KiemTraGioChieuSoGhe(gioChieuSoGheMoi)) {
        cout << "Gio chieu hoac so ghe moi khong hop le!" << endl << endl;
        return;
    }

    if (!KiemTraSoDT(soDTMoi)) {
        cout << "So dien thoai khach hang moi khong hop le!" << endl << endl;
        return;
    }
    
    if (!KiemTraTenDichVu(tenDichVuMoi)) {
            cout << "Ten dich vu moi khong hop le!" << endl << endl;
            return;
    }

    // Kiểm tra xem vé với giờ chiếu + số ghế mới có tồn tại trong danh sách không
    bool veTonTai = false;
    for (const auto& ve : DanhSachVe) {
        if (ve.GioChieuSoGhe == gioChieuSoGheMoi) {
            veTonTai = true;
            break;
        }
    }

    // Nếu vé cũ và vé mới giống nhau, cho phép sửa mà không báo lỗi
    if (gioChieuSoGheCu == gioChieuSoGheMoi) {
        veTonTai = false;  // Để không kiểm tra lại nếu người dùng không thay đổi giờ chiếu và số ghế
    }

    if (veTonTai) {
        cout << "Ve da ton tai voi gio chieu+so ghe moi!" << endl << endl;
        return;
    }



    for (auto& ve : DanhSachVe) {
        if (ve.GioChieuSoGhe == gioChieuSoGheCu) {
            ve.GioChieuSoGhe = gioChieuSoGheMoi;
            ve.TenDichVu = tenDichVuMoi;  // Cập nhật tên dịch vụ
            ve.SoDT = soDTMoi;
            LuuVe();  // Lưu lại thông tin vào file
            cout << "Da sua ve thanh cong!" << endl << endl;
            return;
        }
    }
    cout << "Khong tim thay ve can sua!" << endl << endl;
}


    // Hàm xóa vé
    void XoaVe(const string& gioChieuSoGhe) {
        for (size_t i = 0; i < DanhSachVe.size(); ++i) {
            if (DanhSachVe[i].GioChieuSoGhe == gioChieuSoGhe) {
                DanhSachVe.erase(DanhSachVe.begin() + i);
                LuuVe();  // Lưu lại thông tin vào file
                cout << "Da xoa ve thanh cong!" << endl << endl;
                return;
            }
        }
        cout << "Khong tim thay ve!" << endl << endl;
    }

    // Hàm tìm vé
    void TimVe(const string& dauVao) {
    bool timThay = false;

    // Duyệt qua tất cả vé trong danh sách
    for (const auto& ve : DanhSachVe) {
    	if(ve.GioChieuSoGhe == dauVao) {
    		TimGheConTrong(dauVao);
		}
        // Tìm vé dựa trên giờ chiếu + số ghế, tên dịch vụ hoặc số điện thoại khách hàng
        if (ve.GioChieuSoGhe == dauVao || ve.TenDichVu == dauVao || ve.SoDT == dauVao) {
            HienVe(ve);  // Hiển thị thông tin vé tìm thấy
            timThay = true;
        }
    }

    if (!timThay) {
        cout << "Khong tim thay ve." << endl << endl;
    }
}


    // Hàm hiển thị tất cả vé
    void HienTatCaVe() {
        if (DanhSachVe.empty()) {
            cout << "Danh sach ve rong!" << endl << endl;
            return;
        }
        for (const auto& ve : DanhSachVe) {
            cout << "Gio chieu+So ghe: " << ve.GioChieuSoGhe << endl;
            cout << "Ten dich vu: " << ve.TenDichVu << endl;
            cout << "So DT: " << ve.SoDT << endl;
            cout << endl;
        }
    }
    void HienVe(const Ve::VeChiTiet& ve) {
    cout << "Gio chieu+So ghe: " << ve.GioChieuSoGhe << endl;
    // Hiển thị tên dịch vụ, nếu trống thì hiển thị "Chua chon dich vu"
    cout << "Ten dich vu: " << (ve.TenDichVu.empty() ? "Chua chon dich vu" : ve.TenDichVu) << endl;
    cout << "So DT: " << ve.SoDT << endl;
    cout << endl;
}



};

int main() {
    Ve ve;
    string luaChon, gioChieuSoGhe, tenDichVu, soDT, gioChieuSoGheMoi;

    do {
        cout << "Quan ly ve\n";
        cout << "1. Tim ve\n2. Them ve\n3. Xoa ve\n4. Sua ve\n5. Xem ve\n6. Thoat\n";
        cout << "Chon chuc nang: ";
        getline(cin, luaChon);

        if (luaChon == "1") {
            cout << "Nhap (gio chieu+so ve/ten dich vu/so DT) de tim: ";
            getline(cin, gioChieuSoGhe);
            ve.TimVe(gioChieuSoGhe);
        }
        else if (luaChon == "2") {
            cout << "Nhap gio chieu+so ghe (hh:mm-dd/mm/yyyy+S): ";
            getline(cin, gioChieuSoGhe);
            cout << "Nhap ten dich vu: ";
            getline(cin, tenDichVu);
            cout << "Nhap so DT: ";
            getline(cin, soDT);
            ve.ThemVe(gioChieuSoGhe, tenDichVu, soDT);
        }
        else if (luaChon == "3") {
            cout << "Nhap gio chieu+so ghe muon xoa (hh:mm-dd/mm/yyyy+S): ";
            getline(cin, gioChieuSoGhe);
            ve.XoaVe(gioChieuSoGhe);
        }
        else if (luaChon == "4") {
            cout << "Nhap gio chieu+so ghe cu: ";
            getline(cin, gioChieuSoGhe);
            cout << "Nhap gio chieu+so ghe moi: ";
            getline(cin, gioChieuSoGheMoi);
            cout << "Nhap ten dich vu moi: ";
            getline(cin, tenDichVu);
            cout << "Nhap so DT moi: ";
            getline(cin, soDT);
            ve.SuaVe(gioChieuSoGhe, gioChieuSoGheMoi, tenDichVu, soDT);
        }
        else if (luaChon == "5") {
            ve.HienTatCaVe();
        }
        else if (luaChon == "6") {
            cout << "Thoat chuong trinh...\n";
        }
        else {
            cout << "Lua chon khong hop le, vui long thu lai.\n\n";
        }

    } while (luaChon != "6");

    return 0;
}

