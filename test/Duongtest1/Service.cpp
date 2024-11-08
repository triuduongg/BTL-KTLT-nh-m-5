#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

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
    }

    void deleteService(const string& serviceName) {
        for (int i = 0; i < services.size(); i++) {
            if (services[i].serviceName == serviceName) {
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
                services[i].serviceName = newServiceName; // Cho phép nhập lại chính ServiceName
                services[i].serviceProvider = newServiceProvider;
                services[i].servicePrice = newServicePrice;

                saveServices();
                cout << "Service edited successfully." << endl << endl;
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
        for (int i = 0; i < services.size(); i++) {
            display(services[i]);
        }
    }
    void clearServices() {
        services.clear();
        ofstream file("Service.txt", ios::trunc);
        file.close();
        cout << "All Service cleared." << endl << endl;
    }

    void display(const Entry& service) const {
        cout << "Service Name    : " << service.serviceName << endl;
        cout << "Service Provider: " << service.serviceProvider << endl;
        cout << "Service Price   : " << service.servicePrice << endl;
        cout << endl;
    }
};

int main() {
    Service manager;
    string choice;
    string serviceName, newServiceName, serviceProvider, servicePrice;

    do {
        cout << "Service Manager\n";
        cout << "1. Search Service\n2. Add Service\n3. Delete Service\n4. Edit Service\n5. Display Services\n6. Clear Service\n7. Exit\n";
        cout << "Select operation                       : ";
        getline(cin, choice);

        if (choice == "1") {
            cout << "Service (Name/Provider/Price) to search: ";
            getline(cin, serviceName);
            manager.search(serviceName);
        } else if (choice == "2") {
            cout << "Service Name to add                    : ";
            getline(cin, serviceName);
            cout << "Service Provider to add                : ";
            getline(cin, serviceProvider);
            cout << "Service Price (>=0) to add             : ";
            getline(cin, servicePrice);
            manager.addService(serviceName, serviceProvider, servicePrice);
        } else if (choice == "3") {
            cout << "Service Name to delete                 : ";
            getline(cin, serviceName);
            manager.deleteService(serviceName);
        } else if (choice == "4") {
            cout << "Service Name to edit                   : ";
            getline(cin, serviceName);
            cout << "Service Name edited                    : ";
            getline(cin, newServiceName);
            cout << "Service Provider edited                : ";
            getline(cin, serviceProvider);
            cout << "Service Price (>=0) edited             : ";
            getline(cin, servicePrice);
            manager.editService(serviceName, newServiceName, serviceProvider, servicePrice);
        } else if (choice == "5") {
            manager.displayServices();
        } else if (choice == "6") {
            manager.clearServices();
        } else if (choice != "7") {
            cout << "Invalid choice. Please try again." << endl << endl;
        }
    } while (choice != "7");

    cout << "Exiting..." << endl;

    return 0;
}
