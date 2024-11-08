#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Revenue {
private:
    struct Entry {
        string revenueDate;   // Ngày doanh thu (dd/mm/yyyy)
        string revenueAmount; // Số tiền doanh thu
        string revenueDetail; // Chi tiết doanh thu
    };

    vector<Entry> revenues;

public:
    Revenue() {
        loadRevenues();
    }

    void loadRevenues() {
        ifstream file("Revenue.txt");
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            Entry entry;
            entry.revenueDate = line.substr(line.find(":") + 2);
            getline(file, line);
            entry.revenueAmount = line.substr(line.find(":") + 2);
            getline(file, line);
            entry.revenueDetail = line.substr(line.find(":") + 2);
            revenues.push_back(entry);
        }
    }

    void saveRevenues() {
        ofstream file("Revenue.txt");
        for (int i = 0; i < revenues.size(); i++) {
            file << "Revenue Date  : " << revenues[i].revenueDate << endl;
            file << "Revenue Amount: " << revenues[i].revenueAmount << endl;
            file << "Revenue Detail: " << revenues[i].revenueDetail << endl;
            file << endl; // Dòng trắng để dễ đọc
        }
    }

    void search(const string& input) {
        bool found = false;
        for (int i = 0; i < revenues.size(); i++) {
            if (revenues[i].revenueDate == input || revenues[i].revenueAmount == input || revenues[i].revenueDetail == input) {
                display(revenues[i]);
                found = true;
            }
        }
        if (!found) {
            cout << "Revenue not found." << endl << endl;
        }
    }

    bool isValidDate(const string& date) const {
        stringstream ss(date);
        int day, month, year;
        char slash1, slash2;
        ss >> day >> slash1 >> month >> slash2 >> year;

        if (ss.fail() || slash1 != '/' || slash2 != '/' || month < 1 || month > 12 || year < 2024) {
            return false;
        }

        int daysInMonth = 31;
        if (month == 2) {
            daysInMonth = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            daysInMonth = 30;
        }

        return day > 0 && day <= daysInMonth;
    }

    bool isValidAmount(const string& amount) const {
        if (amount.empty()) return false;
        for (int i = 0; i < amount.size(); i++) {
            if (!isdigit(amount[i])) return false;
        }
        return true;
    }

    void addRevenue(const string& revenueDate, const string& revenueAmount, const string& revenueDetail) {
        if (!isValidDate(revenueDate) || !isValidAmount(revenueAmount)) {
            cout << "Invalid Revenue format." << endl << endl;
            return;
        }

        // Kiểm tra nếu ngày doanh thu đã tồn tại
        for (int i = 0; i < revenues.size(); i++) {
            if (revenues[i].revenueDate == revenueDate) {
                cout << "Revenue for this date already exists." << endl << endl;
                return;
            }
        }

        Entry newRevenue;
        newRevenue.revenueDate = revenueDate;
        newRevenue.revenueAmount = revenueAmount;
        newRevenue.revenueDetail = revenueDetail;

        revenues.push_back(newRevenue);
        saveRevenues();
        cout << "Revenue added successfully." << endl << endl;
    }

    void deleteRevenue(const string& revenueDate) {
        for (int i = 0; i < revenues.size(); i++) {
            if (revenues[i].revenueDate == revenueDate) {
                revenues.erase(revenues.begin() + i);
                saveRevenues();
                cout << "Revenue deleted successfully." << endl << endl;
                return;
            }
        }
        cout << "Revenue not found." << endl << endl;
    }

    void editRevenue(const string& oldDate, const string& newDate, const string& newAmount, const string& newDetail) {
        if (!isValidDate(newDate) || !isValidAmount(newAmount)) {
            cout << "Invalid Revenue format." << endl << endl;
            return;
        }

        // Chấp nhận sửa đổi RevenueDate nếu trùng với oldDate
        for (int i = 0; i < revenues.size(); i++) {
            if (revenues[i].revenueDate == newDate && newDate != oldDate) {
                cout << "Revenue for this date already exists." << endl << endl;
                return;
            }
        }

        for (int i = 0; i < revenues.size(); i++) {
            if (revenues[i].revenueDate == oldDate) {
                revenues[i].revenueDate = newDate; // Cho phép nhập lại chính ngày
                revenues[i].revenueAmount = newAmount;
                revenues[i].revenueDetail = newDetail;

                saveRevenues();
                cout << "Revenue edited successfully." << endl << endl;
                return;
            }
        }
        cout << "Revenue not found." << endl << endl;
    }

    void displayRevenues() {
        if(revenues.empty()){
            cout << endl;
            return;
        }
        for (int i = 0; i < revenues.size(); i++) {
            display(revenues[i]);
        }
    }
    void clearRevenues() {
        revenues.clear();
        ofstream file("Revenue.txt", ios::trunc);
        file.close();
        cout << "All Revenue cleared." << endl << endl;
    }

    void display(const Entry& revenue) const {
        cout << "Revenue Date  : " << revenue.revenueDate << endl;
        cout << "Revenue Amount: " << revenue.revenueAmount << endl;
        cout << "Revenue Detail: " << revenue.revenueDetail << endl;
        cout << endl;
    }
};

int main() {
    Revenue manager;
    string choice;
    string revenueDate, newRevenueDate, revenueAmount, revenueDetail;

    do {
        cout << "Revenue Manager\n";
        cout << "1. Search Revenue\n2. Add Revenue\n3. Delete Revenue\n4. Edit Revenue\n5. Display Revenue\n6. Clear Revenue\n7. Exit\n";
        cout << "Select operation                      : ";
        getline(cin, choice);

        if (choice == "1") {
            cout << "Revenue (Date/Amount/Detail) to search: ";
            getline(cin, revenueDate);
            manager.search(revenueDate);
        } else if (choice == "2") {
            cout << "Revenue Date (dd/mm/>=2024) to add    : ";
            getline(cin, revenueDate);
            cout << "Revenue Amount (>=0) to add           : ";
            getline(cin, revenueAmount);
            cout << "Revenue Detail to add                 : ";
            getline(cin, revenueDetail);
            manager.addRevenue(revenueDate, revenueAmount, revenueDetail);
        } else if (choice == "3") {
            cout << "Revenue Date (dd/mm/>=2024) to delete : ";
            getline(cin, revenueDate);
            manager.deleteRevenue(revenueDate);
        } else if (choice == "4") {
            cout << "Revenue Date (dd/mm/>=2024) to edit   : ";
            getline(cin, revenueDate);
            cout << "Revenue Date (dd/mm/>=2024) edited    : ";
            getline(cin, newRevenueDate);
            cout << "Revenue Amount (>=0) edited           : ";
            getline(cin, revenueAmount);
            cout << "Revenue Detail edited                 : ";
            getline(cin, revenueDetail);
            manager.editRevenue(revenueDate, newRevenueDate, revenueAmount, revenueDetail);
        } else if (choice == "5") {
            manager.displayRevenues();
        } else if (choice == "6") {
            manager.clearRevenues();
        } else if (choice != "7") {
            cout << "Invalid choice. Please try again." << endl << endl;
        }
    } while (choice != "7");

    cout << "Exiting..." << endl;

    return 0;
}
