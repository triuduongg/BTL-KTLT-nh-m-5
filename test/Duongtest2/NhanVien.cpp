#include <iostream>     // Thư viện cho các thao tác nhập xuất cơ bản
#include <fstream>      // Thư viện cho thao tác với file
#include <sstream>      // Thư viện cho thao tác với chuỗi (string)
#include <vector>       // Thư viện cho cấu trúc dữ liệu vector
#include <string>       // Thư viện cho kiểu dữ liệu chuỗi

using namespace std;    // Sử dụng không gian tên std để tránh phải viết std:: mỗi lần

class NhanVien {       // Định nghĩa lớp NhanVien
private:
    struct NhapNhanVien { // Định nghĩa cấu trúc để lưu thông tin nhân viên
        string CCCD;        // Mã CCCD (12 chữ số)
        string TenNhanVien; // Tên nhân viên
        string Luong;      // Lương của nhân viên
    };

    vector<NhapNhanVien> ThongTinNhanVien; // Vector chứa danh sách thông tin nhân viên

public:
    NhanVien() {            // Hàm khởi tạo của lớp
        DuyetNhanVien();   // Gọi hàm DuyetNhanVien để đọc thông tin từ file
    }

    void DuyetNhanVien() { // Hàm để duyệt và đọc thông tin nhân viên từ file
        ifstream Tep("NhanVien.txt"); // Mở file NhanVien.txt để đọc
        string Dong;                     // Biến lưu từng dòng đọc từ file
        while (getline(Tep, Dong)) {   // Đọc từng dòng trong file
            if (Dong.empty()) continue; // Nếu dòng trống thì bỏ qua
            NhapNhanVien GhiThongTin;  // Khai báo một biến để lưu thông tin nhân viên
            GhiThongTin.CCCD = Dong.substr(Dong.find(":") + 2); // Lấy CCCD từ dòng
            getline(Tep, Dong);         // Đọc dòng tiếp theo
            GhiThongTin.TenNhanVien = Dong.substr(Dong.find(":") + 2); // Lấy tên nhân viên
            getline(Tep, Dong);         // Đọc dòng tiếp theo
            GhiThongTin.Luong = Dong.substr(Dong.find(":") + 2); // Lấy lương
            ThongTinNhanVien.push_back(GhiThongTin); // Thêm thông tin nhân viên vào vector
        }
    }

    void LuuNhanVien() { // Hàm để lưu thông tin nhân viên vào file
        ofstream Tep("NhanVien.txt"); // Mở file NhanVien.txt để ghi
        for (int i = 0; i < ThongTinNhanVien.size(); i++) { // Lặp qua từng nhân viên
            Tep << "CCCD         : " << ThongTinNhanVien[i].CCCD << endl; // Ghi CCCD
            Tep << "Ten nhan vien: " << ThongTinNhanVien[i].TenNhanVien << endl; // Ghi tên nhân viên
            Tep << "Luong        : " << ThongTinNhanVien[i].Luong << endl; // Ghi lương
            Tep << endl; // Ghi dòng trắng để dễ đọc
        }
    }

    void TimNhanVien(const string& DauVao) { // Hàm tìm nhân viên theo CCCD, tên hoặc lương
        bool TimThay = false; // Biến đánh dấu có tìm thấy nhân viên hay không
        for (int i = 0; i < ThongTinNhanVien.size(); i++) { // Lặp qua danh sách nhân viên
            if (ThongTinNhanVien[i].CCCD == DauVao || // Kiểm tra CCCD
                ThongTinNhanVien[i].TenNhanVien == DauVao || // Kiểm tra tên nhân viên
                ThongTinNhanVien[i].Luong == DauVao) { // Kiểm tra lương
                Hien(ThongTinNhanVien[i]); // Hiện thông tin nhân viên
                TimThay = true; // Đánh dấu đã tìm thấy
            }
        }
        if (!TimThay) { // Nếu không tìm thấy
            cout << "Khong tim thay nhan vien." << endl << endl; // Thông báo không tìm thấy
        }
    }

