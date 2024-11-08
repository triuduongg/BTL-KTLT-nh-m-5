#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Expense {
private:
    struct Entry {
        string expenseDate;   // Ngày chi phí (dd/mm/yyyy)
        string expenseAmount; // Số tiền chi phí
        string expenseDetail; // Chi tiết chi phí
    };

    vector<Entry> expenses;

public:
    Expense() {
        loadExpenses();
    }

    void loadExpenses() {
        ifstream file("Expense.txt");
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            Entry entry;
            entry.expenseDate = line.substr(line.find(":") + 2);
            getline(file, line);
            entry.expenseAmount = line.substr(line.find(":") + 2);
            getline(file, line);
            entry.expenseDetail = line.substr(line.find(":") + 2);
            expenses.push_back(entry);
        }
    }

    void saveExpenses() {
        ofstream file("Expense.txt");
        for (int i = 0; i < expenses.size(); i++) {
            file << "Expense Date  : " << expenses[i].expenseDate << endl;
            file << "Expense Amount: " << expenses[i].expenseAmount << endl;
            file << "Expense Detail: " << expenses[i].expenseDetail << endl;
            file << endl; // Dòng trắng để dễ đọc
        }
    }

    void search(const string& input) {
        bool found = false;
        for (int i = 0; i < expenses.size(); i++) {
            if (expenses[i].expenseDate == input || expenses[i].expenseAmount == input || expenses[i].expenseDetail == input) {
                display(expenses[i]);
                found = true;
            }
        }
        if (!found) {
            cout << "Expense not found." << endl << endl;
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

    void addExpense(const string& expenseDate, const string& expenseAmount, const string& expenseDetail) {
        if (!isValidDate(expenseDate) || !isValidAmount(expenseAmount)) {
            cout << "Invalid Expense format." << endl << endl;
            return;
        }

        // Kiểm tra nếu ngày chi phí đã tồn tại
        for (int i = 0; i < expenses.size(); i++) {
            if (expenses[i].expenseDate == expenseDate) {
                cout << "Expense already exists." << endl << endl;
                return;
            }
        }

        Entry newExpense;
        newExpense.expenseDate = expenseDate;
        newExpense.expenseAmount = expenseAmount;
        newExpense.expenseDetail = expenseDetail;

        expenses.push_back(newExpense);
        saveExpenses();
        cout << "Expense added successfully." << endl << endl;
    }

    void deleteExpense(const string& expenseDate) {
        for (int i = 0; i < expenses.size(); i++) {
            if (expenses[i].expenseDate == expenseDate) {
                expenses.erase(expenses.begin() + i);
                saveExpenses();
                cout << "Expense deleted successfully." << endl << endl;
                return;
            }
        }
        cout << "Expense not found." << endl << endl;
    }

    void editExpense(const string& oldDate, const string& newDate, const string& newAmount, const string& newDetail) {
        if (!isValidDate(newDate) || !isValidAmount(newAmount)) {
            cout << "Invalid Expense format." << endl << endl;
            return;
        }

        // Chấp nhận sửa đổi ExpenseDate nếu trùng với oldDate
        for (int i = 0; i < expenses.size(); i++) {
            if (expenses[i].expenseDate == newDate && newDate != oldDate) {
                cout << "Expense already exists." << endl << endl;
                return;
            }
        }

        for (int i = 0; i < expenses.size(); i++) {
            if (expenses[i].expenseDate == oldDate) {
                expenses[i].expenseDate = newDate; // Cho phép nhập lại chính ngày
                expenses[i].expenseAmount = newAmount;
                expenses[i].expenseDetail = newDetail;

                saveExpenses();
                cout << "Expense edited successfully." << endl << endl;
                return;
            }
        }
        cout << "Expense not found." << endl << endl;
    }

    void displayExpenses() {
        if(expenses.empty()){
            cout << endl;
            return;
        }
        for (int i = 0; i < expenses.size(); i++) {
            display(expenses[i]);
        }
    }
    void clearExpenses() {
        expenses.clear();
        ofstream file("Expense.txt", ios::trunc);
        file.close();
        cout << "All Expense cleared." << endl << endl;
    }

    void display(const Entry& expense) const {
        cout << "Expense Date  : " << expense.expenseDate << endl;
        cout << "Expense Amount: " << expense.expenseAmount << endl;
        cout << "Expense Detail: " << expense.expenseDetail << endl;
        cout << endl;
    }
};

int main() {
    Expense manager;
    string choice;
    string expenseDate, newExpenseDate, expenseAmount, expenseDetail;

    do {
        cout << "Expense Manager\n";
        cout << "1. Search Expense\n2. Add Expense\n3. Delete Expense\n4. Edit Expense\n5. Display Expense\n6. Clear Expense\n7. Exit\n";
        cout << "Select operation                      : ";
        getline(cin, choice);

        if (choice == "1") {
            cout << "Expense (Date/Amount/Detail) to search: ";
            getline(cin, expenseDate);
            manager.search(expenseDate);
        } else if (choice == "2") {
            cout << "Expense Date (dd/mm/>=2024) to add    : ";
            getline(cin, expenseDate);
            cout << "Expense Amount (>=0) to add           : ";
            getline(cin, expenseAmount);
            cout << "Expense Detail to add                 : ";
            getline(cin, expenseDetail);
            manager.addExpense(expenseDate, expenseAmount, expenseDetail);
        } else if (choice == "3") {
            cout << "Expense Date (dd/mm/>=2024) to delete : ";
            getline(cin, expenseDate);
            manager.deleteExpense(expenseDate);
        } else if (choice == "4") {
            cout << "Expense Date (dd/mm/>=2024) to edit   : ";
            getline(cin, expenseDate);
            cout << "Expense Date (dd/mm/>=2024) edited    : ";
            getline(cin, newExpenseDate);
            cout << "Expense Amount (>=0) edited           : ";
            getline(cin, expenseAmount);
            cout << "Expense Detail edited                 : ";
            getline(cin, expenseDetail);
            manager.editExpense(expenseDate, newExpenseDate, expenseAmount, expenseDetail);
        } else if (choice == "5") {
            manager.displayExpenses();
        } else if (choice == "6") {
            manager.clearExpenses();
        } else if (choice != "7") {
            cout << "Invalid choice. Please try again." << endl << endl;
        }
    } while (choice != "7");

    cout << "Exiting..." << endl;

    return 0;
}
