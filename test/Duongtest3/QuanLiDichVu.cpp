#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class DichVu {  // Định nghĩa lớp DichVu
private:
    struct NhapDichVu {  // Cấu trúc để lưu thông tin dịch vụ
        string TenDichVu;    // Tên dịch vụ
        string NhaCungCap;   // Nhà cung cấp dịch vụ
        string GiaDichVu;    // Giá dịch vụ
    };

    vector<NhapDichVu> ThongTinDichVu;  // Vector chứa danh sách các dịch vụ

public:
    DichVu() {   // Hàm khởi tạo của lớp
        DuyetDichVu();  // Gọi hàm DuyetDichVu để đọc thông tin dịch vụ từ file
    }

    void DuyetDichVu() {  // Hàm để duyệt và đọc thông tin dịch vụ từ file
        ifstream Tep("DichVu.txt");  // Mở file DichVu.txt để đọc
        string Dong;  // Biến lưu từng dòng đọc từ file
        while (getline(Tep, Dong)) {  // Đọc từng dòng trong file
            if (Dong.empty()) continue;  // Nếu dòng trống thì bỏ qua
            NhapDichVu GhiThongTin;  // Khai báo một biến để lưu thông tin dịch vụ
            GhiThongTin.TenDichVu = Dong.substr(Dong.find(":") + 2);  // Lấy tên dịch vụ từ dòng
            getline(Tep, Dong);  // Đọc dòng tiếp theo
            GhiThongTin.NhaCungCap = Dong.substr(Dong.find(":") + 2);  // Lấy nhà cung cấp
            getline(Tep, Dong);  // Đọc dòng tiếp theo
            GhiThongTin.GiaDichVu = Dong.substr(Dong.find(":") + 2);  // Lấy giá dịch vụ
            ThongTinDichVu.push_back(GhiThongTin);  // Thêm thông tin dịch vụ vào vector
        }
    }

    void LuuDichVu() {  // Hàm để lưu thông tin dịch vụ vào file
        ofstream Tep("DichVu.txt");  // Mở file DichVu.txt để ghi
        for (int i = 0; i < ThongTinDichVu.size(); i++) {  // Lặp qua từng dịch vụ
            Tep << "Ten dich vu  : " << ThongTinDichVu[i].TenDichVu << endl;  // Ghi tên dịch vụ
            Tep << "Nha cung cap : " << ThongTinDichVu[i].NhaCungCap << endl;  // Ghi nhà cung cấp
            Tep << "Gia dich vu  : " << ThongTinDichVu[i].GiaDichVu << endl;  // Ghi giá dịch vụ
            Tep << endl;  // Ghi dòng trắng để dễ đọc
        }
    }

    void TimDichVu(const string& DauVao) {  // Hàm tìm dịch vụ theo tên, nhà cung cấp hoặc giá
        bool TimThay = false;  // Biến đánh dấu có tìm thấy dịch vụ hay không
        for (int i = 0; i < ThongTinDichVu.size(); i++) {  // Lặp qua danh sách dịch vụ
            if (ThongTinDichVu[i].TenDichVu == DauVao ||  // Kiểm tra tên dịch vụ
                ThongTinDichVu[i].NhaCungCap == DauVao ||  // Kiểm tra nhà cung cấp
                ThongTinDichVu[i].GiaDichVu == DauVao) {  // Kiểm tra giá dịch vụ
                Hien(ThongTinDichVu[i]);  // Hiện thông tin dịch vụ
                TimThay = true;  // Đánh dấu đã tìm thấy
            }
        }
        if (!TimThay) {  // Nếu không tìm thấy
            cout << "Khong tim thay dich vu." << endl << endl;  // Thông báo không tìm thấy
        }
    }

    bool KiemTraGia(const string& Gia) const {  // Hàm kiểm tra định dạng giá dịch vụ
        if (Gia.empty()) return false;  // Không để giá rỗng
        if (Gia[0] == '0' && Gia.length() > 1) return false;  // Không bắt đầu bằng 0, trừ khi giá là "0"
        
        // Kiểm tra nếu giá là một số nguyên không âm
        for (int i = 0; i < Gia.size(); i++) {
            if (!isdigit(Gia[i])) return false;  // Kiểm tra xem có phải số không
        }

        // Chuyển giá sang số nguyên để kiểm tra >= 0
        int giaInt = stoi(Gia);
        if (giaInt < 0) return false;  // Giá phải >= 0

        return true;  // Trả về true nếu định dạng hợp lệ
    }

    void ThemDichVu(const string& TenDichVu, const string& NhaCungCap, const string& GiaDichVu) {  // Hàm thêm dịch vụ
        if (!KiemTraGia(GiaDichVu)) {  // Kiểm tra định dạng giá dịch vụ
            cout << "Sai dinh dang gia dich vu." << endl << endl;  // Thông báo sai định dạng
            return;  // Kết thúc hàm
        }

        NhapDichVu DichVuMoi;  // Khai báo một dịch vụ mới
        DichVuMoi.TenDichVu = TenDichVu;  // Gán tên dịch vụ cho dịch vụ mới
        DichVuMoi.NhaCungCap = NhaCungCap;  // Gán nhà cung cấp cho dịch vụ mới
        DichVuMoi.GiaDichVu = GiaDichVu;  // Gán giá dịch vụ cho dịch vụ mới

        for (int i = 0; i < ThongTinDichVu.size(); i++) {  // Lặp qua danh sách dịch vụ
            if (ThongTinDichVu[i].TenDichVu == TenDichVu) {  // Kiểm tra nếu tên dịch vụ đã tồn tại
                cout << "Dich vu da ton tai." << endl << endl;  // Thông báo đã tồn tại
                return;  // Kết thúc hàm
            }
        }

        ThongTinDichVu.push_back(DichVuMoi);  // Thêm dịch vụ mới vào danh sách
        LuuDichVu();  // Lưu danh sách dịch vụ vào file
        cout << "Da them thanh cong dich vu." << endl << endl;  // Thông báo thêm thành công
    }

    void XoaDichVu(const string& TenDichVu) {  // Hàm xóa dịch vụ theo tên
        for (int i = 0; i < ThongTinDichVu.size(); i++) {  // Lặp qua danh sách dịch vụ
            if (ThongTinDichVu[i].TenDichVu == TenDichVu) {  // Kiểm tra nếu tìm thấy tên dịch vụ
                ThongTinDichVu.erase(ThongTinDichVu.begin() + i);  // Xóa dịch vụ khỏi danh sách
                LuuDichVu();  // Lưu danh sách dịch vụ vào file
                cout << "Da xoa dich vu thanh cong." << endl << endl;  // Thông báo xóa thành công
                return;  // Kết thúc hàm
            }
        }
        cout << "Khong tim thay dich vu." << endl << endl;  // Thông báo không tìm thấy dịch vụ
    }

    void SuaDichVu(const string& TenDichVuCu, const string& TenDichVuMoi, const string& NhaCungCapMoi, const string& GiaMoi) {  // Hàm sửa thông tin dịch vụ
    if (!KiemTraGia(GiaMoi)) {  // Kiểm tra định dạng giá dịch vụ mới
        cout << "Sai dinh dang gia dich vu." << endl << endl;  // Thông báo sai định dạng
        return;  // Kết thúc hàm
    }

    // Kiểm tra nếu tên dịch vụ mới đã tồn tại trong danh sách, nhưng không phải là dịch vụ hiện tại
    for (int i = 0; i < ThongTinDichVu.size(); i++) {
        // Nếu tên dịch vụ mới trùng với tên dịch vụ khác và không phải là tên hiện tại
        if (ThongTinDichVu[i].TenDichVu == TenDichVuMoi && ThongTinDichVu[i].TenDichVu != TenDichVuCu) {
            cout << "Dich vu moi da ton tai. Khong the sua." << endl << endl;  // Thông báo dịch vụ đã tồn tại
            return;  // Kết thúc hàm
        }
    }

    // Nếu không có tên dịch vụ trùng, thực hiện sửa
    for (int i = 0; i < ThongTinDichVu.size(); i++) {  // Lặp qua danh sách dịch vụ
        if (ThongTinDichVu[i].TenDichVu == TenDichVuCu) {  // Kiểm tra nếu tìm thấy tên dịch vụ cũ
            ThongTinDichVu[i].TenDichVu = TenDichVuMoi;  // Cập nhật tên dịch vụ
            ThongTinDichVu[i].NhaCungCap = NhaCungCapMoi;  // Cập nhật nhà cung cấp
            ThongTinDichVu[i].GiaDichVu = GiaMoi;  // Cập nhật giá dịch vụ

            LuuDichVu();  // Lưu danh sách dịch vụ vào file
            cout << "Da sua thanh cong dich vu." << endl << endl;  // Thông báo sửa thành công
            return;  // Kết thúc hàm
        }
    }

    cout << "Khong tim thay dich vu." << endl << endl;  // Thông báo không tìm thấy dịch vụ cần sửa
}


    void HienDichVu() {  // Hàm hiển thị danh sách dịch vụ
        if (ThongTinDichVu.empty()) {  // Nếu danh sách trống
            cout << "Danh sach dich vu rong!" << endl << endl;
            return;  // Kết thúc hàm
        }
        for (int i = 0; i < ThongTinDichVu.size(); i++) {  // Lặp qua danh sách dịch vụ
            Hien(ThongTinDichVu[i]);  // Hiện thông tin từng dịch vụ
        }
    }

    void Hien(const NhapDichVu& DichVu) const {  // Hàm hiển thị thông tin một dịch vụ
        cout << "Ten dich vu  : " << DichVu.TenDichVu << endl;  // In tên dịch vụ
        cout << "Nha cung cap : " << DichVu.NhaCungCap << endl;  // In nhà cung cấp
        cout << "Gia dich vu  : " << DichVu.GiaDichVu << endl;  // In giá dịch vụ
        cout << endl;  // In dòng trắng
    }
};