    bool KiemTraCCCD(const string& CCCD) const { // Hàm kiểm tra định dạng CCCD
        if (CCCD.length() != 12) return false; // CCCD phải có 12 ký tự
        for (int i = 0; i < 12; i++) { // Lặp qua từng ký tự
            if (!isdigit(CCCD[i])) return false; // Kiểm tra xem có phải số không
        }
        return true; // Trả về true nếu định dạng hợp lệ
    }

    bool KiemTraLuong(const string& Luong) const { // Hàm kiểm tra định dạng lương
        if (Luong.empty() || (Luong.length() > 1 && Luong[0] == '0')) return false; // Không để lương rỗng và không bắt đầu bằng 0
        for (int i = 0; i < Luong.size(); i++) { // Lặp qua từng ký tự
            if (!isdigit(Luong[i])) return false; // Kiểm tra xem có phải số không
        }
        return true; // Trả về true nếu định dạng hợp lệ
    }

    void ThemNhanVien(const string& CCCD, const string& TenNhanVien, const string& Luong) { // Hàm thêm nhân viên
        if (!KiemTraCCCD(CCCD) || !KiemTraLuong(Luong)) { // Kiểm tra định dạng CCCD và lương
            cout << "Sai dinh dang nhan vien." << endl << endl; // Thông báo sai định dạng
            return; // Kết thúc hàm
        }

        NhapNhanVien NhanVienMoi; // Khai báo một nhân viên mới
        NhanVienMoi.CCCD = CCCD; // Gán CCCD cho nhân viên mới
        NhanVienMoi.TenNhanVien = TenNhanVien; // Gán tên cho nhân viên mới
        NhanVienMoi.Luong = Luong; // Gán lương cho nhân viên mới

        for (int i = 0; i < ThongTinNhanVien.size(); i++) { // Lặp qua danh sách nhân viên
            if (ThongTinNhanVien[i].CCCD == CCCD) { // Kiểm tra nếu CCCD đã tồn tại
                cout << "Da ton tai nhan vien." << endl << endl; // Thông báo đã tồn tại
                return; // Kết thúc hàm
            }
        }

        ThongTinNhanVien.push_back(NhanVienMoi); // Thêm nhân viên mới vào danh sách
        LuuNhanVien(); // Lưu danh sách nhân viên vào file
        cout << "Da them thanh cong nhan vien." << endl << endl; // Thông báo thêm thành công
    }

    void XoaNhanVien(const string& CCCD) { // Hàm xóa nhân viên theo CCCD
        for (int i = 0; i < ThongTinNhanVien.size(); i++) { // Lặp qua danh sách nhân viên
            if (ThongTinNhanVien[i].CCCD == CCCD) { // Kiểm tra nếu tìm thấy CCCD
                ThongTinNhanVien.erase(ThongTinNhanVien.begin() + i); // Xóa nhân viên khỏi danh sách
                LuuNhanVien(); // Lưu danh sách nhân viên vào file
                cout << "Da xoa nhan vien thanh cong." << endl << endl; // Thông báo xóa thành công
                return; // Kết thúc hàm
            }
        }
        cout << "Khong tim thay nhan vien." << endl << endl; // Thông báo không tìm thấy nhân viên
    }

