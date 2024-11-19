#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class DoanhThu {
private:
    struct DoanhThuItem {
        string ThangThu;  // Tháng thu (mm/yyyy)
        vector<string> DongThu;  // Danh sách giờ chiếu + số ghế (hh:mm-dd/mm/yyyy+S)
        double TienThu;  // Tổng tiền thu trong tháng
    };

    vector<DoanhThuItem> DoanhThuList;  // Danh sách các doanh thu theo tháng

public:
    DoanhThu() {
        DocDoanhThu();  // Đọc dữ liệu từ file DoanhThu.txt
    }

    // Đọc dữ liệu từ file DoanhThu.txt
    void DocDoanhThu() {
        ifstream file("DoanhThu.txt");
        string line;
        DoanhThuItem item;

        while (getline(file, line)) {
            if (line.find("Thang thu:") != string::npos) {
                if (!item.ThangThu.empty()) {
                    DoanhThuList.push_back(item);  // Lưu doanh thu của tháng cũ trước khi tiếp tục với tháng mới
                    item.DongThu.clear();
                    item.TienThu = 0.0;
                }
                item.ThangThu = line.substr(line.find(":") + 2);
            }
            else if (line.find("Dong thu :") != string::npos) {
                stringstream ss(line.substr(line.find(":") + 2));
                string gioChieuSoGhe;
                while (getline(ss, gioChieuSoGhe, ',')) {
                    item.DongThu.push_back(gioChieuSoGhe);
                }
            }
            else if (line.find("Tien thu :") != string::npos) {
                stringstream ss(line.substr(line.find(":") + 2));
                ss >> item.TienThu;
            }
        }

        // Lưu doanh thu của tháng cuối
        if (!item.ThangThu.empty()) {
            DoanhThuList.push_back(item);
        }

        file.close();
    }

    // Lưu dữ liệu vào file DoanhThu.txt
    void LuuDoanhThu() {
        ofstream file("DoanhThu.txt");
        for (const auto& item : DoanhThuList) {
            file << "Thang thu: " << item.ThangThu << endl;
            file << "Dong thu : ";
            for (size_t i = 0; i < item.DongThu.size(); ++i) {
                file << item.DongThu[i];
                if (i < item.DongThu.size() - 1) file << ", ";
            }
            file << endl;
            file << "Tien thu : " << item.TienThu << endl << endl;
        }
    }

    // Tính tổng tiền thu cho tháng thu (dạng mm/yyyy)
double TinhTienThu(const string& thangThu) {
    double tongTien = 0.0;
    ifstream file("HoaDon.txt");
    string line;
    string gioChieuSoGhe;
    double thanhTien = 0.0;

    while (getline(file, line)) {
        // Tìm dòng "Gio Chieu + So Ghe"
        if (line.find("Gio Chieu + So Ghe:") != string::npos) {
            gioChieuSoGhe = line.substr(line.find(":") + 2);  // Lấy phần sau dấu ":"
            
            // Kiểm tra tháng/năm trong giờ chiếu (giả sử định dạng: hh:mm-dd/mm/yyyy+S)
            string thangNamTrongGioChieu = gioChieuSoGhe.substr(gioChieuSoGhe.find("-") + 4, 7);  // Lấy mm/yyyy từ "dd/mm/yyyy"
            
            if (thangNamTrongGioChieu == thangThu) {
                // Nếu tháng/năm khớp, tìm thành tiền
                while (getline(file, line)) {
                    if (line.find("Thanh Tien") != string::npos) {
                        // Lấy giá trị thành tiền
                        stringstream ss(line.substr(line.find(":") + 2));
                        ss >> thanhTien;
                        tongTien += thanhTien;  // Cộng dồn tiền thu
                        break;  // Dừng lại sau khi tìm được thành tiền
                    }
                }
            }
        }
    }

    file.close();
    return tongTien;
}


    // Thêm doanh thu cho tháng
    // Thêm doanh thu cho tháng
