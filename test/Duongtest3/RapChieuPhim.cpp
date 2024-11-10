#include <iostream>
#include "QuanLiKhachHang.cpp"
#include "QuanLiLichChieu.cpp"
#include "QuanLiGhe.cpp"
#include "QuanLiDichVu.cpp"
#include "QuanLiNhanVien.cpp"
#include "QuanLiVe.cpp"
#include "QuanLiDanhGia.cpp"

using namespace std;

int main() {
    string luaChon;

    do {
        cout << "Quan li rap chieu phim\n";
        cout << "a. Quan li khach hang\nb. Quan li lich chieu\nc. Quan li ghe\nd. Quan li dich vu\ne. Quan li nhan vien\nf. Quan li ve\ng. Quan li hoa don\nh. Quan li danh gia\ni. Quan li chi phi\nj. Quan li doanh thu\n0. Thoat\n";
        cout << "Chon quan li: ";
        getline(cin, luaChon);
        if (luaChon == "a") {
        	cout << endl;
        	QuanLiKhachHang();
        }
        else if (luaChon == "b") {
        	cout << endl;
            QuanLiLichChieu();
        }
        else if (luaChon == "c") {
        	cout << endl;
            QuanLiGhe();
        }
        else if (luaChon == "d") {
        	cout << endl;
            QuanLiDichVu();
        }
        else if (luaChon == "e") {
        	cout << endl;
            QuanLiNhanVien();
        }
        else if (luaChon == "f") {
        	cout << endl;
            QuanLiVe();
        }
        else if (luaChon == "g") {
        	cout << endl;
            
        }
        else if (luaChon == "h") {
        	cout << endl;
            QuanLiDanhGia();
        }
        else if (luaChon == "i") {
        	cout << endl;
            
        }
        else if (luaChon == "j") {
        	cout << endl;
            
        }
        else if (luaChon != "0") {
            cout << "Lua chon khong hop le, vui long thu lai.\n\n";
        }

    } while (luaChon != "0");
    cout << "Thoat chuong trinh...";
    return 0;
}