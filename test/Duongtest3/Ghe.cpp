#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

class Ghe {
private:
    struct GheChiTiet {
        string SoGhe;           // Số ghế (kiểu string)
        string KhuVuc;          // Khu vực (kiểu string)
        string HangGhe;         // Hàng ghế (kiểu string)
    };

    vector<GheChiTiet> DanhSachGhe;  // Vector chứa các ghế

public:
    Ghe() {
        DocGhe();  // Đọc thông tin ghế từ file
    }

    // Hàm kiểm tra tính hợp lệ của số ghế 
    bool KiemTraSoGhe(const string& soGhe) const {
    // Kiểm tra nếu chuỗi trống hoặc có ký tự không phải số
    if (soGhe.empty() || !isdigit(soGhe[0])) {
        return false;
    }

    // Kiểm tra nếu chuỗi không có ký tự nào khác ngoài số
    for (char c : soGhe) {
        if (!isdigit(c)) {
            return false;
        }
    }

    // Kiểm tra nếu số ghế có số 0 ở đầu
    if (soGhe[0] == '0' && soGhe.size() > 1) {
        return false; // Nếu số ghế có số 0 ở đầu (nhưng không phải số 0 duy nhất), thì không hợp lệ
    }

    // Kiểm tra nếu số ghế là 0 hoặc nhỏ hơn 1
    int so = stoi(soGhe);  // Chuyển chuỗi thành số nguyên
    if (so <= 0) {
        return false;  // Chỉ chấp nhận số nguyên dương từ 1 trở lên
    }

    return true;
}


    bool KiemTraKhuVuc(const string& khuVuc) const {
    // Khu vực phải có đúng 1 ký tự và phải là chữ cái in hoa (A-Z)
    return khuVuc.size() == 1 && isupper(khuVuc[0]);
}


    bool KiemTraHangGhe(const string& hangGhe) const {
    // Hàng ghế phải có đúng 1 ký tự và phải là chữ cái in thường (a-z)
    return hangGhe.size() == 1 && islower(hangGhe[0]);
}