// Kiểm tra xem tháng thu có tồn tại trong file HoaDon.txt không
bool KiemTraThangThuTrongHoaDon(const string& ThangThu) {
    ifstream file("HoaDon.txt");
    string line;
    
    while (getline(file, line)) {
        if (line.find("Gio Chieu + So Ghe:") != string::npos) {
            string gioChieuSoGhe = line.substr(line.find(":") + 2);
            string thangHoaDon = gioChieuSoGhe.substr(9, 7); // mm/yyyy từ Giờ chiếu + Số ghế
            if (thangHoaDon == ThangThu) {
                file.close();
                return true;  // Tìm thấy tháng thu trong HoaDon.txt
            }
        }
    }
    
    file.close();
    return false;  // Không tìm thấy tháng thu trong HoaDon.txt
}

// Thêm doanh thu cho tháng thu
void ThemDoanhThu(const string& ThangThu) {
    // Kiểm tra xem tháng thu đã tồn tại trong danh sách DoanhThuList chưa
    for (const auto& item : DoanhThuList) {
        if (item.ThangThu == ThangThu) {
            cout << "Doanh thu cho thang " << ThangThu << " da ton tai!" << endl << endl;
            return;  // Nếu đã tồn tại thì không thêm, thoát hàm
        }
    }

    // Kiểm tra xem tháng thu có tồn tại trong HoaDon.txt không
    if (!KiemTraThangThuTrongHoaDon(ThangThu)) {
        cout << "Khong tim thay hoa don cho thang " << ThangThu  << endl << endl;
        return;  // Nếu không có hóa đơn tương ứng, không thêm doanh thu
    }

    // Nếu chưa có tháng thu này, tiếp tục thêm doanh thu mới
    DoanhThuItem newItem;
    newItem.ThangThu = ThangThu;

    // Duyệt qua HoaDon.txt và tìm các hóa đơn có tháng thu tương ứng
    ifstream file("HoaDon.txt");
    string line;

    while (getline(file, line)) {
        if (line.find("Gio Chieu + So Ghe:") != string::npos) {
            string gioChieuSoGhe = line.substr(line.find(":") + 2);
            string thangHoaDon = gioChieuSoGhe.substr(9, 7); // mm/yyyy từ Giờ chiếu + Số ghế
            if (thangHoaDon == ThangThu) {
                newItem.DongThu.push_back(gioChieuSoGhe);  // Thêm giờ chiếu + số ghế vào dòng thu
            }
        }
    }

    // Tính tổng tiền thu
    newItem.TienThu = TinhTienThu(ThangThu);
    DoanhThuList.push_back(newItem);
    LuuDoanhThu();
    file.close();

    cout << "Them doanh thu cho thang " << ThangThu << " thanh cong!" << endl << endl;
}



    // Xem doanh thu theo tháng
    void XemDoanhThu() {
        if (DoanhThuList.empty()) {
            cout << "Khong co doanh thu nao!" << endl << endl;
            return;
        }

        for (const auto& item : DoanhThuList) {
            cout << "Thang thu: " << item.ThangThu << endl;
            cout << "Dong thu : ";
            for (const auto& gioChieuSoGhe : item.DongThu) {
                cout << gioChieuSoGhe << ", ";
            }
            cout << endl;
            cout << "Tien thu : " << item.TienThu << endl;
            cout << endl;
        }
    }

    // Tìm doanh thu theo tháng
    void TimDoanhThu(const string& ThangThu) {
        bool timThay = false;
        for (const auto& item : DoanhThuList) {
            if (item.ThangThu == ThangThu) {
                cout << "Thang thu: " << item.ThangThu << endl;
                cout << "Dong thu : ";
                for (const auto& gioChieuSoGhe : item.DongThu) {
                    cout << gioChieuSoGhe << ", ";
                }
                cout << endl;
                cout << "Tien thu : " << item.TienThu << endl;
                timThay = true;
                break;
            }
        }
        if (!timThay) {
            cout << "Khong tim thay doanh thu cho thang " << ThangThu << "!" << endl << endl;
        }
    }
    // Xóa doanh thu theo tháng thu