    void SuaNhanVien(const string& CCCDCu, const string& CCCDMoi, const string& TenNhanVienMoi, const string& LuongMoi) { // Hàm sửa thông tin nhân viên
        if (!KiemTraCCCD(CCCDMoi) || !KiemTraLuong(LuongMoi)) { // Kiểm tra định dạng CCCD mới và lương mới
            cout << "Sai dinh dang nhan vien." << endl << endl; // Thông báo sai định dạng
            return; // Kết thúc hàm
        }

        // Kiểm tra nếu CCCD mới đã tồn tại và khác với CCCD cũ
        for (int i = 0; i < ThongTinNhanVien.size(); i++) {
            if (ThongTinNhanVien[i].CCCD == CCCDMoi && CCCDMoi != CCCDCu) {
                cout << "Da ton tai nhan vien." << endl << endl; // Thông báo đã tồn tại
                return; // Kết thúc hàm
            }
        }

        for (int i = 0; i < ThongTinNhanVien.size(); i++) { // Lặp qua danh sách nhân viên
            if (ThongTinNhanVien[i].CCCD == CCCDCu) { // Kiểm tra nếu tìm thấy CCCD cũ
                ThongTinNhanVien[i].CCCD = CCCDMoi; // Cập nhật CCCD
                ThongTinNhanVien[i].TenNhanVien = TenNhanVienMoi; // Cập nhật tên
                ThongTinNhanVien[i].Luong = LuongMoi; // Cập nhật lương

                LuuNhanVien(); // Lưu danh sách nhân viên vào file
                cout << "Da sua thanh cong nhan vien." << endl << endl; // Thông báo sửa thành công
                return; // Kết thúc hàm
            }
        }
        cout << "Khong tim thay nhan vien." << endl << endl; // Thông báo không tìm thấy nhân viên
    }

    void HienNhanVien() { // Hàm hiển thị danh sách nhân viên
        if (ThongTinNhanVien.empty()) { // Nếu danh sách trống
            cout << endl; // In dòng trắng
            return; // Kết thúc hàm
        }
        for (int i = 0; i < ThongTinNhanVien.size(); i++) { // Lặp qua danh sách nhân viên
            Hien(ThongTinNhanVien[i]); // Hiện thông tin từng nhân viên
        }
    }

    void Hien(const NhapNhanVien& NhanVien) const { // Hàm hiển thị thông tin một nhân viên
        cout << "CCCD         : " << NhanVien.CCCD << endl; // In CCCD
        cout << "Ten nhan vien: " << NhanVien.TenNhanVien << endl; // In tên nhân viên
        cout << "Luong        : " << NhanVien.Luong << endl; // In lương
        cout << endl; // In dòng trắng
    }
};
 int main() {
 	NhanVien nv;
 	string luachon;
 	string cccd, cccdmoi, ten, luong;
 	do {
 		cout << "Quan li nhan vien\n";
 	    cout << "1. Tim nhan vien\n2. Them nhan vien\n3. Xoa nhan vien\n4. Sua nhan vien\n5. Xem nhan vien\n6. Thoat\n";
 	    cout << "Chon chuc nang: ";
 	    getline(cin, luachon);
 		if(luachon=="1") {
 			cout << "Tim nhan vien theo (CCCD/Ten/Luong): ";
 			getline(cin, cccd);
 			nv.TimNhanVien(cccd);
		 }
		 else if(luachon=="2"){
		 	cout << "Them CCCD (XXXXXXXXXXXX): ";
		 	getline(cin, cccd);
		 	cout << "Them ten nhan vien: ";
		 	getline(cin, ten);
		 	cout << "Them luong: ";
		 	getline(cin, luong);
		 	nv.ThemNhanVien(cccd, ten, luong);
		 }
		 else if(luachon=="3"){
		 	cout << "Nhap CCCD cua nhan vien muon xoa: ";
		 	getline(cin, cccd);
		 	nv.XoaNhanVien(cccd);
		 }
		 else if(luachon=="4"){
		 	cout << "Nhap CCCD cua nhan vien muon sua: ";
		 	getline(cin, cccd);
		 	cout << "Nhap CCCD moi sua: ";
		 	getline(cin, cccdmoi);
		 	cout << "Nhap ten nhan vien moi sua: ";
		 	getline(cin, ten);
		 	cout << "Nhap luong moi sua: ";
		 	getline(cin, luong);
		 	nv.SuaNhanVien(cccd, cccdmoi, ten, luong);
		 }
		 else if(luachon=="5"){
		 	nv.HienNhanVien();
		 }
		 else if(luachon!="6"){
		 	cout << "Lua chon khong hop le, hay thu lai\n\n";
		 } 
		 } while(luachon!="6");
		 cout << "Thoat chuong trinh...";
		 return 0;
 }
