#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

string generateLogFileName() {
    time_t t = time(0);
    tm* tm = localtime(&t);
    
    stringstream ss;

    // Tạo tên file theo định dạng HHMMSS_DDMMYYYY.txt
    ss << "Log_"
       << (tm->tm_hour < 10 ? "0" : "") << tm->tm_hour
       << (tm->tm_min < 10 ? "0" : "") << tm->tm_min
       << (tm->tm_sec < 10 ? "0" : "") << tm->tm_sec << "_"
       << (tm->tm_mday < 10 ? "0" : "") << tm->tm_mday
       << (tm->tm_mon + 1 < 10 ? "0" : "") << (tm->tm_mon + 1)
       << (tm->tm_year + 1900);

    ss << ".txt"; // Thêm phần mở rộng file

    return ss.str(); // Trả về chuỗi tên file
}

const string LogFileName = generateLogFileName();

void writeToLogFile(const string& message) {
    ofstream File(LogFileName.c_str(), ios::app); // Sử dụng .c_str() để chuyển đổi
    if (!File) {
        return;
    }
    File << message;
    File.close();
}
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
        ifstream file("Customer.txt");
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
        ofstream file("Customer.txt");
        for (int i = 0; i < customers.size(); i++) {
            file << "Customer Phone: " << customers[i].phone << endl;
            file << "Customer Name : " << customers[i].name << endl;
            file << "Customer Age  : " << customers[i].age << endl;
            file << endl; // Dòng trắng để dễ đọc
        }
    }

    void search(const string& input) {
        bool found = false;
        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].phone == input || customers[i].name == input || customers[i].age == input) {
                writeToLogFile("Searched Customer!\n");
                found = true;
                break;
            }
        }
        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].phone == input || customers[i].name == input || customers[i].age == input) {
                display(customers[i]);
                found = true;
            }
        }
        if (!found) {
            cout << "Customer not found." << endl << endl;
        }
    }

    void addCustomer(const string& phone, const string& name, const string& age) {
        if (!isValidPhone(phone)) {
            cout << "Invalid Customer format." << endl << endl;
            return;
        }

        if (!isValidAge(age)) {
            cout << "Invalid Customer format." << endl << endl;
            return;
        }

        CustomerInfo newCustomer;
        newCustomer.phone = phone;
        newCustomer.name = name;
        newCustomer.age = age;

        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].phone == phone) {
                cout << "Customer already exists." << endl << endl;
                return;
            }
        }

        customers.push_back(newCustomer);
        saveCustomers();
        cout << "Customer added successfully." << endl << endl;
        writeToLogFile("Added Customer!\n");
        writeToLogFile("Customer Phone: " + phone + "\n");
        writeToLogFile("Customer Name : " + name + "\n");
        writeToLogFile("Customer Age  : " + age + "\n\n");
    }

    void deleteCustomer(const string& phone) {
        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].phone == phone) {
                writeToLogFile("Deleted Customer!\n");
                writeToLogFile("Customer Phone: " + customers[i].phone + "\n");
                writeToLogFile("Customer Name : " + customers[i].name + "\n");
                writeToLogFile("Customer Age  : " + customers[i].age + "\n\n");
                customers.erase(customers.begin() + i);
                saveCustomers();
                cout << "Customer deleted successfully." << endl << endl;
                return;
            }
        }
        cout << "Customer not found." << endl << endl;
    }

    void editCustomer(const string& oldPhone, const string& newPhone, const string& newName, const string& newAge) {
        if (!isValidPhone(newPhone)) {
            cout << "Invalid Customer format." << endl << endl;
            return;
        }

        if (!isValidAge(newAge)) {
            cout << "Invalid Customer format." << endl << endl;
            return;
        }

        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].phone == newPhone && newPhone != oldPhone) {
                cout << "Customer already exists." << endl << endl;
                return;
            }
        }

        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].phone == oldPhone) {
                writeToLogFile("Edit Customer!\n");
                writeToLogFile("Customer Phone: " + customers[i].phone + "\n");
                writeToLogFile("Customer Name : " + customers[i].name + "\n");
                writeToLogFile("Customer Age  : " + customers[i].age + "\n");
                customers[i].phone = newPhone;
                customers[i].name = newName;
                customers[i].age = newAge;

                saveCustomers();
                cout << "Customer edited successfully." << endl << endl;
                writeToLogFile("Edited Customer!\n");
                writeToLogFile("Customer Phone: " + customers[i].phone + "\n");
                writeToLogFile("Customer Name : " + customers[i].name + "\n");
                writeToLogFile("Customer Age  : " + customers[i].age + "\n\n");
                return;
            }
        }
        cout << "Customer not found." << endl << endl;
    }

    void displayCustomers() {
        if(customers.empty()){
            cout << endl;
            return;
        }
        writeToLogFile("Displayed Customer!\n");
        for (int i = 0; i < customers.size(); i++) {
            display(customers[i]);
        }
    }

    void clearCustomers(){
        customers.clear();
        ofstream file("Customer.txt", ios::trunc);
        file.close();
        cout << "All Customer cleared." << endl << endl;
        writeToLogFile("Cleared Customer!\n\n");
    }

    void display(const CustomerInfo& customer) const {
        cout << "Customer Phone: " << customer.phone << endl;
        cout << "Customer Name : " << customer.name << endl;
        cout << "Customer Age  : " << customer.age << endl << endl;
        writeToLogFile("Customer Phone: " + customer.phone + "\n");
        writeToLogFile("Customer Name : " + customer.name + "\n");
        writeToLogFile("Customer Age  : " + customer.age + "\n\n");
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
                writeToLogFile("Searched Ticket!\n");
                found = true;
                break;
            }
        }
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
        writeToLogFile("Added Ticket!\n");
        writeToLogFile("Ticket Code : " + code + "\n");
        writeToLogFile("Ticket Date : " + date + "\n");
        writeToLogFile("Ticket Price: " + price + "\n\n");
    }

    void deleteTicket(const string& code) {
        for (int i = 0; i < tickets.size(); i++) {
            if (tickets[i].code == code) {
                writeToLogFile("Deleted Ticket!\n");
                writeToLogFile("Ticket Code : " + tickets[i].code + "\n");
                writeToLogFile("Ticket Date : " + tickets[i].date + "\n");
                writeToLogFile("Ticket Price: " + tickets[i].price + "\n\n");
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
                writeToLogFile("Edit Ticket!\n");
                writeToLogFile("Ticket Code : " + tickets[i].code + "\n");
                writeToLogFile("Ticket Date : " + tickets[i].date + "\n");
                writeToLogFile("Ticket Price: " + tickets[i].price + "\n");
                tickets[i].code = newCode; // Cập nhật mã code
                tickets[i].date = newDate; // Cập nhật date
                tickets[i].price = newPrice;

                saveTickets();
                cout << "Ticket edited successfully." << endl << endl;
                writeToLogFile("Edited Ticket!\n");
                writeToLogFile("Ticket Code : " + tickets[i].code + "\n");
                writeToLogFile("Ticket Date : " + tickets[i].date + "\n");
                writeToLogFile("Ticket Price: " + tickets[i].price + "\n\n");
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
        writeToLogFile("Displayed Ticket!\n");
        for (int i = 0; i < tickets.size(); i++) {
            display(tickets[i]);
        }
    }
    void clearTickets() {
        tickets.clear();
        ofstream file("Ticket.txt", ios::trunc);
        file.close();
        cout << "All Ticket cleared." << endl << endl;
        writeToLogFile("Cleared Ticket!\n\n");
    }

    void display(const TicketInfo& ticket) const {
        cout << "Ticket Code : " << ticket.code << endl;
        cout << "Ticket Date : " << ticket.date << endl; // Hiển thị date
        cout << "Ticket Price: " << ticket.price << endl << endl;
        writeToLogFile("Ticket Code : " + ticket.code + "\n");
        writeToLogFile("Ticket Date : " + ticket.date + "\n");
        writeToLogFile("Ticket Price: " + ticket.price + "\n\n");
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
class Schedule {
private:
    struct Entry {
        string movie;
        string scheduleTime; // Giờ bắt đầu (hh:mm)
        string scheduleDate; // Ngày chiếu (dd/mm/yyyy)
    };

    vector<Entry> schedules;

public:
    Schedule() {
        loadSchedules();
    }

    void loadSchedules() {
        ifstream file("Schedule.txt");
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            Entry entry;
            entry.movie = line.substr(line.find(":") + 2);
            getline(file, line);
            entry.scheduleTime = line.substr(line.find(":") + 2);
            getline(file, line);
            entry.scheduleDate = line.substr(line.find(":") + 2);
            schedules.push_back(entry);
        }
    }

    void saveSchedules() {
        ofstream file("Schedule.txt");
        for (int i = 0; i < schedules.size(); i++) {
            file << "Schedule Movie: " << schedules[i].movie << endl;
            file << "Schedule Time : " << schedules[i].scheduleTime << endl;
            file << "Schedule Date : " << schedules[i].scheduleDate << endl;
            file << endl; // Dòng trắng để dễ đọc
        }
    }

    void search(const string& input) {
        bool found = false;
        for (int i = 0; i < schedules.size(); i++) {
            if (schedules[i].movie == input || schedules[i].scheduleTime == input || schedules[i].scheduleDate == input) {
                writeToLogFile("Searched Schedule!\n");
                found = true;
                break;
            }
        }
        for (int i = 0; i < schedules.size(); i++) {
            if (schedules[i].movie == input || schedules[i].scheduleTime == input || schedules[i].scheduleDate == input) {
                display(schedules[i]);
                found = true;
            }
        }
        if (!found) {
            cout << "Schedule not found." << endl << endl;
        }
    }

    void addSchedule(const string& movie, const string& scheduleTime, const string& scheduleDate) {
        Entry newSchedule;
        newSchedule.movie = movie;
        newSchedule.scheduleTime = scheduleTime;
        newSchedule.scheduleDate = scheduleDate;

        for (int i = 0; i < schedules.size(); i++) {
            if (schedules[i].movie == movie) {
                cout << "Schedule already exists." << endl << endl;
                return;
            }
        }
        if (!isValidTime(scheduleTime) || !isValidDate(scheduleDate)) {
            cout << "Invalid Schedule format." << endl << endl;
            return;
        }

        schedules.push_back(newSchedule);
        saveSchedules();
        cout << "Schedule added successfully." << endl << endl;
        writeToLogFile("Added Schedule!\n");
        writeToLogFile("Schedule Movie: " + movie + "\n");
        writeToLogFile("Schedule Time : " + scheduleTime + "\n");
        writeToLogFile("Schedule Date : " + scheduleDate + "\n\n");
    }

    void deleteSchedule(const string& movie) {
        for (int i = 0; i < schedules.size(); i++) {
            if (schedules[i].movie == movie) {
                writeToLogFile("Deleted Schedule!\n");
                writeToLogFile("Schedule Movie: " + schedules[i].movie + "\n");
                writeToLogFile("Schedule Time : " + schedules[i].scheduleTime + "\n");
                writeToLogFile("Schedule Date : " + schedules[i].scheduleDate + "\n\n");
                schedules.erase(schedules.begin() + i);
                saveSchedules();
                cout << "Schedule deleted successfully." << endl << endl;
                return;
            }
        }
        cout << "Schedule not found." << endl << endl;
    }

    void editSchedule(const string& oldMovie, const string& newMovie, const string& newScheduleTime, const string& newScheduleDate) {
        for (int i = 0; i < schedules.size(); i++) {
            if (schedules[i].movie == newMovie && newMovie != oldMovie) {
                cout << "Schedule already exists." << endl << endl;
                return;
            }
        }

        for (int i = 0; i < schedules.size(); i++) {
            if (schedules[i].movie == oldMovie) {
                if (!isValidTime(newScheduleTime) || !isValidDate(newScheduleDate)) {
                    cout << "Invalid Schedule format." << endl << endl;
                    return;
                }
                writeToLogFile("Edit Schedule!\n");
                writeToLogFile("Schedule Movie: " + schedules[i].movie + "\n");
                writeToLogFile("Schedule Time : " + schedules[i].scheduleTime + "\n");
                writeToLogFile("Schedule Date : " + schedules[i].scheduleDate + "\n");
                schedules[i].movie = newMovie;
                schedules[i].scheduleTime = newScheduleTime;
                schedules[i].scheduleDate = newScheduleDate;

                saveSchedules();
                cout << "Schedule edited successfully." << endl << endl;
                writeToLogFile("Edited Schedule!\n");
                writeToLogFile("Schedule Movie: " + schedules[i].movie + "\n");
                writeToLogFile("Schedule Time : " + schedules[i].scheduleTime + "\n");
                writeToLogFile("Schedule Date : " + schedules[i].scheduleDate + "\n\n");
                return;
            }
        }
        cout << "Schedule not found." << endl << endl;
    }

    void displaySchedules() {
        if(schedules.empty()){
            cout << endl;
            return;
        }
        writeToLogFile("Displayed Schedule!\n");
        for (int i = 0; i < schedules.size(); i++) {
            display(schedules[i]);
        }
    }
    void clearSchedules() {
        schedules.clear();
        ofstream file("Schedule.txt", ios::trunc);
        file.close();
        cout << "All Schedule cleared." << endl << endl;
        writeToLogFile("Cleared Schedule!\n\n");
    }

    void display(const Entry& schedule) const {
        cout << "Schedule Movie: " << schedule.movie << endl;
        cout << "Schedule Time : " << schedule.scheduleTime << endl;
        cout << "Schedule Date : " << schedule.scheduleDate << endl << endl;
        writeToLogFile("Schedule Movie: " + schedule.movie + "\n");
        writeToLogFile("Schedule Time : " + schedule.scheduleTime + "\n");
        writeToLogFile("Schedule Date : " + schedule.scheduleDate + "\n\n");
    }

    bool isValidTime(const string& time) const {
        stringstream ss(time);
        int hour, minute;
        char colon;
        ss >> hour >> colon >> minute;

        return !(ss.fail() || colon != ':' || hour < 0 || hour > 23 || minute < 0 || minute > 59);
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
};
class Event {
private:
    struct Entry {
        string eventName;
        string startDate;
        string endDate;
    };

    vector<Entry> events;

public:
    Event() {
        loadEvents();
    }

    void loadEvents() {
        ifstream file("Event.txt");
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            Entry entry;
            entry.eventName = line.substr(line.find(":") + 2);
            getline(file, line);
            entry.startDate = line.substr(line.find(":") + 2);
            getline(file, line);
            entry.endDate = line.substr(line.find(":") + 2);
            events.push_back(entry);
        }
    }

    void saveEvents() {
        ofstream file("Event.txt");
        for (int i = 0; i < events.size(); i++) {
            file << "Event Name     : " << events[i].eventName << endl;
            file << "Event Startdate: " << events[i].startDate << endl;
            file << "Event Enddate  : " << events[i].endDate << endl;
            file << endl; // Dòng trắng để dễ đọc
        }
    }

    void search(const string& input) {
        bool found = false;
        for (int i = 0; i < events.size(); i++) {
            if (events[i].eventName == input || events[i].startDate == input || events[i].endDate == input) {
                writeToLogFile("Searched Event!\n");
                found = true;
                break;
            }
        }
        for (int i = 0; i < events.size(); i++) {
            if (events[i].eventName == input || events[i].startDate == input || events[i].endDate == input) {
                display(events[i]);
                found = true;
            }
        }
        if (!found) {
            cout << "Event not found." << endl << endl;
        }
    }

    void addEvent(const string& eventName, const string& startDate, const string& endDate) {
        Entry newEvent;
        newEvent.eventName = eventName;
        newEvent.startDate = startDate;
        newEvent.endDate = endDate;

        for (int i = 0; i < events.size(); i++) {
            if (events[i].eventName == eventName) {
                cout << "Event already exists." << endl << endl;
                return;
            }
        }
        if (!isValidDate(startDate) || !isValidDate(endDate)) {
            cout << "Invalid Event format." << endl << endl;
            return;
        }
        if (!isEndDateAfterStartDate(startDate, endDate)) {
            cout << "Invalid Event format." << endl << endl;
            return;
        }

        events.push_back(newEvent);
        saveEvents();
        cout << "Event added successfully." << endl << endl;
        writeToLogFile("Added Event!\n");
        writeToLogFile("Event Name     : " + eventName + "\n");
        writeToLogFile("Event Startdate: " + startDate + "\n");
        writeToLogFile("Event Enddate  : " + endDate + "\n\n");
    }

    void deleteEvent(const string& eventName) {
        for (int i = 0; i < events.size(); i++) {
            if (events[i].eventName == eventName) {
                writeToLogFile("Deleted Event!\n");
                writeToLogFile("Event Name     : " + events[i].eventName + "\n");
                writeToLogFile("Event Startdate: " + events[i].startDate + "\n");
                writeToLogFile("Event Enddate  : " + events[i].endDate + "\n\n");
                events.erase(events.begin() + i);
                saveEvents();
                cout << "Event deleted successfully." << endl << endl;
                return;
            }
        }
        cout << "Event not found." << endl << endl;
    }

    void editEvent(const string& oldEventName, const string& newEventName, const string& newStartDate, const string& newEndDate) {
        for (int i = 0; i < events.size(); i++) {
            if (events[i].eventName == newEventName && newEventName != oldEventName) {
                cout << "Event already exists." << endl << endl;
                return;
            }
        }

        for (int i = 0; i < events.size(); i++) {
            if (events[i].eventName == oldEventName) {
                if (!isValidDate(newStartDate) || !isValidDate(newEndDate)) {
                    cout << "Invalid Event format." << endl << endl;
                    return;
                }
                if (!isEndDateAfterStartDate(newStartDate, newEndDate)) {
                    cout << "Invalid Event format" << endl << endl;
                    return;
                }
                writeToLogFile("Edit Event!\n");
                writeToLogFile("Event Movie    : " + events[i].eventName + "\n");
                writeToLogFile("Event Startdate: " + events[i].startDate + "\n");
                writeToLogFile("Event Enddate  : " + events[i].endDate + "\n");

                Entry updatedEvent;
                updatedEvent.eventName = newEventName;
                updatedEvent.startDate = newStartDate;
                updatedEvent.endDate = newEndDate;
                events[i] = updatedEvent;

                saveEvents();
                cout << "Event edited successfully." << endl << endl;
                writeToLogFile("Edited Event!\n");
                writeToLogFile("Event Name     : " + events[i].eventName + "\n");
                writeToLogFile("Event Startdate: " + events[i].startDate + "\n");
                writeToLogFile("Event Enddate  : " + events[i].endDate + "\n\n");
                return;
            }
        }
        cout << "Event not found." << endl << endl;
    }

    void displayEvents() {
        if(events.empty()){
            cout << endl;
            return;
        }
        writeToLogFile("Displayed Event!\n");
        for (int i = 0; i < events.size(); i++) {
            display(events[i]);
        }
    }
    void clearEvents() {
        events.clear();
        ofstream file("Event.txt", ios::trunc);
        file.close();
        cout << "All Event cleared." << endl << endl;
        writeToLogFile("Cleared Event!\n\n");
    }

    void display(const Entry& event) const {
        cout << "Event Name     : " << event.eventName << endl;
        cout << "Event Startdate: " << event.startDate << endl;
        cout << "Event Enddate  : " << event.endDate << endl << endl;
        writeToLogFile("Event Name     : " + event.eventName + "\n");
        writeToLogFile("Event Startdate: " + event.startDate + "\n");
        writeToLogFile("Event Enddate  : " + event.endDate + "\n\n");
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

    bool isEndDateAfterStartDate(const string& startDate, const string& endDate) const {
        int startDay, startMonth, startYear;
        int endDay, endMonth, endYear;

        getDate(startDate, startDay, startMonth, startYear);
        getDate(endDate, endDay, endMonth, endYear);

        if (endYear > startYear) return true;
        if (endYear == startYear) {
            if (endMonth > startMonth) return true;
            if (endMonth == startMonth) {
                return endDay >= startDay;
            }
        }
        return false;
    }

    void getDate(const string& date, int& day, int& month, int& year) const {
        stringstream ss(date);
        char slash1, slash2;
        ss >> day >> slash1 >> month >> slash2 >> year;
    }
};
class Room {
private:
    struct Entry {
        string roomNumber; // RoomNumber
        string roomSeat;   // RoomSeat
        string roomStatus; // RoomStatus
    };

    vector<Entry> rooms;

public:
    Room() {
        loadRooms();
    }

    void loadRooms() {
        ifstream file("Room.txt");
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            Entry entry;
            entry.roomNumber = line.substr(line.find(":") + 2);
            getline(file, line);
            entry.roomSeat = line.substr(line.find(":") + 2);
            getline(file, line);
            entry.roomStatus = line.substr(line.find(":") + 2);
            rooms.push_back(entry);
        }
    }

    void saveRooms() {
        ofstream file("Room.txt");
        for (int i = 0; i < rooms.size(); i++) {
            file << "Room Number: " << rooms[i].roomNumber << endl;
            file << "Room Seat  : " << rooms[i].roomSeat << endl;
            file << "Room Status: " << rooms[i].roomStatus << endl;
            file << endl; // Dòng trắng để dễ đọc
        }
    }

    void search(const string& input) {
        bool found = false;
        for (int i = 0; i < rooms.size(); i++) {
            if (rooms[i].roomNumber == input || rooms[i].roomSeat == input || rooms[i].roomStatus == input) {
                writeToLogFile("Searched Room!\n");
                break;
                found = true;
            }
        }
        for (int i = 0; i < rooms.size(); i++) {
            if (rooms[i].roomNumber == input || rooms[i].roomSeat == input || rooms[i].roomStatus == input) {
                display(rooms[i]);
                found = true;
            }
        }
        if (!found) {
            cout << "Room not found." << endl << endl;
        }
    }

    bool isValidRoomNumber(const string& roomNumber) const {
        if (roomNumber.empty()) return false;
        for (int i = 0; i < roomNumber.size(); i++) {
            if (!isdigit(roomNumber[i])) return false;
        }
        int num = 0;
        for (int i = 0; i < roomNumber.size(); i++) {
            num = num * 10 + (roomNumber[i] - '0');
        }
        return num >= 1;
    }

    bool isValidRoomSeat(const string& roomSeat) const {
        if (roomSeat.empty()) return false;
        for (int i = 0; i < roomSeat.size(); i++) {
            if (!isdigit(roomSeat[i])) return false;
        }
        int num = 0;
        for (int i = 0; i < roomSeat.size(); i++) {
            num = num * 10 + (roomSeat[i] - '0');
        }
        return num >= 0;
    }

    bool isValidRoomStatus(const string& roomStatus) const {
        if (roomStatus.empty()) return false;
        for (int i = 0; i < roomStatus.size(); i++) {
            if (!isdigit(roomStatus[i])) return false;
        }
        int num = 0;
        for (int i = 0; i < roomStatus.size(); i++) {
            num = num * 10 + (roomStatus[i] - '0');
        }
        return num >= 0;
    }

    void addRoom(const string& roomNumber, const string& roomSeat, const string& roomStatus) {
        if (!isValidRoomNumber(roomNumber) || !isValidRoomSeat(roomSeat) || !isValidRoomStatus(roomStatus)) {
            cout << "Invalid Room format." << endl << endl;
            return;
        }

        Entry newRoom;
        newRoom.roomNumber = roomNumber;
        newRoom.roomSeat = roomSeat;
        newRoom.roomStatus = roomStatus;

        for (int i = 0; i < rooms.size(); i++) {
            if (rooms[i].roomNumber == roomNumber) {
                cout << "Room already exists." << endl << endl;
                return;
            }
        }

        rooms.push_back(newRoom);
        saveRooms();
        cout << "Room added successfully." << endl << endl;
        writeToLogFile("Added Room!\n");
        writeToLogFile("Room Number: " + roomNumber + "\n");
        writeToLogFile("Room Seat  : " + roomSeat + "\n");
        writeToLogFile("Room Status: " + roomStatus + "\n\n");
    }

    void deleteRoom(const string& roomNumber) {
        for (int i = 0; i < rooms.size(); i++) {
            if (rooms[i].roomNumber == roomNumber) {
                writeToLogFile("Deleted Room!\n");
                writeToLogFile("Room Number: " + rooms[i].roomNumber + "\n");
                writeToLogFile("Room Seat  : " + rooms[i].roomSeat + "\n");
                writeToLogFile("Room Status: " + rooms[i].roomStatus + "\n\n");
                rooms.erase(rooms.begin() + i);
                saveRooms();
                cout << "Room deleted successfully." << endl << endl;
                return;
            }
        }
        cout << "Room not found." << endl << endl;
    }

    void editRoom(const string& oldRoomNumber, const string& newRoomNumber, const string& newRoomSeat, const string& newRoomStatus) {
        if (!isValidRoomNumber(newRoomNumber) || !isValidRoomSeat(newRoomSeat) || !isValidRoomStatus(newRoomStatus)) {
            cout << "Invalid Room format." << endl << endl;
            return;
        }

        // Chấp nhận sửa đổi RoomNumber nếu trùng với oldRoomNumber
        for (int i = 0; i < rooms.size(); i++) {
            if (rooms[i].roomNumber == newRoomNumber && newRoomNumber != oldRoomNumber) {
                cout << "Room already exists." << endl << endl;
                return;
            }
        }

        for (int i = 0; i < rooms.size(); i++) {
            if (rooms[i].roomNumber == oldRoomNumber) {
                writeToLogFile("Edit Room!\n");
                writeToLogFile("Room Number: " + rooms[i].roomNumber + "\n");
                writeToLogFile("Room Seat  : " + rooms[i].roomSeat + "\n");
                writeToLogFile("Room Status: " + rooms[i].roomStatus + "\n");
                rooms[i].roomNumber = newRoomNumber; // Cho phép nhập lại chính số phòng
                rooms[i].roomSeat = newRoomSeat;
                rooms[i].roomStatus = newRoomStatus;

                saveRooms();
                cout << "Room edited successfully." << endl << endl;
                writeToLogFile("Edited Room!\n");
                writeToLogFile("Room Number: " + rooms[i].roomNumber + "\n");
                writeToLogFile("Room Seat  : " + rooms[i].roomSeat + "\n");
                writeToLogFile("Room Status: " + rooms[i].roomStatus + "\n\n");
                return;
            }
        }
        cout << "Room not found." << endl << endl;
    }

    void displayRooms() {
        if(rooms.empty()){
            cout << endl;
            return;
        }
        writeToLogFile("Displayed Room!\n");
        for (int i = 0; i < rooms.size(); i++) {
            display(rooms[i]);
        }
    }
    void clearRooms() {
        rooms.clear();
        ofstream file("Room.txt", ios::trunc);
        file.close();
        cout << "All Room cleared." << endl << endl;
        writeToLogFile("Cleared Room!\n\n");
    }

    void display(const Entry& room) const {
        cout << "Room Number: " << room.roomNumber << endl;
        cout << "Room Seat  : " << room.roomSeat << endl;
        cout << "Room Status: " << room.roomStatus << endl << endl;
        writeToLogFile("Room Number: " + room.roomNumber + "\n");
        writeToLogFile("Room Seat  : " + room.roomSeat + "\n");
        writeToLogFile("room Status: " + room.roomStatus + "\n\n");
    }
};
class Review {
private:
    struct Entry {
        string reviewTimeDate; // ReviewTimeDate
        string reviewStar;     // ReviewStar (1 to 5)
        string reviewFeedback; // ReviewFeedback
    };

    vector<Entry> reviews;

public:
    Review() {
        loadReviews();
    }

    void loadReviews() {
        ifstream file("Review.txt");
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            Entry entry;
            entry.reviewTimeDate = line.substr(line.find(":") + 2);
            getline(file, line);
            entry.reviewStar = line.substr(line.find(":") + 2);
            getline(file, line);
            entry.reviewFeedback = line.substr(line.find(":") + 2);
            reviews.push_back(entry);
        }
    }

    void saveReviews() {
        ofstream file("Review.txt");
        for (int i = 0; i < reviews.size(); i++) {
            file << "Review TimeDate: " << reviews[i].reviewTimeDate << endl;
            file << "Review Star    : " << reviews[i].reviewStar << endl;
            file << "Review Feedback: " << reviews[i].reviewFeedback << endl;
            file << endl; // Dòng trắng để dễ đọc
        }
    }

    void search(const string& input) {
        bool found = false;
        for (int i = 0; i < reviews.size(); i++) {
            if (reviews[i].reviewTimeDate == input || reviews[i].reviewStar == input || reviews[i].reviewFeedback == input) {
                writeToLogFile("Searched Review!\n");
                found = true;
                break;
            }
        }
        for (int i = 0; i < reviews.size(); i++) {
            if (reviews[i].reviewTimeDate == input || reviews[i].reviewStar == input || reviews[i].reviewFeedback == input) {
                display(reviews[i]);
                found = true;
            }
        }
        if (!found) {
            cout << "Review not found." << endl << endl;
        }
    }

    bool isValidTimeDate(const string& timeDate) const {
        if (timeDate.size() != 19 || timeDate[2] != ':' || timeDate[5] != ':' || timeDate[8] != '-' || timeDate[11] != '/') return false;

        // Check hh:mm:ss
        int hour = (timeDate[0] - '0') * 10 + (timeDate[1] - '0');
        int minute = (timeDate[3] - '0') * 10 + (timeDate[4] - '0');
        int second = (timeDate[6] - '0') * 10 + (timeDate[7] - '0');
        if (hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59) return false;

        // Check dd/mm/yyyy
        int day = (timeDate[9] - '0') * 10 + (timeDate[10] - '0');
        int month = (timeDate[12] - '0') * 10 + (timeDate[13] - '0');
        int year = (timeDate[15] - '0') * 1000 + (timeDate[16] - '0') * 100 + (timeDate[17] - '0') * 10 + (timeDate[18] - '0');

        if (year < 2024 || month < 1 || month > 12) return false;

        // Kiểm tra số ngày trong tháng
        int daysInMonth = 31;
        if (month == 2) {
            daysInMonth = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            daysInMonth = 30;
        }

        return day > 0 && day <= daysInMonth;
    }

    bool isValidStar(const string& star) const {
        return star.size() == 1 && star[0] >= '1' && star[0] <= '5';
    }

    void addReview(const string& timeDate, const string& star, const string& feedback) {
        if (!isValidTimeDate(timeDate) || !isValidStar(star)) {
            cout << "Invalid Review format." << endl << endl;
            return;
        }

        // Kiểm tra xem ReviewTimeDate đã tồn tại chưa
        for (int i = 0; i < reviews.size(); i++) {
            if (reviews[i].reviewTimeDate == timeDate) {
                cout << "Review already exists." << endl << endl;
                return;
            }
        }

        Entry newReview;
        newReview.reviewTimeDate = timeDate;
        newReview.reviewStar = star;
        newReview.reviewFeedback = feedback;

        reviews.push_back(newReview);
        saveReviews();
        cout << "Review added successfully." << endl << endl;
        writeToLogFile("Added Review!\n");
        writeToLogFile("Review TimeDate: " + timeDate + "\n");
        writeToLogFile("Review Star    : " + star + "\n");
        writeToLogFile("Review Feedback: " + feedback + "\n\n");
    }

    void deleteReview(const string& timeDate) {
        for (int i = 0; i < reviews.size(); i++) {
            if (reviews[i].reviewTimeDate == timeDate) {
                writeToLogFile("Deleted Review!\n");
                writeToLogFile("Review TimeDate: " + reviews[i].reviewTimeDate + "\n");
                writeToLogFile("review Star    : " + reviews[i].reviewStar + "\n");
                writeToLogFile("Review Feedback: " + reviews[i].reviewFeedback + "\n\n");
                reviews.erase(reviews.begin() + i);
                saveReviews();
                cout << "Review deleted successfully." << endl << endl;
                return;
            }
        }
        cout << "Review not found." << endl << endl;
    }

    void editReview(const string& oldTimeDate, const string& newTimeDate, const string& newStar, const string& newFeedback) {
        if (!isValidTimeDate(newTimeDate) || !isValidStar(newStar)) {
            cout << "Invalid Review format." << endl << endl;
            return;
        }

        // Kiểm tra nếu mới và cũ trùng nhau
        if (oldTimeDate == newTimeDate) {
            for (int i = 0; i < reviews.size(); i++) {
                if (reviews[i].reviewTimeDate == oldTimeDate) {
                    reviews[i].reviewStar = newStar;
                    reviews[i].reviewFeedback = newFeedback;

                    saveReviews();
                    cout << "Review edited successfully." << endl << endl;
                    return;
                }
            }
            cout << "Review not found." << endl << endl;
            return;
        }

        // Nếu sửa đổi thành một thời gian đã tồn tại khác
        for (int i = 0; i < reviews.size(); i++) {
            if (reviews[i].reviewTimeDate == newTimeDate) {
                cout << "Review already exists." << endl << endl;
                return;
            }
        }

        for (int i = 0; i < reviews.size(); i++) {
            if (reviews[i].reviewTimeDate == oldTimeDate) {
                writeToLogFile("Edit Review!\n");
                writeToLogFile("Review TimeDate: " + reviews[i].reviewTimeDate + "\n");
                writeToLogFile("Review Star    : " + reviews[i].reviewStar + "\n");
                writeToLogFile("Review Feedback: " + reviews[i].reviewFeedback +"\n");
                reviews[i].reviewTimeDate = newTimeDate; // Cho phép nhập lại chính thời gian
                reviews[i].reviewStar = newStar;
                reviews[i].reviewFeedback = newFeedback;

                saveReviews();
                cout << "Review edited successfully." << endl << endl;
                writeToLogFile("Edited Review!\n");
                writeToLogFile("Review TimeDate: " + reviews[i].reviewTimeDate + "\n");
                writeToLogFile("Review Star    : " + reviews[i].reviewStar + "\n");
                writeToLogFile("Review Feedback: " + reviews[i].reviewFeedback +"\n\n");
                return;
            }
        }
        cout << "Review not found." << endl << endl;
    }

    void displayReviews() {
        if(reviews.empty()){
            cout << endl;
            return;
        }
        writeToLogFile("Displayed Review!\n");
        for (int i = 0; i < reviews.size(); i++) {
            display(reviews[i]);
        }
    }
    
    void clearReviews() {
        reviews.clear();
        ofstream file("Review.txt", ios::trunc);
        file.close();
        cout << "All Review cleared." << endl << endl;
        writeToLogFile("Cleared Review!\n\n");
    }

    void display(const Entry& review) const {
        cout << "Review TimeDate: " << review.reviewTimeDate << endl;
        cout << "Review Star    : " << review.reviewStar << endl;
        cout << "Review Feedback: " << review.reviewFeedback << endl << endl;
        writeToLogFile("Review TimeDate: " + review.reviewTimeDate + "\n");
        writeToLogFile("Review Star    : " + review.reviewStar + "\n");
        writeToLogFile("Review Feedback: " + review.reviewFeedback + "\n\n");
    }
};
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
                writeToLogFile("Searched Staff!\n");
                found = true;
                break;
            }
        }
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
        writeToLogFile("Added Staff!\n");
        writeToLogFile("Staff ID    : " + staffID + "\n");
        writeToLogFile("Staff Name  : " + staffName + "\n");
        writeToLogFile("Staff Salary: " + staffSalary + "\n\n");
    }

    void deleteStaff(const string& staffID) {
        for (int i = 0; i < staffMembers.size(); i++) {
            if (staffMembers[i].staffID == staffID) {
                writeToLogFile("Deleted Staff!\n");
                writeToLogFile("Staff ID    : " + staffMembers[i].staffID + "\n");
                writeToLogFile("Staff Name  : " + staffMembers[i].staffName + "\n");
                writeToLogFile("Staff Salary: " + staffMembers[i].staffSalary + "\n\n");
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
                writeToLogFile("Staff ID    : " + staffMembers[i].staffID + "\n");
                writeToLogFile("Staff Name  : " + staffMembers[i].staffName + "\n");
                writeToLogFile("Staff Salary: " + staffMembers[i].staffSalary + "\n");
                staffMembers[i].staffID = newStaffID; // Cho phép nhập lại chính StaffID
                staffMembers[i].staffName = newStaffName;
                staffMembers[i].staffSalary = newStaffSalary;

                saveStaff();
                cout << "Staff edited successfully." << endl << endl;
                writeToLogFile("Staff ID    : " + staffMembers[i].staffID + "\n");
                writeToLogFile("Staff Name  : " + staffMembers[i].staffName + "\n");
                writeToLogFile("Staff Salary: " + staffMembers[i].staffSalary + "\n\n");
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
        writeToLogFile("Displayed Staff!\n");
        for (int i = 0; i < staffMembers.size(); i++) {
            display(staffMembers[i]);
        }
    }
    void clearStaff() {
        staffMembers.clear();
        ofstream file("Staff.txt", ios::trunc);
        file.close();
        cout << "All Staff cleared." << endl << endl;
        writeToLogFile("Cleared Staff!\n\n");
    }

    void display(const Entry& staff) const {
        cout << "Staff ID    : " << staff.staffID << endl;
        cout << "Staff Name  : " << staff.staffName << endl;
        cout << "Staff Salary: " << staff.staffSalary << endl << endl;
        writeToLogFile("Staff ID    : " + staff.staffID + "\n");
        writeToLogFile("Staff Name  : " + staff.staffName + "\n");
        writeToLogFile("Staff Salary: " + staff.staffSalary + "\n\n");
    }
};
class Service {
private:
    struct Entry {
        string serviceName;     // ServiceName (đối tượng tham chiếu)
        string serviceProvider;  // ServiceProvider
        string servicePrice;     // ServicePrice
    };

    vector<Entry> services;

public:
    Service() {
        loadServices();
    }

    void loadServices() {
        ifstream file("Service.txt");
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            Entry entry;
            entry.serviceName = line.substr(line.find(":") + 2);
            getline(file, line);
            entry.serviceProvider = line.substr(line.find(":") + 2);
            getline(file, line);
            entry.servicePrice = line.substr(line.find(":") + 2);
            services.push_back(entry);
        }
    }

    void saveServices() {
        ofstream file("Service.txt");
        for (int i = 0; i < services.size(); i++) {
            file << "Service Name    : " << services[i].serviceName << endl;
            file << "Service Provider: " << services[i].serviceProvider << endl;
            file << "Service Price   : " << services[i].servicePrice << endl;
            file << endl; // Dòng trắng để dễ đọc
        }
    }

    void search(const string& input) {
        bool found = false;
        for (int i = 0; i < services.size(); i++) {
            if (services[i].serviceName == input || services[i].serviceProvider == input || services[i].servicePrice == input) {
                writeToLogFile("Searched Service!\n");
                found = true;
                break;
            }
        }
        for (int i = 0; i < services.size(); i++) {
            if (services[i].serviceName == input || services[i].serviceProvider == input || services[i].servicePrice == input) {
                display(services[i]);
                found = true;
            }
        }
        if (!found) {
            cout << "Service not found." << endl << endl;
        }
    }

    bool isValidServicePrice(const string& servicePrice) const {
        if (servicePrice.empty()) return false;
        for (int i = 0; i < servicePrice.size(); i++) {
            if (!isdigit(servicePrice[i])) return false;
        }
        return true;
    }

    void addService(const string& serviceName, const string& serviceProvider, const string& servicePrice) {
        if (serviceName.empty() || !isValidServicePrice(servicePrice)) {
            cout << "Invalid Service format." << endl << endl;
            return;
        }

        Entry newService;
        newService.serviceName = serviceName;
        newService.serviceProvider = serviceProvider;
        newService.servicePrice = servicePrice;

        for (int i = 0; i < services.size(); i++) {
            if (services[i].serviceName == serviceName) {
                cout << "Service already exists." << endl << endl;
                return;
            }
        }

        services.push_back(newService);
        saveServices();
        cout << "Service added successfully." << endl << endl;
        writeToLogFile("Added Service!\n");
        writeToLogFile("Service Name    : " + serviceName + "\n");
        writeToLogFile("Service Provider: " + serviceProvider + "\n");
        writeToLogFile("Service Price   : " + servicePrice + "\n\n");
    }

    void deleteService(const string& serviceName) {
        for (int i = 0; i < services.size(); i++) {
            if (services[i].serviceName == serviceName) {
                writeToLogFile("Deleted Service!\n");
                writeToLogFile("Service Name    : " + services[i].serviceName + "\n");
                writeToLogFile("Service Provider: " + services[i].serviceProvider + "\n");
                writeToLogFile("Service Price   : " + services[i].servicePrice + "\n\n");
                services.erase(services.begin() + i);
                saveServices();
                cout << "Service deleted successfully." << endl << endl;
                return;
            }
        }
        cout << "Service not found." << endl << endl;
    }

    void editService(const string& oldServiceName, const string& newServiceName, const string& newServiceProvider, const string& newServicePrice) {
        if (newServiceName.empty() || !isValidServicePrice(newServicePrice)) {
            cout << "Invalid Service format." << endl << endl;
            return;
        }

        // Chấp nhận sửa đổi ServiceName nếu trùng với oldServiceName
        for (int i = 0; i < services.size(); i++) {
            if (services[i].serviceName == newServiceName && newServiceName != oldServiceName) {
                cout << "Service already exists." << endl << endl;
                return;
            }
        }

        for (int i = 0; i < services.size(); i++) {
            if (services[i].serviceName == oldServiceName) {
                writeToLogFile("Edit Service!\n");
                writeToLogFile("Service Name    : " + services[i].serviceName + "\n");
                writeToLogFile("Service Provider: " + services[i].serviceProvider + "\n");
                writeToLogFile("Service Price   : " + services[i].servicePrice + "\n");
                services[i].serviceName = newServiceName; // Cho phép nhập lại chính ServiceName
                services[i].serviceProvider = newServiceProvider;
                services[i].servicePrice = newServicePrice;

                saveServices();
                cout << "Service edited successfully." << endl << endl;
                writeToLogFile("Edited Service!\n");
                writeToLogFile("Service Name    : " + services[i].serviceName + "\n");
                writeToLogFile("Service Provider: " + services[i].serviceProvider + "\n");
                writeToLogFile("Service Price   : " + services[i].servicePrice + "\n\n");
                return;
            }
        }
        cout << "Service not found." << endl << endl;
    }

    void displayServices() {
        if(services.empty()){
            cout << endl;
            return;
        }
        writeToLogFile("Displayed Service!\n");
        for (int i = 0; i < services.size(); i++) {
            display(services[i]);
        }
    }
    void clearServices() {
        services.clear();
        ofstream file("Service.txt", ios::trunc);
        file.close();
        cout << "All Service cleared." << endl << endl;
        writeToLogFile("Cleared Service!\n\n");
    }

    void display(const Entry& service) const {
        cout << "Service Name    : " << service.serviceName << endl;
        cout << "Service Provider: " << service.serviceProvider << endl;
        cout << "Service Price   : " << service.servicePrice << endl << endl;
        writeToLogFile("Service Name    : " + service.serviceName + "\n");
        writeToLogFile("Service Provider: " + service.serviceProvider + "\n");
        writeToLogFile("Service Price   : " + service.servicePrice + "\n\n");
    }
};
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
                writeToLogFile("Searched Expense!\n");
                found = true;
                break;
            }
        }
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
        writeToLogFile("Added Expense!\n");
        writeToLogFile("Expense Date  : " + expenseDate + "\n");
        writeToLogFile("Expense Amount: " + expenseAmount + "\n");
        writeToLogFile("Expense Detail: " + expenseDetail + "\n\n");
    }

    void deleteExpense(const string& expenseDate) {
        for (int i = 0; i < expenses.size(); i++) {
            if (expenses[i].expenseDate == expenseDate) {
                writeToLogFile("Deleted Expense!\n");
                writeToLogFile("Expense Date  : " + expenses[i].expenseDate + "\n");
                writeToLogFile("Expense Amount: " + expenses[i].expenseAmount + "\n");
                writeToLogFile("Expense Detail: " + expenses[i].expenseDetail + "\n\n");
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
                writeToLogFile("Edit Expense!\n");
                writeToLogFile("Expense Date  : " + expenses[i].expenseDate + "\n");
                writeToLogFile("Expense Amount: " + expenses[i].expenseAmount + "\n");
                writeToLogFile("Expense Detail: " + expenses[i].expenseDetail + "\n");
                expenses[i].expenseDate = newDate; // Cho phép nhập lại chính ngày
                expenses[i].expenseAmount = newAmount;
                expenses[i].expenseDetail = newDetail;

                saveExpenses();
                cout << "Expense edited successfully." << endl << endl;
                writeToLogFile("Edited Expense!\n");
                writeToLogFile("Expense Date  : " + expenses[i].expenseDate + "\n");
                writeToLogFile("Expense Amount: " + expenses[i].expenseAmount + "\n");
                writeToLogFile("Expense Detail: " + expenses[i].expenseDetail + "\n\n");
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
        writeToLogFile("Displayed Expense!\n");
        for (int i = 0; i < expenses.size(); i++) {
            display(expenses[i]);
        }
    }
    void clearExpenses() {
        expenses.clear();
        ofstream file("Expense.txt", ios::trunc);
        file.close();
        cout << "All Expense cleared." << endl << endl;
        writeToLogFile("Cleared Expense!\n\n");
    }

    void display(const Entry& expense) const {
        cout << "Expense Date  : " << expense.expenseDate << endl;
        cout << "Expense Amount: " << expense.expenseAmount << endl;
        cout << "Expense Detail: " << expense.expenseDetail << endl << endl;
        writeToLogFile("Expense Date  : " + expense.expenseDate + "\n");
        writeToLogFile("Expense Amount: " + expense.expenseAmount + "\n");
        writeToLogFile("Expense Detail: " + expense.expenseDetail + "\n\n");
    }
};
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
                writeToLogFile("Searched Revenue!\n");
                found = true;
                break;
            }
        }
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
        writeToLogFile("Added Revenue!\n");
        writeToLogFile("Revenue Date  : " + revenueDate + "\n");
        writeToLogFile("Revenue Amount: " + revenueAmount + "\n");
        writeToLogFile("Revenue Detail: " + revenueDetail + "\n\n");
    }

    void deleteRevenue(const string& revenueDate) {
        for (int i = 0; i < revenues.size(); i++) {
            if (revenues[i].revenueDate == revenueDate) {
                writeToLogFile("Deleted Revenue!\n");
                writeToLogFile("Revenue Date  : " + revenues[i].revenueDate + "\n");
                writeToLogFile("Revenue Amount: " + revenues[i].revenueAmount + "\n");
                writeToLogFile("Revenue Detail: " + revenues[i].revenueDetail + "\n\n");
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
                writeToLogFile("Edit Revenue!\n");
                writeToLogFile("Revenue Date  : " + revenues[i].revenueDate + "\n");
                writeToLogFile("Revenue Amount: " + revenues[i].revenueAmount + "\n");
                writeToLogFile("Revenue Detail: " + revenues[i].revenueDetail + "\n");
                revenues[i].revenueDate = newDate; // Cho phép nhập lại chính ngày
                revenues[i].revenueAmount = newAmount;
                revenues[i].revenueDetail = newDetail;

                saveRevenues();
                cout << "Revenue edited successfully." << endl << endl;
                writeToLogFile("Edited Revenue!\n");
                writeToLogFile("Revenue Date  : " + revenues[i].revenueDate + "\n");
                writeToLogFile("Revenue Amount: " + revenues[i].revenueAmount + "\n");
                writeToLogFile("Revenue Detail: " + revenues[i].revenueDetail + "\n\n");
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
        writeToLogFile("Displayed Revenue!\n");
        for (int i = 0; i < revenues.size(); i++) {
            display(revenues[i]);
        }
    }
    void clearRevenues() {
        revenues.clear();
        ofstream file("Revenue.txt", ios::trunc);
        file.close();
        cout << "All Revenue cleared." << endl << endl;
        writeToLogFile("Cleared Revenue!\n\n");
    }

    void display(const Entry& revenue) const {
        cout << "Revenue Date  : " << revenue.revenueDate << endl;
        cout << "Revenue Amount: " << revenue.revenueAmount << endl;
        cout << "Revenue Detail: " << revenue.revenueDetail << endl << endl;
        writeToLogFile("Revenue Date  : " + revenue.revenueDate + "\n");
        writeToLogFile("Revenue Amount: " + revenue.revenueAmount + "\n");
        writeToLogFile("Revenue Detail: " + revenue.revenueDetail + "\n\n");
    }
};

int main() {
    Customer customer;
    Ticket ticket;
    Schedule schedule;
    Event event;
    Room room;
    Review review;
    Staff staff;
    Service service;
    Expense expense;
    Revenue revenue;
    string choice;
    string customerphone, newcustomerphone, customername, customerage;
    string ticketcode, newticketcode, ticketdate, ticketprice;
    string schedulemovie, newschedulemovie, scheduletime, scheduledate;
    string eventname, neweventname, eventstartdate, eventenddate;
    string roomnumber, newroomnumber, roomseat, roomstatus;
    string reviewtimedate, newreviewtimedate, reviewstar, reviewfeedback;
    string staffid, newstaffid, staffname, staffsalary;
    string servicename, newservicename, serviceprovider, serviceprice;
    string expensedate, newexpensedate, expenseamount, expensedetail;
    string revenuedate, newrevenuedate, revenueamount, revenuedetail;
    do {
        cout << "Cinema Manager\n";
        cout << "Function: 1.Search, 2.Add, 3.Delete, 4.Edit, 5.Display, 6.Clear, 0.Exit(No category needed)\n";
        cout << "Category: a.Customer, b.Ticket, c.Schedule, d.Event, e.Room, f.Review, g.Staff, h.Service, i.Expense, j.Revenue\n";
        cout << "Select operation (Function-Category)             : ";
        getline(cin, choice);
        if (choice == "1-a") {
            cout << "Customer (Phone/Name/Age) to search              : ";
            getline(cin, customerphone);
            customer.search(customerphone);
        } else if (choice == "1-b") {
            cout << "Ticket (Code/Date/Price) to search               : ";
            getline(cin, ticketcode);
            ticket.search(ticketcode);
        } else if (choice == "1-c") {
            cout << "Schedule (Movie/Time/Date) to search             : ";
            getline(cin, schedulemovie);
            schedule.search(schedulemovie);
        } else if (choice == "1-d") {
            cout << "Event (Name/Startdate/Enddate) to search         : ";
            getline(cin, eventname);
            event.search(eventname);
        } else if (choice == "1-e") {
            cout << "Room (Number/Seat/Status) to search              : ";
            getline(cin, roomnumber);
            room.search(roomnumber);
        } else if (choice == "1-f") {
            cout << "Review (TimeDate/Star/Feedback) to search        : ";
            getline(cin, reviewtimedate);
            review.search(reviewtimedate);
        } else if (choice == "1-g") {
            cout << "Staff (ID/Name/Salary) to search                 : ";
            getline(cin, staffid);
            staff.search(staffid);
        } else if (choice == "1-h") {
            cout << "Service (Name/Provider/Price) to search          : ";
            getline(cin, servicename);
            event.search(servicename);
        } else if (choice == "1-i") {
            cout << "Expense (Date/Amount/Detail) to search           : ";
            getline(cin, expensedate);
            expense.search(expensedate);
        } else if (choice == "1-j") {
            cout << "Revenue (Date/Amount/Detail) to search           : ";
            getline(cin, revenuedate);
            revenue.search(revenuedate);
        } else if (choice == "2-a") {
            cout << "Customer Phone (0XXXXXXXXX) to add               : ";
            getline(cin, customerphone);
            cout << "Customer Name to add                             : ";
            getline(cin, customername);
            cout << "Customer Age (>=3) to add                        : ";
            getline(cin, customerage);
            customer.addCustomer(customerphone, customername, customerage);
        } else if (choice == "2-b") {
            cout << "Ticket Code (numbers, letters) to add            : ";
            getline(cin, ticketcode);
            cout << "Ticket Date (dd/mm/>=2024) to add                : ";
            getline(cin, ticketdate);
            cout << "Ticket Price (>=0) to add                        : ";
            getline(cin, ticketprice);
            ticket.addTicket(ticketcode, ticketdate, ticketprice);
        } else if (choice == "2-c") {
            cout << "Schedule Movie to add                            : ";
            getline(cin, schedulemovie);
            cout << "Schedule Time to add (hh:mm)                     : ";
            getline(cin, scheduletime);
            cout << "Schedule Date to add (dd/mm/>=2024)              : ";
            getline(cin, scheduledate);
            schedule.addSchedule(schedulemovie, scheduletime, scheduledate);
        } else if (choice == "2-d") {
            cout << "Event Name to add                                : ";
            getline(cin, eventname);
            cout << "Event Startdate to add (dd/mm/>=2024)            : ";
            getline(cin, eventstartdate);
            cout << "Event Enddate to add (dd/mm/>=2024)              : ";
            getline(cin, eventenddate);
            event.addEvent(eventname, eventstartdate, eventenddate);
        } else if (choice == "2-e") {
            cout << "Room Number (>=1) to add                         : ";
            getline(cin, roomnumber);
            cout << "Room Seat (>=0) to add                           : ";
            getline(cin, roomseat);
            cout << "Room Status (>=0) to add                         : ";
            getline(cin, roomstatus);
            room.addRoom(roomnumber, roomseat, roomstatus);
        } else if (choice == "2-f") {
            cout << "Review TimeDate (hh:mm:ss-dd/mm/>=2024) to add   : ";
            getline(cin, reviewtimedate);
            cout << "Review Star (1-5) to add                         : ";
            getline(cin, reviewstar);
            cout << "Review Feedback to add                           : ";
            getline(cin, reviewfeedback);
            review.addReview(reviewtimedate, reviewstar, reviewfeedback);
        } else if (choice == "2-g") {
            cout << "Staff ID (XXXXXXXXXXXX) to add                   : ";
            getline(cin, staffid);
            cout << "Staff Name to add                                : ";
            getline(cin, staffname);
            cout << "Staff Salary (>=0) to add                        : ";
            getline(cin, staffsalary);
            staff.addStaff(staffid, staffname, staffsalary);
        } else if (choice == "2-h") {
            cout << "Service Name to add                              : ";
            getline(cin, servicename);
            cout << "Service Provider to add                          : ";
            getline(cin, serviceprovider);
            cout << "Service Price (>=0) to add                       : ";
            getline(cin, serviceprice);
            service.addService(servicename, serviceprovider, serviceprice);
        } else if (choice == "2-i") {
            cout << "Expense Date (dd/mm/>=2024) to add               : ";
            getline(cin, expensedate);
            cout << "Expense Amount (>=0) to add                      : ";
            getline(cin, expenseamount);
            cout << "Expense Detail to add                            : ";
            getline(cin, expensedetail);
            expense.addExpense(expensedate, expenseamount, expensedetail);
        } else if (choice == "2-j") {
            cout << "Revenue Date (dd/mm/>=2024) to add               : ";
            getline(cin, revenuedate);
            cout << "Revenue Amount (>=0) to add                      : ";
            getline(cin, revenueamount);
            cout << "Revenue Detail to add                            : ";
            getline(cin, revenuedetail);
            revenue.addRevenue(revenuedate, revenueamount, revenuedetail);
        } else if (choice == "3-a") {
            cout << "Customer Phone (0XXXXXXXXX) to delete            : ";
            getline(cin, customerphone);
            customer.deleteCustomer(customerphone);
        } else if (choice == "3-b") {
            cout << "Ticket Code (numbers, letters) to delete         : ";
            getline(cin, ticketcode);
            ticket.deleteTicket(ticketcode);
        } else if (choice == "3-c") {
            cout << "Schedule Movie to delete                         : ";
            getline(cin, schedulemovie);
            schedule.deleteSchedule(schedulemovie);
        } else if (choice == "3-d") {
            cout << "Event Name to delete                             : ";
            getline(cin, eventname);
            event.deleteEvent(eventname);
        } else if (choice == "3-e") {
            cout << "Room Number (>=1) to delete                      : ";
            getline(cin, roomnumber);
            room.deleteRoom(roomnumber);
        } else if (choice == "3-f") {
            cout << "Review TimeDate (hh:mm:ss-dd/mm/>=2024) to delete: ";
            getline(cin, reviewtimedate);
            review.deleteReview(reviewtimedate);
        } else if (choice == "3-g") {
            cout << "Staff ID (XXXXXXXXXXXX) to delete                : ";
            getline(cin, staffid);
            staff.deleteStaff(staffid);
        } else if (choice == "3-h") {
            cout << "Service Name to delete                           : ";
            getline(cin, servicename);
            service.deleteService(servicename);
        } else if (choice == "3-i") {
            cout << "Expense Date (dd/mm/>=2024) to delete            : ";
            getline(cin, expensedate);
            expense.deleteExpense(expensedate);
        } else if (choice == "3-j") {
            cout << "Revenue Date (dd/mm/>=2024) to delete            : ";
            getline(cin, revenuedate);
            revenue.deleteRevenue(revenuedate);
        } else if (choice == "4-a") {
            cout << "Customer Phone (0XXXXXXXXX) to edit              : ";
            getline(cin, customerphone);
            cout << "Customer Phone (0XXXXXXXXX) edited               : ";
            getline(cin, newcustomerphone);
            cout << "Customer Name edited                             : ";
            getline(cin, customername);
            cout << "Customer Age (>=3) edited                        : ";
            getline(cin, customerage);
            customer.editCustomer(customerphone, newcustomerphone, customername, customerage);
        } else if (choice == "4-b") {
            cout << "Ticket Code (numbers, letters) to edit           : ";
            getline(cin, ticketcode);
            cout << "Ticket Code (numbers, letters) edited            : ";
            getline(cin, newticketcode);
            cout << "Ticket Date (dd/mm/>=2024) edited                : ";
            getline(cin, ticketdate);
            cout << "Ticket Price (>=0) edited                        : ";
            getline(cin, ticketprice);
            ticket.editTicket(ticketcode, newticketcode, ticketdate, ticketprice);
        } else if (choice == "4-c") {
            cout << "Schedule Movie to edit                           : ";
            getline(cin, schedulemovie);
            cout << "Schedule Movie edited                            : ";
            getline(cin, newschedulemovie);
            cout << "Schedule Time edited (hh:mm)                     : ";
            getline(cin, scheduletime);
            cout << "Schedule Date edited (dd/mm/>=2024)              : ";
            getline(cin, scheduledate);
            schedule.editSchedule(schedulemovie, newschedulemovie, scheduletime, scheduledate);
        } else if (choice == "4-d") {
            cout << "Event Name to edit                               : ";
            getline(cin, eventname);
            cout << "Event Name edited                                : ";
            getline(cin, neweventname);
            cout << "Event Startdate edited (dd/mm/>=2024)            : ";
            getline(cin, eventstartdate);
            cout << "Event Enddate edited (dd/mm/>=2024)              : ";
            getline(cin, eventenddate);
            event.editEvent(eventname, neweventname, eventstartdate, eventenddate);
        } else if (choice == "4-e") {
            cout << "Room Number (>=1)to edit                         : ";
            getline(cin, roomnumber);
            cout << "Room Number (>=1) edited                         : ";
            getline(cin, newroomnumber);
            cout << "Room Seat (>=0) edited                           : ";
            getline(cin, roomseat);
            cout << "Room Status (>=0) edited                         : ";
            getline(cin, roomstatus);
            room.editRoom(roomnumber, newroomnumber, roomseat, roomstatus);
        } else if (choice == "4-f") {
            cout << "Review TimeDate (hh:mm:ss-dd/mm/>=2024) to edit  : ";
            getline(cin, reviewtimedate);
            cout << "Review TimeDate (hh:mm:ss-dd/mm/>=2024) edited   : ";
            getline(cin, newreviewtimedate);
            cout << "Review Star (1-5) edited                         : ";
            getline(cin, reviewstar);
            cout << "Review Feedback edited                           : ";
            getline(cin, reviewfeedback);
            review.editReview(reviewtimedate, newreviewtimedate, reviewstar, reviewfeedback);
        } else if (choice == "4-g") {
            cout << "Staff ID (XXXXXXXXXXXX) to edit                  : ";
            getline(cin, staffid);
            cout << "Staff ID (XXXXXXXXXXXX) edited                   : ";
            getline(cin, newstaffid);
            cout << "Staff Name edited                                : ";
            getline(cin, staffname);
            cout << "Staff Salary (>=0) edited                        : ";
            getline(cin, staffsalary);
            staff.editStaff(staffid, newstaffid, staffname, staffsalary);
        } else if (choice == "4-h") {
            cout << "Service Name to edit                             : ";
            getline(cin, servicename);
            cout << "Service Name edited                              : ";
            getline(cin, newservicename);
            cout << "Service Provider edited                          : ";
            getline(cin, serviceprovider);
            cout << "Service Price (>=0) edited                       : ";
            getline(cin, serviceprice);
            service.editService(servicename, newservicename, serviceprovider, serviceprice);
        } else if (choice == "4-i") {
            cout << "Expense Date (dd/mm/>=2024) to edit              : ";
            getline(cin, expensedate);
            cout << "Expense Date (dd/mm/>=2024) edited               : ";
            getline(cin, newexpensedate);
            cout << "Expense Amount (>=0) edited                      : ";
            getline(cin, expenseamount);
            cout << "Expense Detail edited                            : ";
            getline(cin, expensedetail);
            expense.editExpense(expensedate, newexpensedate, expenseamount, expensedetail);
        } else if (choice == "4-j") {
            cout << "Revenue Date (dd/mm/>=2024) to edit              : ";
            getline(cin, revenuedate);
            cout << "Revenue Date (dd/mm/>=2024) edited               : ";
            getline(cin, newrevenuedate);
            cout << "Revenue Amount (>=0) edited                      : ";
            getline(cin, revenueamount);
            cout << "Revenue Detail edited                            : ";
            getline(cin, revenuedetail);
            revenue.editRevenue(revenuedate, newrevenuedate, revenueamount, revenuedetail);
        } else if (choice == "5-a") {
            customer.displayCustomers();
        } else if (choice == "5-b") {
            ticket.displayTickets();
        } else if (choice == "5-c") {
            schedule.displaySchedules();
        } else if (choice == "5-d") {
            event.displayEvents();
        } else if (choice == "5-e") {
            room.displayRooms();
        } else if (choice == "5-f") {
            review.displayReviews();
        } else if (choice == "5-g") {
            staff.displayStaff();
        } else if (choice == "5-h") {
            service.displayServices();
        } else if (choice == "5-i") {
            expense.displayExpenses();
        } else if (choice == "5-j") {
            revenue.displayRevenues();
        } else if (choice == "6-a") {
            customer.clearCustomers();
        } else if (choice == "6-b") {
            ticket.clearTickets();
        } else if (choice == "6-c") {
            schedule.clearSchedules();
        } else if (choice == "6-d") {
            event.clearEvents();
        } else if (choice == "6-e") {
            room.clearRooms();
        } else if (choice == "6-f") {
            review.clearReviews();
        } else if (choice == "6-g") {
            staff.clearStaff();
        } else if (choice == "6-h") {
            service.clearServices();
        } else if (choice == "6-i") {
            expense.clearExpenses();
        } else if (choice == "6-j") {
            revenue.clearRevenues();
        } else if (choice != "0") {
            cout << "Invalid choice. Please try again." << endl << endl;
        }
    } while (choice != "0");

    cout << "Exiting..." << endl;

    return 0;
}
