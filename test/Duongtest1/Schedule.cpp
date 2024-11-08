#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

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
    }

    void deleteSchedule(const string& movie) {
        for (int i = 0; i < schedules.size(); i++) {
            if (schedules[i].movie == movie) {
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

                schedules[i].movie = newMovie;
                schedules[i].scheduleTime = newScheduleTime;
                schedules[i].scheduleDate = newScheduleDate;

                saveSchedules();
                cout << "Schedule edited successfully." << endl << endl;
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
        for (int i = 0; i < schedules.size(); i++) {
            display(schedules[i]);
        }
    }
    void clearSchedules() {
        schedules.clear();
        ofstream file("Schedule.txt", ios::trunc);
        file.close();
        cout << "All Schedule cleared." << endl << endl;
    }

    void display(const Entry& schedule) const {
        cout << "Schedule Movie: " << schedule.movie << endl;
        cout << "Schedule Time : " << schedule.scheduleTime << endl;
        cout << "Schedule Date : " << schedule.scheduleDate << endl;
        cout << endl;
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

int main() {
    Schedule manager;
    string choice;
    string movie, newMovie, scheduleTime, scheduleDate;

    do {
        cout << "Schedule Manager\n";
        cout << "1. Search Schedule\n2. Add Schedule\n3. Delete Schedule\n4. Edit Schedule\n5. Display Schedule\n6. Clear Schedule\n7. Exit\n";
        cout << "Select operation                    : ";
        getline(cin, choice);

        if (choice == "1") {
            cout << "Schedule (Movie/Time/Date) to search: ";
            getline(cin, movie);
            manager.search(movie);
        } else if (choice == "2") {
            cout << "Schedule Movie to add               : ";
            getline(cin, movie);
            cout << "Schedule Time to add (hh:mm)        : ";
            getline(cin, scheduleTime);
            cout << "Schedule Date to add (dd/mm/>=2024) : ";
            getline(cin, scheduleDate);
            manager.addSchedule(movie, scheduleTime, scheduleDate);
        } else if (choice == "3") {
            cout << "Schedule Movie to delete            : ";
            getline(cin, movie);
            manager.deleteSchedule(movie);
        } else if (choice == "4") {
            cout << "Schedule Movie to edit              : ";
            getline(cin, movie);
            cout << "Schedule Movie edited               : ";
            getline(cin, newMovie);
            cout << "Schedule Time edited (hh:mm)        : ";
            getline(cin, scheduleTime);
            cout << "Schedule Date edited (dd/mm/>=2024) : ";
            getline(cin, scheduleDate);
            manager.editSchedule(movie, newMovie, scheduleTime, scheduleDate);
        } else if (choice == "5") {
            manager.displaySchedules();
        } else if (choice == "6") {
            manager.clearSchedules();
        } else if (choice != "7") {
            cout << "Invalid choice. Please try again." << endl << endl;
        }
    } while (choice != "7");

    cout << "Exiting..." << endl;

    return 0;
}