    void DocGhe() {
        ifstream file("Ghe.txt");
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;  // Bỏ qua dòng trống

            GheChiTiet ghe;

            // Đọc "So ghe: ..."
            if (line.find("So ghe:") != string::npos) {
                ghe.SoGhe = line.substr(line.find(":") + 2);  // Lấy thông tin sau dấu ": "
            }

            // Đọc "Khu vuc: ..."
            getline(file, line);
            if (line.find("Khu vuc:") != string::npos) {
                ghe.KhuVuc = line.substr(line.find(":") + 2);  // Lấy thông tin sau dấu ": "
            }

            // Đọc "Hang ghe: ..."
            getline(file, line);
            if (line.find("Hang ghe:") != string::npos) {
                ghe.HangGhe = line.substr(line.find(":") + 2);  // Lấy thông tin sau dấu ": "
            }

            DanhSachGhe.push_back(ghe);  // Thêm ghế vào danh sách

            // Đọc dòng trống giữa các ghế (nếu có)
            getline(file, line);
        }
    }

    void LuuGhe() {
        ofstream file("Ghe.txt");
        for (const auto& ghe : DanhSachGhe) {
            file << "So ghe: " << ghe.SoGhe << endl;
            file << "Khu vuc: " << ghe.KhuVuc << endl;
            file << "Hang ghe: " << ghe.HangGhe << endl;
            file << endl;  // Thêm một dòng trống giữa các ghế
        }
    }

    // Hàm thêm ghế mới
    void ThemGhe(const string& soGhe, const string& khuVuc, const string& hangGhe) {
        if (!KiemTraSoGhe(soGhe) || !KiemTraKhuVuc(khuVuc) || !KiemTraHangGhe(hangGhe)) {
            cout << "Thong tin khong hop le. Vui long kiem tra lai." << endl << endl;
            return;
        }

        // Kiểm tra nếu ghế đã tồn tại trong danh sách
        for (auto& ghe : DanhSachGhe) {
            if (ghe.SoGhe == soGhe) {
                cout << "Ghe da ton tai." << endl << endl;
                return;
            }
        }

        // Nếu ghế chưa tồn tại, thêm ghế mới vào danh sách
        GheChiTiet gheMoi = {soGhe, khuVuc, hangGhe};
        DanhSachGhe.push_back(gheMoi);
        LuuGhe(); // Lưu lại thông tin vào file
        cout << "Da them ghe thanh cong!" << endl << endl;
    }

    // Hàm xóa ghế
    void XoaGhe(const string& soGhe) {
        for (size_t i = 0; i < DanhSachGhe.size(); ++i) {
            if (DanhSachGhe[i].SoGhe == soGhe) {
                DanhSachGhe.erase(DanhSachGhe.begin() + i);
                LuuGhe(); // Lưu lại thông tin vào file
                cout << "Da xoa ghe thanh cong!" << endl << endl;
                return;
            }
        }
        cout << "Khong tim thay ghe." << endl << endl;
    }

    void SuaGhe(const string& soGheCu, const string& soGheMoi, const string& khuVucMoi, const string& hangGheMoi) {
    // Kiểm tra tính hợp lệ của các đối tượng
    if (!KiemTraSoGhe(soGheMoi) || !KiemTraKhuVuc(khuVucMoi) || !KiemTraHangGhe(hangGheMoi)) {
        cout << "Thong tin khong hop le. Vui long kiem tra lai." << endl << endl;
        return;
    }

    // Kiểm tra xem số ghế mới có giống số ghế cũ không
    if (soGheCu == soGheMoi) {
        // Nếu số ghế cũ và số ghế mới giống nhau thì chỉ sửa khu vực và hàng ghế
        cout << "So ghe moi khong thay doi, chi sua khu vuc va hang ghe!" << endl << endl;
        // Tiến hành sửa khu vực và hàng ghế
        for (size_t i = 0; i < DanhSachGhe.size(); ++i) {
            if (DanhSachGhe[i].SoGhe == soGheCu) {
                // Sửa khu vực và hàng ghế
                DanhSachGhe[i].KhuVuc = khuVucMoi;
                DanhSachGhe[i].HangGhe = hangGheMoi;
                LuuGhe(); // Lưu lại thông tin vào file
                cout << "Da sua khu vuc va hang ghe thanh cong!" << endl << endl;
                return;
            }
        }
    } else {
        // Nếu số ghế mới khác số ghế cũ, kiểm tra xem số ghế mới đã tồn tại chưa
        for (const auto& ghe : DanhSachGhe) {
            if (ghe.SoGhe == soGheMoi) {
                cout << "So ghe moi da ton tai trong danh sach!" << endl << endl;
                return;
            }
        }

        // Nếu không trùng, tiến hành sửa số ghế, khu vực và hàng ghế
        for (size_t i = 0; i < DanhSachGhe.size(); ++i) {
            if (DanhSachGhe[i].SoGhe == soGheCu) {
                // Sửa số ghế, khu vực và hàng ghế
                DanhSachGhe[i].SoGhe = soGheMoi;
                DanhSachGhe[i].KhuVuc = khuVucMoi;
                DanhSachGhe[i].HangGhe = hangGheMoi;
                LuuGhe(); // Lưu lại thông tin vào file
                cout << "Da sua ghe thanh cong!" << endl << endl;
                return;
            }
        }
        cout << "Khong tim thay ghe cu." << endl << endl;
    }
}


    void TimGhe(const string& dauVao) {
    bool timThay = false;
    
    // Tìm kiếm theo số ghế
    for (const auto& ghe : DanhSachGhe) {
        if (ghe.SoGhe == dauVao || ghe.KhuVuc == dauVao || ghe.HangGhe == dauVao) {
            HienGhe(ghe);
            timThay = true;
        }
    }

    // Nếu không tìm thấy ghế nào
    if (!timThay) {
        cout << "Khong tim thay ghe." << endl << endl;
    }
}


    // Hàm hiển thị tất cả ghế
    void HienTatCaGhe() {
        if (DanhSachGhe.empty()) {
            cout << "Danh sach ghe rong!" << endl << endl;
            return;
        }
        for (const auto& ghe : DanhSachGhe) {
            HienGhe(ghe);
        }
    }

    // Hàm hiển thị thông tin một ghế
    void HienGhe(const GheChiTiet& ghe) const {
        cout << "So ghe   : " << ghe.SoGhe << endl;
        cout << "Khu vuc  : " << ghe.KhuVuc << endl;
        cout << "Hang ghe : " << ghe.HangGhe << endl;
        cout << endl;
    }
};

int main() {
    Ghe ghe;
    string luaChon, khuVuc, hangGhe, soGhe, soGheMoi;

    do {
        cout << "Quan ly ghe\n";
        cout << "1. Tim ghe\n2. Them ghe\n3. Xoa ghe\n4. Sua ghe\n5. Xem ghe\n6. Thoat\n";
        cout << "Chon chuc nang: ";
        getline(cin, luaChon);

        if (luaChon == "1") {
            cout << "Tim ghe theo (so ghe/khu vuc/hng ghe): ";
            getline(cin, soGhe);
            ghe.TimGhe(soGhe);
        }
        else if (luaChon == "2") {
            cout << "Them so ghe (>0): ";
            getline(cin, soGhe);
            cout << "Them khu vuc (chu cai in hoa): ";
            getline(cin, khuVuc);
            cout << "Them hang ghe (chu cai in thuong): ";
            getline(cin, hangGhe);
            ghe.ThemGhe(soGhe, khuVuc, hangGhe);
        }
        else if (luaChon == "3") {
            cout << "Nhap so ghe muon xoa: ";
            getline(cin, soGhe);
            ghe.XoaGhe(soGhe);
        }
        else if (luaChon == "4") {
            string soGheCu, soGheMoi, khuVucMoi, hangGheMoi;
            cout << "Nhap so ghe cu (>0): ";
            getline(cin, soGheCu);
            cout << "Nhap so ghe moi (>0): ";
            getline(cin, soGheMoi);
            cout << "Nhap khu vuc moi (chu cai in hoa): ";
            getline(cin, khuVucMoi);
            cout << "Nhap hang ghe moi (chu cai in thuong): ";
            getline(cin, hangGheMoi);
            ghe.SuaGhe(soGheCu, soGheMoi, khuVucMoi, hangGheMoi);
        }
        else if (luaChon == "5") {
            ghe.HienTatCaGhe();
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
