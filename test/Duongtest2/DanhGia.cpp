#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

class DanhGia {
private:
    struct DanhGiaChiTiet {
        string SoDT;    // Số điện thoại khách hàng (kiểu string)
        string SoSao;   // Số sao đánh giá (kiểu string)
        string PhanHoi; // Phản hồi của khách hàng (kiểu string)
    };

    vector<DanhGiaChiTiet> DanhSachDanhGia;  // Vector chứa danh sách đánh giá

    // Kiểm tra nếu số sao hợp lệ (1 đến 5)
    bool KiemTraSoSao(const string& soSao) const {
        if (soSao.size() != 1 || soSao < "1" || soSao > "5") {
            return false;
        }
        return true;
    }

    // Kiểm tra xem số điện thoại có tồn tại trong file KhachHang.txt không
    bool KiemTraKhachHang(const string& soDT) const {
        ifstream file("KhachHang.txt");
        string line;
        while (getline(file, line)) {
            if (line.find("So DT:") != string::npos) {
                string sdt = line.substr(line.find(":") + 2);
                if (sdt == soDT) {
                    return true;
                }
            }
        }
        return false;
    }

    // Đọc thông tin đánh giá từ file
    void DocDanhGia() {
        ifstream file("DanhGia.txt");
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;  // Bỏ qua dòng trống

            DanhGiaChiTiet danhGia;

            // Đọc "So DT: ..."
            if (line.find("So DT:") != string::npos) {
                danhGia.SoDT = line.substr(line.find(":") + 2);  // Lấy thông tin sau dấu ": "
            }

            // Đọc "So sao: ..."
            getline(file, line);
            if (line.find("So sao:") != string::npos) {
                danhGia.SoSao = line.substr(line.find(":") + 2);  // Lấy thông tin sau dấu ": "
            }

            // Đọc "Phan hoi: ..."
            getline(file, line);
            if (line.find("Phan hoi:") != string::npos) {
                danhGia.PhanHoi = line.substr(line.find(":") + 2);  // Lấy thông tin sau dấu ": "
            }

            DanhSachDanhGia.push_back(danhGia);  // Thêm đánh giá vào danh sách

            // Đọc dòng trống giữa các đánh giá (nếu có)
            getline(file, line);
        }
    }

    // Lưu danh sách đánh giá vào file
    void LuuDanhGia() {
        ofstream file("DanhGia.txt");
        for (const auto& danhGia : DanhSachDanhGia) {
            file << "So DT: " << danhGia.SoDT << endl;
            file << "So sao: " << danhGia.SoSao << endl;
            file << "Phan hoi: " << danhGia.PhanHoi << endl;
            file << endl;  // Thêm một dòng trống giữa các đánh giá
        }
    }