void QuanLiDichVu() {
    DichVu dv;
    string luachon;
    string tendv, nhacungcap, gia;

        cout << "Quan li dich vu\n";
        cout << "1. Tim dich vu\n2. Them dich vu\n3. Xoa dich vu\n4. Sua dich vu\n5. Xem dich vu\nNhap bat ky de thoat\n";
        cout << "Chon chuc nang: ";
        getline(cin, luachon);
        if (luachon == "1") {
            cout << "Tim dich vu theo (TenDichVu/NhaCungCap/Gia): ";
            getline(cin, tendv);
            dv.TimDichVu(tendv);
        }
        else if (luachon == "2") {
            cout << "Nhap ten dich vu: ";
            getline(cin, tendv);
            cout << "Nhap nha cung cap: ";
            getline(cin, nhacungcap);
            cout << "Nhap gia dich vu: ";
            getline(cin, gia);
            dv.ThemDichVu(tendv, nhacungcap, gia);
        }
        else if (luachon == "3") {
            cout << "Nhap ten dich vu muon xoa: ";
            getline(cin, tendv);
            dv.XoaDichVu(tendv);
        }
        else if (luachon == "4") {
            string tendvc, tendvmoi, nhacmoi, gamoi;
            cout << "Nhap ten dich vu cu muon sua: ";
            getline(cin, tendvc);
            cout << "Nhap ten dich vu moi: ";
            getline(cin, tendvmoi);
            cout << "Nhap nha cung cap moi: ";
            getline(cin, nhacmoi);
            cout << "Nhap gia moi: ";
            getline(cin, gamoi);
            dv.SuaDichVu(tendvc, tendvmoi, nhacmoi, gamoi);
        }
        else if (luachon == "5") {
            dv.HienDichVu();
        }
        else {
            cout << endl;
        }

}
