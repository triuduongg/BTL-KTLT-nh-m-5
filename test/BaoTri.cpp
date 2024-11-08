#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class BaoTri {
private:
    struct Entry {
        string maintenanceDate;  // Ngay bao tri (dd/mm/yyyy)
        string issue;            // Van de bao tri (doi tuong tham chieu)
        string fee;              // Phi bao tri
    };

    vector<Entry> maintenances;

public:
    BaoTri() {
        loadMaintenances();
    }

    // Load data from the maintenance file
    void loadMaintenances() {
        ifstream file("BaoTri.txt");
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            Entry entry;
            entry.maintenanceDate = line.substr(line.find(":") + 2);
            getline(file, line);
            entry.issue = line.substr(line.find(":") + 2);
            getline(file, line);
            entry.fee = line.substr(line.find(":") + 2);
            maintenances.push_back(entry);
        }
    }

    // Save maintenances data to the file
    void saveMaintenances() {
        ofstream file("BaoTri.txt", ios::app);
        for (int i = 0; i < maintenances.size(); i++) {
            file << "Ngay bao tri  : " << maintenances[i].maintenanceDate << endl;
            file << "Van de bao tri: " << maintenances[i].issue << endl;
            file << "Phi bao tri   : " << maintenances[i].fee << endl;
            file << endl; // New line for easy reading
        }
    }

    // Read schedule dates from the LichChieu.txt file
    vector<string> readSchedulesFromFile() {
        ifstream file("LichChieu.txt");
        string line;
        vector<string> scheduleDates;

        while (getline(file, line)) {
            if (line.empty()) continue;
            string scheduleDate = line.substr(line.find(":") + 2);  // Extract the date part
            scheduleDate = scheduleDate.substr(6, 10);  // Extract dd/mm/yyyy
            scheduleDates.push_back(scheduleDate);
            getline(file, line); // Skip movie title
            getline(file, line); // Skip duration
        }
        return scheduleDates;
    }

    // Check for conflicts with the schedule dates
    bool isMaintenanceConflictingWithSchedules(const string& maintenanceDate) {
        vector<string> scheduleDates = readSchedulesFromFile();  // Get all schedule dates
        for (const auto& scheduleDate : scheduleDates) {
            if (scheduleDate == maintenanceDate) {
                return true;  // Conflict detected
            }
        }
        return false;  // No conflict
    }

    // Check if maintenance fee is valid (only digits)
    bool isValidMaintenanceFee(const string& fee) const {
        if (fee.empty()) return false;  // Empty fee is not valid
        for (int i = 0; i < fee.size(); i++) {
            if (!isdigit(fee[i])) return false;  // Non-digit characters make fee invalid
        }
        // Convert fee string to integer and check if it's non-negative
        int feeValue = stoi(fee);
        return feeValue >= 0;
    }
    // Kiểm tra xem ngày bảo trì đã tồn tại trong danh sách không
bool isDateAlreadyExists(const string& maintenanceDate) {
    for (int i = 0; i < maintenances.size(); i++) {
        if (maintenances[i].maintenanceDate == maintenanceDate) {
            return true;  // Ngày bảo trì đã tồn tại
        }
    }
    return false;  // Ngày bảo trì chưa tồn tại
}
    // Hàm kiểm tra tính hợp lệ của ngày (dd/mm/yyyy)
bool isValidDate(const string& date) const {
    if (date.size() != 10) return false;  // Đảm bảo chuỗi dài 10 ký tự
    if (date[2] != '/' || date[5] != '/') return false;  // Kiểm tra dấu '/' tại đúng vị trí
    
    // Kiểm tra ngày, tháng, năm có phải là số không
    for (int i = 0; i < date.size(); i++) {
        if ((i == 2 || i == 5)) continue; // Bỏ qua dấu '/'
        if (!isdigit(date[i])) return false; // Kiểm tra mỗi ký tự là số
    }

    // Phân tách ngày, tháng, năm
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    // Kiểm tra tính hợp lệ của ngày tháng
    if (month < 1 || month > 12) return false; // Tháng phải từ 1 đến 12
    if (day < 1 || day > 31) return false;    // Ngày phải từ 1 đến 31

    // Kiểm tra tháng 2 (tháng 2 có 28 hoặc 29 ngày tùy vào năm nhuận)
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if ((isLeapYear && day > 29) || (!isLeapYear && day > 28)) return false;
    }
    // Kiểm tra tháng có 30 ngày
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) return false;
    }

    return true; // Nếu tất cả các kiểm tra đều hợp lệ
}

    // Add a new maintenance task
    // Thêm bảo trì vào hệ thống