public:
    DanhGia() {
        DocDanhGia();  // Đọc thông tin đánh giá từ file
    }

    // Hàm thêm đánh giá
    void ThemDanhGia(const string& soDT, const string& soSao, const string& phanHoi) {
        if (!KiemTraSoSao(soSao)) {
            cout << "So sao khong hop le. Vui long chon so sao tu 1 den 5." << endl << endl;
            return;
        }

        // Kiểm tra nếu khách hàng đã tồn tại trong danh sách
        if (!KiemTraKhachHang(soDT)) {
            cout << "Khach hang voi so dien thoai nay khong ton tai!" << endl << endl;
            return;
        }

        // Kiểm tra nếu đánh giá đã tồn tại cho khách hàng này
        for (const auto& danhGia : DanhSachDanhGia) {
            if (danhGia.SoDT == soDT) {
                cout << "Danh gia cua khach hang nay da ton tai!" << endl << endl;
                return;
            }
        }

        // Nếu chưa tồn tại, thêm đánh giá mới vào danh sách
        DanhGiaChiTiet danhGiaMoi = {soDT, soSao, phanHoi};
        DanhSachDanhGia.push_back(danhGiaMoi);
        LuuDanhGia();  // Lưu lại thông tin vào file
        cout << "Da them danh gia thanh cong!" << endl << endl;
    }

    // Hàm xóa đánh giá
    void XoaDanhGia(const string& soDT) {
        for (size_t i = 0; i < DanhSachDanhGia.size(); ++i) {
            if (DanhSachDanhGia[i].SoDT == soDT) {
                DanhSachDanhGia.erase(DanhSachDanhGia.begin() + i);
                LuuDanhGia();  // Lưu lại thông tin vào file
                cout << "Da xoa danh gia thanh cong!" << endl << endl;
                return;
            }
        }
        cout << "Khong tim thay danh gia cua khach hang." << endl << endl;
    }

    // Hàm sửa đánh giá
    void SuaDanhGia(const string& soDTCu, const string& soDTMoi, const string& soSaoMoi, const string& phanHoiMoi) {
    // Kiểm tra số sao có hợp lệ không (phải từ 1 đến 5)
    if (!KiemTraSoSao(soSaoMoi)) {
        cout << "So sao khong hop le. Vui long chon so sao tu 1 den 5." << endl << endl;
        return;
    }

    // Kiểm tra số điện thoại cũ có tồn tại trong file DanhGia.txt không
    bool timThay = false;
    for (const auto& danhGia : DanhSachDanhGia) {
        if (danhGia.SoDT == soDTCu) {
            timThay = true; // Đánh dấu đã tìm thấy đánh giá của khách hàng
            break;
        }
    }

    if (!timThay) {
        cout << "Khong tim thay danh gia cua khach hang voi so DT cu!" << endl << endl;
        return;
    }

    // Kiểm tra số điện thoại mới có hợp lệ không (phải tồn tại trong KhachHang.txt)
    if (!KiemTraKhachHang(soDTMoi)) {
        cout << "Khach hang voi so dien thoai moi khong ton tai!" << endl << endl;
        return;
    }

    // Kiểm tra nếu số điện thoại mới trùng với số điện thoại cũ thì không cần sửa
    if (soDTCu == soDTMoi) {
        // Tìm và sửa đánh giá
        for (auto& danhGia : DanhSachDanhGia) {
            if (danhGia.SoDT == soDTCu) {
                danhGia.SoSao = soSaoMoi;  // Sửa số sao
                danhGia.PhanHoi = phanHoiMoi;  // Sửa phản hồi

                LuuDanhGia();  // Lưu lại thông tin vào file
                cout << "Da sua danh gia thanh cong!" << endl << endl;
                return;
            }
        }
    } else {
        // Nếu số điện thoại mới khác số điện thoại cũ, kiểm tra xem số điện thoại mới có tồn tại trong danh sách đánh giá không
        for (const auto& danhGia : DanhSachDanhGia) {
            if (danhGia.SoDT == soDTMoi) {
                cout << "So dien thoai moi da ton tai trong danh sach danh gia!" << endl << endl;
                return;  // Không cho phép sửa vì số điện thoại mới đã tồn tại trong danh sách
            }
        }

        // Nếu không trùng số điện thoại, tiến hành sửa
        for (auto& danhGia : DanhSachDanhGia) {
            if (danhGia.SoDT == soDTCu) {
                danhGia.SoDT = soDTMoi;  // Sửa số điện thoại
                danhGia.SoSao = soSaoMoi;  // Sửa số sao
                danhGia.PhanHoi = phanHoiMoi;  // Sửa phản hồi

                LuuDanhGia();  // Lưu lại thông tin vào file
                cout << "Da sua danh gia thanh cong!" << endl << endl;
                return;
            }
        }
    }

    cout << "Khong tim thay danh gia cua khach hang voi so DT cu!" << endl << endl;
}



    // Hàm tìm kiếm đánh giá
    void TimDanhGia(const string& dauVao) {
        bool timThay = false;

        for (const auto& danhGia : DanhSachDanhGia) {
            if (danhGia.SoDT == dauVao || danhGia.SoSao == dauVao || danhGia.PhanHoi == dauVao) {
                HienDanhGia(danhGia);  // Hiển thị thông tin đánh giá
                timThay = true;
            }
        }

        if (!timThay) {
            cout << "Khong tim thay danh gia." << endl << endl;
        }
    }

    // Hàm hiển thị tất cả đánh giá
    // Hàm hiển thị tất cả đánh giá và tính số sao trung bình
