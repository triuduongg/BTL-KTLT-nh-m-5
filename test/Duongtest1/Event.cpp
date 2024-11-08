#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

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
    }

    void deleteEvent(const string& eventName) {
        for (int i = 0; i < events.size(); i++) {
            if (events[i].eventName == eventName) {
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

                Entry updatedEvent;
                updatedEvent.eventName = newEventName;
                updatedEvent.startDate = newStartDate;
                updatedEvent.endDate = newEndDate;
                events[i] = updatedEvent;

                saveEvents();
                cout << "Event edited successfully." << endl << endl;
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
        for (int i = 0; i < events.size(); i++) {
            display(events[i]);
        }
    }
    void clearEvents() {
        events.clear();
        ofstream file("Event.txt", ios::trunc);
        file.close();
        cout << "All Event cleared." << endl << endl;
    }

    void display(const Entry& event) const {
        cout << "Event Name     : " << event.eventName << endl;
        cout << "Event Startdate: " << event.startDate << endl;
        cout << "Event Enddate  : " << event.endDate << endl;
        cout << endl;
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

int main() {
    Event manager;
    string choice;
    string eventName, newEventName, startDate, endDate;

    do {
        cout << "Event Manager\n";
        cout << "1. Search Event\n2. Add Event\n3. Delete Event\n4. Edit Event\n5. Display Event\n6. Clear Event\n7. Exit\n";
        cout << "Select operation                        : ";
        getline(cin, choice);

        if (choice == "1") {
            cout << "Event (Name/Startdate/Enddate) to search: ";
            getline(cin, eventName);
            manager.search(eventName);
        } else if (choice == "2") {
            cout << "Event Name to add                       : ";
            getline(cin, eventName);
            cout << "Event Startdate to add (dd/mm/>=2024)   : ";
            getline(cin, startDate);
            cout << "Event Enddate to add (dd/mm/>=2024)     : ";
            getline(cin, endDate);
            manager.addEvent(eventName, startDate, endDate);
        } else if (choice == "3") {
            cout << "Event Name to delete                    : ";
            getline(cin, eventName);
            manager.deleteEvent(eventName);
        } else if (choice == "4") {
            cout << "Event Name to edit                      : ";
            getline(cin, eventName);
            cout << "Event Name edited                       : ";
            getline(cin, newEventName);
            cout << "Event Startdate edited (dd/mm/>=2024)   : ";
            getline(cin, startDate);
            cout << "Event Enddate edited (dd/mm/>=2024)     : ";
            getline(cin, endDate);
            manager.editEvent(eventName, newEventName, startDate, endDate);
        } else if (choice == "5") {
            manager.displayEvents();
        } else if (choice == "6") {
            manager.clearEvents();
        } else if (choice != "7") {
            cout << "Invalid choice. Please try again." << endl << endl;
        }
    } while (choice != "7");

    cout << "Exiting..." << endl;

    return 0;
}