void XoaDoanhThu(const string& ThangThu) {
    auto it = remove_if(DoanhThuList.begin(), DoanhThuList.end(), [&](const DoanhThuItem& item) {
        return item.ThangThu == ThangThu;
    });

    if (it != DoanhThuList.end()) {
        DoanhThuList.erase(it, DoanhThuList.end());
        cout << "Xoa doanh thu cho thang " << ThangThu << " thanh cong!" << endl << endl;
        LuuDoanhThu();  // Lưu lại danh sách sau khi xóa
    } else {
        cout << "Khong tim thay doanh thu cho thang " << ThangThu << " de xoa!" << endl << endl;
    }
}
// Sửa tháng thu
void SuaDoanhThu(const string& ThangCu, const string& ThangMoi) {
    // Kiểm tra xem tháng mới có tồn tại trong HoaDon.txt không
    if (!KiemTraThangThuTrongHoaDon(ThangMoi)) {
        cout << "Khong tim thay hoa don cho thang " << ThangMoi << endl << endl;
        return;  // Nếu không có hóa đơn tương ứng, không thể sửa
    }

    for (auto& item : DoanhThuList) {
        if (item.ThangThu == ThangCu) {
            // Kiểm tra xem tháng mới đã tồn tại trong danh sách doanh thu hay chưa
            for (const auto& existingItem : DoanhThuList) {
                if (existingItem.ThangThu == ThangMoi) {
                    cout << "Thang thu " << ThangMoi << " da ton tai!" << endl << endl;
                    return;  // Nếu tháng mới đã tồn tại thì không sửa
                }
            }

            // Cập nhật lại tháng thu
            item.ThangThu = ThangMoi;
            
            // Cập nhật lại dòng thu với tháng thu mới từ HoaDon.txt
            item.DongThu.clear();  // Xóa dòng thu cũ trước khi thêm dòng thu mới
            ifstream file("HoaDon.txt");
            string line;
            
            // Duyệt qua HoaDon.txt và lấy các dòng thu có tháng thu mới
            while (getline(file, line)) {
                if (line.find("Gio Chieu + So Ghe:") != string::npos) {
                    string gioChieuSoGhe = line.substr(line.find(":") + 2);
                    string thangHoaDon = gioChieuSoGhe.substr(9, 7); // mm/yyyy từ "dd/mm/yyyy+S"
                    if (thangHoaDon == ThangMoi) {
                        item.DongThu.push_back(gioChieuSoGhe);  // Thêm dòng thu vào danh sách
                    }
                }
            }
            file.close();

            // Tính lại tổng tiền thu cho tháng mới
            item.TienThu = TinhTienThu(ThangMoi);

            cout << "Sua thang thu tu " << ThangCu << " thanh " << ThangMoi << " thanh cong!" << endl << endl;
            
            // Lưu lại danh sách doanh thu đã được sửa
            LuuDoanhThu();  

            return;
        }
    }

    cout << "Khong tim thay doanh thu cho thang " << ThangCu << " de sua!" << endl << endl;
}


};

void QuanLiDoanhThu() {
    DoanhThu dt;

    string luaChon;
    string thangThu, thangMoi;

        cout << "Quan li doanh thu" << endl;
        cout << "1. Tim doanh thu" << endl;
        cout << "2. Them doanh thu" << endl;
        cout << "3. Xoa doanh thu" << endl;
        cout << "4. Sua doanh thu" << endl;
        cout << "5. Xem doanh thu" << endl;  // Chức năng Xem doanh thu đã chuyển lên trước Thoát
        cout << "Nhap bat ki de quay lai" << endl;  // Tùy chọn Thoát cuối cùng
        cout << "Chon chuc nang: ";
        getline(cin, luaChon);

        if (luaChon == "1") {
            cout << "Nhap Thang thu (mm/yyyy) de tim: ";
            getline(cin, thangThu);
            dt.TimDoanhThu(thangThu);
        } else if (luaChon == "2") {
            cout << "Nhap Thang thu (mm/yyyy) de them: ";
            getline(cin, thangThu);
            dt.ThemDoanhThu(thangThu);
        } else if (luaChon == "3") {
            cout << "Nhap Thang thu (mm/yyyy) de xoa: ";
            getline(cin, thangThu);
            dt.XoaDoanhThu(thangThu);
        } else if (luaChon == "4") {
            cout << "Nhap Thang thu (mm/yyyy) cu: ";
            getline(cin, thangThu);
            cout << "Nhap Thang thu (mm/yyyy) moi: ";
            getline(cin, thangMoi);
            dt.SuaDoanhThu(thangThu, thangMoi);
        } else if (luaChon == "5") {  // Khi chọn Xem doanh thu
            dt.XemDoanhThu();
        } 
         else {
            cout << endl;
        }
}