void HienTatCaDanhGia() {
    if (DanhSachDanhGia.empty()) {
        cout << "Danh sach danh gia rong!" << endl << endl;
        return;
    }

    int tongSoSao = 0;  // Tổng số sao của tất cả đánh giá
    int soLuongDanhGia = 0;  // Số lượng đánh giá hợp lệ

    // Hiển thị tất cả các đánh giá
    for (const auto& danhGia : DanhSachDanhGia) {
        HienDanhGia(danhGia);  // Hiển thị thông tin của đánh giá hiện tại

        // Cộng dồn số sao vào tổng (chỉ tính các đánh giá hợp lệ)
        if (!danhGia.SoSao.empty()) {
            try {
                tongSoSao += stoi(danhGia.SoSao);  // Chuyển số sao từ string sang int và cộng vào tổng
                soLuongDanhGia++;
            } catch (const exception& e) {
                // Nếu không thể chuyển số sao sang int (ví dụ có lỗi dữ liệu), bỏ qua
                cout << "Loi khi chuye so sao: " << e.what() << endl;
            }
        }
    }

    // Tính số sao trung bình nếu có ít nhất một đánh giá
    if (soLuongDanhGia > 0) {
        double soSaoTrungBinh = static_cast<double>(tongSoSao) / soLuongDanhGia;
        cout << "So sao trung binh: " << soSaoTrungBinh << endl << endl;
    }
}


    // Hàm hiển thị thông tin một đánh giá
    void HienDanhGia(const DanhGiaChiTiet& danhGia) const {
        cout << "So DT     : " << danhGia.SoDT << endl;
        cout << "So sao    : " << danhGia.SoSao << endl;
        cout << "Phan hoi  : " << danhGia.PhanHoi << endl;
        cout << endl;
    }
};

int main() {
    DanhGia danhGia;
    string luaChon, soDT, soSao, phanHoi, soDTMoi;

    do {
        cout << "Quan ly danh gia\n";
        cout << "1. Tim danh gia\n2. Them danh gia\n3. Xoa danh gia\n4. Sua danh gia\n5. Xem danh gia\n6. Thoat\n";
        cout << "Chon chuc nang: ";
        getline(cin, luaChon);

        if (luaChon == "1") {
            cout << "Tim danh gia theo (so DT/so sao/phan hoi): ";
            getline(cin, soDT);
            danhGia.TimDanhGia(soDT);
        }
        else if (luaChon == "2") {
            cout << "Them so DT: ";
            getline(cin, soDT);
            cout << "Them so sao (1-5): ";
            getline(cin, soSao);
            cout << "Them phan hoi: ";
            getline(cin, phanHoi);
            danhGia.ThemDanhGia(soDT, soSao, phanHoi);
        }
        else if (luaChon == "3") {
            cout << "Nhap so DT danh gia can xoa: ";
            getline(cin, soDT);
            danhGia.XoaDanhGia(soDT);
        }
        else if (luaChon == "4") {
            cout << "Nhap so DT danh gia can sua: ";
            getline(cin, soDT);
            cout << "Nhap so DT moi: ";
            getline(cin, soDTMoi);
            cout << "Nhap so sao moi (1-5): ";
            getline(cin, soSao);
            cout << "Nhap phan hoi moi: ";
            getline(cin, phanHoi);
            danhGia.SuaDanhGia(soDT, soDTMoi, soSao, phanHoi);
        }
        else if (luaChon == "5") {
            danhGia.HienTatCaDanhGia();
        }
        else if (luaChon != "6") {
            cout << "Lua chon khong hop le!" << endl << endl;
        }

    } while (luaChon != "6");

    return 0;
}
