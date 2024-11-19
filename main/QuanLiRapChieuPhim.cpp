#include <iostream>
#include "QuanLiKhachHang.cpp"
#include "QuanLiLichChieu.cpp"
#include "QuanLiNhanVien.cpp"
#include "QuanLiGhe.cpp"
#include "QuanLiDichVu.cpp"
#include "QuanLiVe.cpp"
#include "QuanLiDanhGia.cpp"
#include "QuanLiHoaDon.cpp"
#include "QuanLiDoanhThu.cpp"
#include "QuanLiChiPhi.cpp"

using namespace std;

int main() {
    string luaChon;

    do {
        cout << "Quan li rap chieu phim\n";
        cout << "a. Quan li lich chieu\nb. Quan li ghe\nc. Quan li dich vu\nd. Quan li nhan vien\ne. Quan li khach hang\nf. Quan li ve\ng. Quan li hoa don\nh. Quan li danh gia\ni. Quan li chi phi\nj. Quan li doanh thu\n0. Thoat\n";
        cout << "Chon quan li: ";
        getline(cin, luaChon);
        if (luaChon == "a") {
        	cout << endl;
        	QuanLiLichChieu();
        }
        else if (luaChon == "b") {
        	cout << endl;
        	QuanLiGhe();
        }
        else if (luaChon == "c") {
        	cout << endl;
        	QuanLiDichVu();
        }
        else if (luaChon == "d") {
        	cout << endl;
        	QuanLiNhanVien();
        }
        else if (luaChon == "e") {
        	cout << endl;
            QuanLiKhachHang();
        }
        else if (luaChon == "f") {
        	cout << endl;
            QuanLiVe();
        }
        else if (luaChon == "g") {
        	cout << endl;
            QuanLiHoaDon();
        }
        else if (luaChon == "h") {
        	cout << endl;
            QuanLiDanhGia();
        }
        else if (luaChon == "i") {
        	cout << endl;
            QuanLiChiPhi();
        }
        else if (luaChon == "j") {
        	cout << endl;
            QuanLiDoanhThu();
        }
        else if (luaChon != "0") {
            cout << "Lua chon khong hop le, vui long thu lai.\n\n";
        }

    } while (luaChon != "0");
    cout << "Thoat chuong trinh...";
    return 0;
}