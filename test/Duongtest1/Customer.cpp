#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Customer {
private:
    struct CustomerInfo {
        string phone;
        string name;
        string age;
    };

    vector<CustomerInfo> customers;

public:
    Customer() {
        loadCustomers();
    }

    void loadCustomers() {
        ifstream file("KhachHang.txt");
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            CustomerInfo customer;
            customer.phone = line.substr(line.find(":") + 2);
            getline(file, line);
            customer.name = line.substr(line.find(":") + 2);
            getline(file, line);
            customer.age = line.substr(line.find(":") + 2);
            customers.push_back(customer);
        }
    }

    void saveCustomers() {
        ofstream file("KhachHang.txt", ios::app);
        for (int i = 0; i < customers.size(); i++) {
            file << "So dien thoai khach hang: " << customers[i].phone << endl;
            file << "Ten khach hang          : " << customers[i].name << endl;
            file << "Tuoi khach hang         : " << customers[i].age << endl;
            file << endl; // Dòng trắng để dễ đọc
        }
    }

    void search(const string& input) {
        bool found = false;
        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].phone == input || customers[i].name == input || customers[i].age == input) {
                display(customers[i]);
                found = true;
            }
        }
        if (!found) {
            cout << "Khong thay khach hang." << endl << endl;
        }
    }

    void addCustomer(const string& phone, const string& name, const string& age) {
        if (!isValidPhone(phone)) {
            cout << "So dien thoai khach hang khong hop le." << endl << endl;
            return;
        }

        if (!isValidAge(age)) {
            cout << "Tuoi khach hang khong hop le." << endl << endl;
            return;
        }

        CustomerInfo newCustomer;
        newCustomer.phone = phone;
        newCustomer.name = name;
        newCustomer.age = age;

        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].phone == phone) {
                cout << "Khach hang da ton tai." << endl << endl;
                return;
            }
        }

        customers.push_back(newCustomer);
        saveCustomers();
        cout << "Da them khach hang." << endl << endl;
    }

    void deleteCustomer(const string& phone) {
        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].phone == phone) {
                customers.erase(customers.begin() + i);
                saveCustomers();
                cout << "Da xoa khach hang." << endl << endl;
                return;
            }
        }
        cout << "Khong thay khach hang." << endl << endl;
    }

    void editCustomer(const string& oldPhone, const string& newPhone, const string& newName, const string& newAge) {
        if (!isValidPhone(newPhone)) {
            cout << "So dien thoai khach hang khong hop le." << endl << endl;
            return;
        }

        if (!isValidAge(newAge)) {
            cout << "Tuoi khach hang khong hop le." << endl << endl;
            return;
        }

        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].phone == newPhone && newPhone != oldPhone) {
                cout << "Khach hang da ton tai." << endl << endl;
                return;
            }
        }

        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].phone == oldPhone) {
                customers[i].phone = newPhone;
                customers[i].name = newName;
                customers[i].age = newAge;

                saveCustomers();
                cout << "Da sua khach hang." << endl << endl;
                return;
            }
        }
        cout << "Khong thay khach hang." << endl << endl;
    }

    void displayCustomers() {
        if(customers.empty()){
            cout << endl;
            return;
        }
        for (int i = 0; i < customers.size(); i++) {
            display(customers[i]);
        }
    }

    void display(const CustomerInfo& customer) const {
        cout << "So dien thoai khach hang: " << customer.phone << endl;
        cout << "Ten khach hang          : " << customer.name << endl;
        cout << "Tuoi khach hang         : " << customer.age << endl;
        cout << endl;
    }

    bool isValidPhone(const string& phone) const {
        return phone.length() == 10 && phone[0] == '0' && phone.substr(1).find_first_not_of("0123456789") == string::npos;
    }

    bool isValidAge(const string& ageStr) const {
        if (ageStr.empty()) return false;

        for (int i = 0; i < ageStr.length(); i++) {
            if (!isdigit(ageStr[i])) return false; // Kiểm tra xem có phải là số không
        }

        // Chuyển đổi chuỗi sang số bằng cách thủ công
        int age = 0;
        for (int i = 0; i < ageStr.length(); i++) {
            age = age * 10 + (ageStr[i] - '0'); // Tính toán giá trị số
        }
        
        return age >= 3; // Kiểm tra tuổi
    }
};

int main() {
    Customer manager;
    string choice;
    string phone, newPhone, name, age;

    do {
        cout << "Quan li khach hang\n";
        cout << "1. Tim khach hang\n2. Them khach hang\n3. Xoa khach hang\n4. Sua khach hang\n5. Xem khach hang\n6. Thoat\n";
        cout << "Lua chon chuc nang                          : ";
        getline(cin, choice);

        if (choice == "1") {
            cout << "Tim khach hang theo (So dien thoai/Ten/Tuoi): ";
            getline(cin, phone);
            manager.search(phone);
        } else if (choice == "2") {
            cout << "Them so dien thoai khach hang               : ";
            getline(cin, phone);
            cout << "Them ten khach hang                         : ";
            getline(cin, name);
            cout << "Them tuoi khach hang (>=3)                  : ";
            getline(cin, age);
            manager.addCustomer(phone, name, age);
        } else if (choice == "3") {
            cout << "Nhap so dien thoai khach hang de xoa        : ";
            getline(cin, phone);
            manager.deleteCustomer(phone);
        } else if (choice == "4") {
            cout << "So dien thoai khach hang muon sua           : ";
            getline(cin, phone);
            cout << "Sua so dien thoai khach hang                : ";
            getline(cin, newPhone);
            cout << "Sua ten khach hang                          : ";
            getline(cin, name);
            cout << "Sua tuoi khach hang                         : ";
            getline(cin, age);
            manager.editCustomer(phone, newPhone, name, age);
        } else if (choice == "5") {
            manager.displayCustomers();
        } else if (choice == "6") {
            break;
        } else if (choice != "6") {
            cout << "Lua chon khong hop le, hay thu lai." << endl << endl;
        }
    } while (true);

    cout << "Dang thoat..." << endl;

    return 0;
}
