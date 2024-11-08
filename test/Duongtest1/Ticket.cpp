#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Ticket {
private:
    struct TicketInfo {
        string code;
        string date; // Thay đổi từ time thành date
        string price;
    };

    vector<TicketInfo> tickets;

public:
    Ticket() {
        loadTickets();
    }

    void loadTickets() {
        ifstream file("Ticket.txt");
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            TicketInfo ticket;
            ticket.code = line.substr(line.find(":") + 2);
            getline(file, line);
            ticket.date = line.substr(line.find(":") + 2); // Đọc date
            getline(file, line);
            ticket.price = line.substr(line.find(":") + 2);
            tickets.push_back(ticket);
        }
    }

    void saveTickets() {
        ofstream file("Ticket.txt");
        for (int i = 0; i < tickets.size(); i++) {
            file << "Ticket Code : " << tickets[i].code << endl;
            file << "Ticket Date : " << tickets[i].date << endl; // Ghi date
            file << "Ticket Price: " << tickets[i].price << endl;
            file << endl; // Dòng trắng để dễ đọc
        }
    }

    void search(const string& input) {
        bool found = false;
        for (int i = 0; i < tickets.size(); i++) {
            if (tickets[i].code == input || tickets[i].date == input || tickets[i].price == input) {
                display(tickets[i]);
                found = true;
            }
        }
        if (!found) {
            cout << "Ticket not found." << endl << endl;
        }
    }

    void addTicket(const string& code, const string& date, const string& price) {
        if (!isValidCode(code)) {
            cout << "Invalid Ticket format." << endl << endl;
            return;
        }

        if (!isValidDate(date)) {
            cout << "Invalid Ticket format." << endl << endl;
            return;
        }

        if (!isValidPrice(price)) {
            cout << "Invalid Ticket format." << endl << endl;
            return;
        }

        // Kiểm tra xem ticket code đã tồn tại chưa
        for (int i = 0; i < tickets.size(); i++) {
            if (tickets[i].code == code) {
                cout << "Ticket already exists." << endl << endl;
                return;
            }
        }

        TicketInfo newTicket;
        newTicket.code = code;
        newTicket.date = date;
        newTicket.price = price;

        tickets.push_back(newTicket);
        saveTickets();
        cout << "Ticket added successfully." << endl << endl;
    }

    void deleteTicket(const string& code) {
        for (int i = 0; i < tickets.size(); i++) {
            if (tickets[i].code == code) {
                tickets.erase(tickets.begin() + i);
                saveTickets();
                cout << "Ticket deleted successfully." << endl << endl;
                return;
            }
        }
        cout << "Ticket not found." << endl << endl;
    }

    void editTicket(const string& oldCode, const string& newCode, const string& newDate, const string& newPrice) {
        if (!isValidCode(newCode)) {
            cout << "Invalid Ticket format." << endl << endl;
            return;
        }

        if (!isValidDate(newDate)) {
            cout << "Invalid Ticket format." << endl << endl;
            return;
        }

        if (!isValidPrice(newPrice)) {
            cout << "Invalid Ticket format." << endl << endl;
            return;
        }

        // Chỉ kiểm tra nếu mã code mới khác mã code cũ
        if (oldCode != newCode) {
            for (int i = 0; i < tickets.size(); i++) {
                if (tickets[i].code == newCode) {
                    cout << "Ticket code already exists." << endl << endl;
                    return;
                }
            }
        }

        for (int i = 0; i < tickets.size(); i++) {
            if (tickets[i].code == oldCode) {
                tickets[i].code = newCode; // Cập nhật mã code
                tickets[i].date = newDate; // Cập nhật date
                tickets[i].price = newPrice;

                saveTickets();
                cout << "Ticket edited successfully." << endl << endl;
                return;
            }
        }
        cout << "Ticket not found." << endl << endl;
    }

    void displayTickets() {
        if(tickets.empty()){
            cout << endl;
            return;
        }
        for (int i = 0; i < tickets.size(); i++) {
            display(tickets[i]);
        }
    }
    void clearTickets() {
        tickets.clear();
        ofstream file("Ticket.txt", ios::trunc);
        file.close();
        cout << "All Ticket cleared." << endl << endl;
    }
    void display(const TicketInfo& ticket) const {
        cout << "Ticket Code : " << ticket.code << endl;
        cout << "Ticket Date : " << ticket.date << endl; // Hiển thị date
        cout << "Ticket Price: " << ticket.price << endl;
        cout << endl;
    }

    bool isValidCode(const string& code) const {
        for (int i = 0; i < code.length(); i++) {
            if (!isalnum(code[i])) return false; // Kiểm tra từng ký tự
        }
        return true;
    }

    bool isValidDate(const string& date) const {
        stringstream ss(date);
        int day, month, year;
        char slash1, slash2;

        ss >> day >> slash1 >> month >> slash2 >> year;

        return !ss.fail() && slash1 == '/' && slash2 == '/' &&
               year >= 2024 && isValidDate(day, month, year);
    }

    bool isValidDate(int day, int month, int year) const {
        int daysInMonth = 31;
        if (month == 2) {
            daysInMonth = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            daysInMonth = 30;
        }
        return day > 0 && day <= daysInMonth;
    }

    bool isValidPrice(const string& priceStr) const {
        if (priceStr.empty()) return false;

        for (int i = 0; i < priceStr.length(); i++) {
            if (!isdigit(priceStr[i])) return false; // Kiểm tra xem có phải là số không
        }

        // Chuyển đổi chuỗi sang số bằng cách thủ công
        int price = 0;
        for (int i = 0; i < priceStr.length(); i++) {
            price = price * 10 + (priceStr[i] - '0'); // Tính toán giá trị số
        }

        return price >= 0; // Kiểm tra giá
    }
};

int main() {
    Ticket manager;
    string choice;
    string code, newCode, date, price;

    do {
        cout << "Ticket Manager\n";
        cout << "1. Search Ticket\n2. Add Ticket\n3. Delete Ticket\n4. Edit Ticket\n5. Display Ticket\n6. Clear Ticket\n7. Exit\n";
        cout << "Select operation                        : ";
        getline(cin, choice);

        if (choice == "1") {
            cout << "Ticket (Code/Date/Price) to search      : ";
            getline(cin, code);
            manager.search(code);
        } else if (choice == "2") {
            cout << "Ticket Code (numbers, letters) to add   : ";
            getline(cin, code);
            cout << "Ticket Date (dd/mm/>=2024) to add       : ";
            getline(cin, date);
            cout << "Ticket Price (>=0) to add               : ";
            getline(cin, price);
            manager.addTicket(code, date, price);
        } else if (choice == "3") {
            cout << "Ticket Code (numbers, letters) to delete: ";
            getline(cin, code);
            manager.deleteTicket(code);
        } else if (choice == "4") {
            cout << "Ticket Code (numbers, letters) to edit  : ";
            getline(cin, code);
            cout << "Ticket Code (numbers, letters) edited   : ";
            getline(cin, newCode);
            cout << "Ticket Date (dd/mm/>=2024) edited       : ";
            getline(cin, date);
            cout << "Ticket Price (>=0) edited               : ";
            getline(cin, price);
            manager.editTicket(code, newCode, date, price);
        } else if (choice == "5") {
            manager.displayTickets();
        } else if (choice == "6") {
            manager.clearTickets();
        } else if (choice != "7") {
            cout << "Invalid choice. Please try again." << endl << endl;
        }
    } while (choice != "7");

    cout << "Exiting..." << endl;

    return 0;
}