void addMaintenance(const string& maintenanceDate, const string& issue, const string& fee) {
    if (maintenanceDate.empty() || issue.empty() || !isValidMaintenanceFee(fee) || !isValidDate(maintenanceDate)) {
        cout << "Dinh dang bao tri khong hop le." << endl << endl;
        return;
    }

    // Kiểm tra xem ngày bảo trì đã tồn tại trong danh sách chưa
    if (isDateAlreadyExists(maintenanceDate)) {
        cout << "Bao tri da ton tai voi ngay bao tri " << maintenanceDate << "." << endl << endl;
        return;
    }

    // Kiểm tra xem ngày bảo trì có xung đột với lịch chiếu không
    if (isMaintenanceConflictingWithSchedules(maintenanceDate)) {
        cout << "Xung dot: Ngay bao tri trung voi ngay chieu." << endl << endl;
        return;
    }

    // Thêm bảo trì nếu không có lỗi
    Entry newMaintenance;
    newMaintenance.maintenanceDate = maintenanceDate;
    newMaintenance.issue = issue;
    newMaintenance.fee = fee;

    maintenances.push_back(newMaintenance);
    saveMaintenances();
    cout << "Them bao tri thanh cong." << endl << endl;
}

    // Delete a maintenance task
    void deleteMaintenance(const string& maintenanceDate) {
        for (int i = 0; i < maintenances.size(); i++) {
            if (maintenances[i].maintenanceDate == maintenanceDate) {
                maintenances.erase(maintenances.begin() + i);
                saveMaintenances();
                cout << "Xoa bao tri thanh cong." << endl << endl;
                return;
            }
        }
        cout << "Bao tri khong ton tai." << endl << endl;
    }

    // Edit an existing maintenance task
    // Edit an existing maintenance task
