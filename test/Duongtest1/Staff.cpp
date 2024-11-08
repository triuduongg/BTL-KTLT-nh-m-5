#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Staff {
private:
    struct Entry {
        string staffID;    // StaffID (12 chữ số)
        string staffName;  // StaffName
        string staffSalary; // StaffSalary
    };

    vector<Entry> staffMembers;

public:
    Staff() {
        loadStaff();
    }

    void loadStaff() {
        ifstream file("Staff.txt");
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            Entry entry;
            entry.staffID = line.substr(line.find(":") + 2);
            getline(file, line);
            entry.staffName = line.substr(line.find(":") + 2);
            getline(file, line);
            entry.staffSalary = line.substr(line.find(":") + 2);
            staffMembers.push_back(entry);
        }
    }

    void saveStaff() {
        ofstream file("Staff.txt");
        for (int i = 0; i < staffMembers.size(); i++) {
            file << "Staff ID    : " << staffMembers[i].staffID << endl;
            file << "Staff Name  : " << staffMembers[i].staffName << endl;
            file << "Staff Salary: " << staffMembers[i].staffSalary << endl;
            file << endl; // Dòng trắng để dễ đọc
        }
    }

    void search(const string& input) {
        bool found = false;
        for (int i = 0; i < staffMembers.size(); i++) {
            if (staffMembers[i].staffID == input || staffMembers[i].staffName == input || staffMembers[i].staffSalary == input) {
                display(staffMembers[i]);
                found = true;
            }
        }
        if (!found) {
            cout << "Staff not found." << endl << endl;
        }
    }

    bool isValidStaffID(const string& staffID) const {
        if (staffID.length() != 12) return false;
        for (int i = 0; i < 12; i++) {
            if (!isdigit(staffID[i])) return false;
        }
        return true;
    }

    bool isValidStaffSalary(const string& staffSalary) const {
        if (staffSalary.empty()) return false;
        for (int i = 0; i < staffSalary.size(); i++) {
            if (!isdigit(staffSalary[i])) return false;
        }
        return true;
    }

    void addStaff(const string& staffID, const string& staffName, const string& staffSalary) {
        if (!isValidStaffID(staffID) || !isValidStaffSalary(staffSalary)) {
            cout << "Invalid Staff format." << endl << endl;
            return;
        }

        Entry newStaff;
        newStaff.staffID = staffID;
        newStaff.staffName = staffName;
        newStaff.staffSalary = staffSalary;

        for (int i = 0; i < staffMembers.size(); i++) {
            if (staffMembers[i].staffID == staffID) {
                cout << "Staff already exists." << endl << endl;
                return;
            }
        }

        staffMembers.push_back(newStaff);
        saveStaff();
        cout << "Staff added successfully." << endl << endl;
    }

    void deleteStaff(const string& staffID) {
        for (int i = 0; i < staffMembers.size(); i++) {
            if (staffMembers[i].staffID == staffID) {
                staffMembers.erase(staffMembers.begin() + i);
                saveStaff();
                cout << "Staff deleted successfully." << endl << endl;
                return;
            }
        }
        cout << "Staff not found." << endl << endl;
    }

    void editStaff(const string& oldStaffID, const string& newStaffID, const string& newStaffName, const string& newStaffSalary) {
        if (!isValidStaffID(newStaffID) || !isValidStaffSalary(newStaffSalary)) {
            cout << "Invalid Staff format." << endl << endl;
            return;
        }

        // Chấp nhận sửa đổi StaffID nếu trùng với oldStaffID
        for (int i = 0; i < staffMembers.size(); i++) {
            if (staffMembers[i].staffID == newStaffID && newStaffID != oldStaffID) {
                cout << "Staff already exists." << endl << endl;
                return;
            }
        }

        for (int i = 0; i < staffMembers.size(); i++) {
            if (staffMembers[i].staffID == oldStaffID) {
                staffMembers[i].staffID = newStaffID; // Cho phép nhập lại chính StaffID
                staffMembers[i].staffName = newStaffName;
                staffMembers[i].staffSalary = newStaffSalary;

                saveStaff();
                cout << "Staff edited successfully." << endl << endl;
                return;
            }
        }
        cout << "Staff not found." << endl << endl;
    }

    void displayStaff() {
        if(staffMembers.empty()){
            cout << endl;
            return;
        }
        for (int i = 0; i < staffMembers.size(); i++) {
            display(staffMembers[i]);
        }
    }
    void clearStaff() {
        staffMembers.clear();
        ofstream file("Staff.txt", ios::trunc);
        file.close();
        cout << "All Staff cleared." << endl << endl;
    }

    void display(const Entry& staff) const {
        cout << "Staff ID    : " << staff.staffID << endl;
        cout << "Staff Name  : " << staff.staffName << endl;
        cout << "Staff Salary: " << staff.staffSalary << endl;
        cout << endl;
    }
};

int main() {
    Staff manager;
    string choice;
    string staffID, newStaffID, staffName, staffSalary;

    do {
        cout << "Staff Manager\n";
        cout << "1. Search Staff\n2. Add Staff\n3. Delete Staff\n4. Edit Staff\n5. Display Staff\n6. Clear Staff\n7. Exit\n";
        cout << "Select operation                 : ";
        getline(cin, choice);

        if (choice == "1") {
            cout << "Staff (ID/Name/Salary) to search : ";
            getline(cin, staffID);
            manager.search(staffID);
        } else if (choice == "2") {
            cout << "Staff ID (XXXXXXXXXXXX) to add   : ";
            getline(cin, staffID);
            cout << "Staff Name to add                : ";
            getline(cin, staffName);
            cout << "Staff Salary (>=0) to add        : ";
            getline(cin, staffSalary);
            manager.addStaff(staffID, staffName, staffSalary);
        } else if (choice == "3") {
            cout << "Staff ID (XXXXXXXXXXXX) to delete: ";
            getline(cin, staffID);
            manager.deleteStaff(staffID);
        } else if (choice == "4") {
            cout << "Staff ID (XXXXXXXXXXXX) to edit  : ";
            getline(cin, staffID);
            cout << "Staff ID (XXXXXXXXXXXX) edited   : ";
            getline(cin, newStaffID);
            cout << "Staff Name edited                : ";
            getline(cin, staffName);
            cout << "Staff Salary (>=0) edited        : ";
            getline(cin, staffSalary);
            manager.editStaff(staffID, newStaffID, staffName, staffSalary);
        } else if (choice == "5") {
            manager.displayStaff();
        } else if (choice == "6") {
            manager.clearStaff();
        } else if (choice != "7") {
            cout << "Invalid choice. Please try again." << endl << endl;
        }
    } while (choice != "7");

    cout << "Exiting..." << endl;

    return 0;
}