// Sửa thông tin bảo trì
// Edit an existing maintenance task
// Sửa thông tin bảo trì
void editMaintenance(const string& oldMaintenanceDate, const string& newMaintenanceDate, const string& newIssue, const string& newFee) {
    if (newIssue.empty() || !isValidMaintenanceFee(newFee) || !isValidDate(oldMaintenanceDate) || !isValidDate(newMaintenanceDate)) {
        cout << "Dinh dang bao tri khong hop le." << endl << endl;
        return;
    }

    // Nếu ngày bảo trì không thay đổi (ngày cũ và ngày mới giống nhau)
    if (oldMaintenanceDate == newMaintenanceDate) {
        // Kiểm tra xem bảo trì có tồn tại với ngày này không
        for (int i = 0; i < maintenances.size(); i++) {
            if (maintenances[i].maintenanceDate == oldMaintenanceDate) {
                // Cập nhật vấn đề và phí, giữ nguyên ngày bảo trì
                maintenances[i].issue = newIssue;
                maintenances[i].fee = newFee;

                // Ghi lại dữ liệu đã sửa vào file
                ofstream file("BaoTri.txt", ios::trunc);  // Mở file và ghi lại toàn bộ danh sách bảo trì
                for (int i = 0; i < maintenances.size(); i++) {
                    file << "Ngay bao tri  : " << maintenances[i].maintenanceDate << endl;
                    file << "Van de bao tri: " << maintenances[i].issue << endl;
                    file << "Phi bao tri   : " << maintenances[i].fee << endl;
                    file << endl; // New line for easy reading
                }

                cout << "Sua bao tri thanh cong." << endl << endl;
                return;
            }
        }
        cout << "Bao tri khong ton tai." << endl << endl;
        return;
    }

    // Nếu ngày bảo trì mới thay đổi, kiểm tra xung đột với lịch chiếu
    if (isMaintenanceConflictingWithSchedules(newMaintenanceDate)) {
        cout << "Xung dot: Ngay bao tri moi trung voi ngay chieu." << endl << endl;
        return;
    }

    // Kiểm tra xem ngày bảo trì mới có tồn tại trong danh sách bảo trì không
    if (isDateAlreadyExists(newMaintenanceDate)) {
        cout << "Bao tri da ton tai voi ngay bao tri " << newMaintenanceDate << "." << endl << endl;
        return;
    }

    // Tìm và sửa bảo trì cũ nếu ngày bảo trì thay đổi
    for (int i = 0; i < maintenances.size(); i++) {
        if (maintenances[i].maintenanceDate == oldMaintenanceDate) {
            // Cập nhật ngày bảo trì, vấn đề và phí
            maintenances[i].maintenanceDate = newMaintenanceDate;
            maintenances[i].issue = newIssue;
            maintenances[i].fee = newFee;

            // Ghi lại dữ liệu đã sửa vào file
            ofstream file("BaoTri.txt", ios::trunc);  // Mở file và ghi lại toàn bộ danh sách bảo trì
            for (int i = 0; i < maintenances.size(); i++) {
                file << "Ngay bao tri  : " << maintenances[i].maintenanceDate << endl;
                file << "Van de bao tri: " << maintenances[i].issue << endl;
                file << "Phi bao tri   : " << maintenances[i].fee << endl;
                file << endl; // New line for easy reading
            }

            cout << "Sua bao tri thanh cong." << endl << endl;
            return;
        }
    }

    cout << "Bao tri khong ton tai." << endl << endl;
}




    // Display all maintenance tasks
    void displayMaintenances() {
        if (maintenances.empty()) {
            cout << "Khong co bao tri nao." << endl << endl;
            return;
        }
        for (int i = 0; i < maintenances.size(); i++) {
            display(maintenances[i]);
        }
    }

    // Display a single maintenance entry
    void display(const Entry& maintenance) const {
        cout << "Ngay bao tri  : " << maintenance.maintenanceDate << endl;
        cout << "Van de bao tri: " << maintenance.issue << endl;
        cout << "Phi bao tri   : " << maintenance.fee << endl;
        cout << endl;
    }

    // Search for maintenance tasks based on input (can search by date, issue, or fee)
    void search(const string& input) {
        bool found = false;
        for (int i = 0; i < maintenances.size(); i++) {
            if (maintenances[i].maintenanceDate == input || maintenances[i].issue == input || maintenances[i].fee == input) {
                display(maintenances[i]);
                found = true;
            }
        }
        if (!found) {
            cout << "Thong tin bao tri khong ton tai." << endl << endl;
        }
    }
};

int main() {
    BaoTri manager;
    string choice;
    string maintenanceDate, newMaintenanceDate, issue, fee;

    do {
        cout << "Bao Tri Manager\n";
        cout << "1. Tim kiem bao tri\n2. Them bao tri\n3. Xoa bao tri\n4. Sua bao tri\n5. Xem danh sach bao tri\n6. Thoat\n";
        cout << "Chon thao tac                       : ";
        getline(cin, choice);

        if (choice == "1") {
            cout << "Bao tri (Ngay/Van de/Phi) can tim: ";
            getline(cin, maintenanceDate);
            manager.search(maintenanceDate);  // Tìm kiếm theo ngày bảo trì, vấn đề hoặc phí
        } else if (choice == "2") {
            cout << "Ngay bao tri can them (dd/mm/yyyy)  : ";
            getline(cin, maintenanceDate);
            cout << "Van de bao tri can them             : ";
            getline(cin, issue);
            cout << "Phi bao tri can them (>=0)          : ";
            getline(cin, fee);
            manager.addMaintenance(maintenanceDate, issue, fee);
        } else if (choice == "3") {
            cout << "Ngay bao tri can xoa                : ";
            getline(cin, maintenanceDate);
            manager.deleteMaintenance(maintenanceDate);
        } else if (choice == "4") {
            cout << "Ngay bao tri can sua                : ";
            getline(cin, maintenanceDate);
            cout << "Ngay bao tri moi                   : ";
            getline(cin, newMaintenanceDate);
            cout << "Van de bao tri moi                  : ";
            getline(cin, issue);
            cout << "Phi bao tri moi (>=0)               : ";
            getline(cin, fee);
            manager.editMaintenance(maintenanceDate, newMaintenanceDate, issue, fee);
        } else if (choice == "5") {
            manager.displayMaintenances();
        } else if (choice != "6") {
            cout << "Lua chon khong hop le. Vui long chon lai." << endl << endl;
        }
    } while (choice != "6");

    cout << "Thoat chuong trinh..." << endl;

    return 0;
}
