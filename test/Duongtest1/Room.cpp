#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

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
    }

    void deleteRoom(const string& roomNumber) {
        for (int i = 0; i < rooms.size(); i++) {
            if (rooms[i].roomNumber == roomNumber) {
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
                rooms[i].roomNumber = newRoomNumber; // Cho phép nhập lại chính số phòng
                rooms[i].roomSeat = newRoomSeat;
                rooms[i].roomStatus = newRoomStatus;

                saveRooms();
                cout << "Room edited successfully." << endl << endl;
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
        for (int i = 0; i < rooms.size(); i++) {
            display(rooms[i]);
        }
    }
    void clearRooms() {
        rooms.clear();
        ofstream file("Room.txt", ios::trunc);
        file.close();
        cout << "All Room cleared." << endl << endl;
    }

    void display(const Entry& room) const {
        cout << "Room Number: " << room.roomNumber << endl;
        cout << "Room Seat  : " << room.roomSeat << endl;
        cout << "Room Status: " << room.roomStatus << endl;
        cout << endl;
    }
};

int main() {
    Room manager;
    string choice;
    string roomNumber, newRoomNumber, roomSeat, roomStatus;

    do {
        cout << "Room Manager\n";
        cout << "1. Search Room\n2. Add Room\n3. Delete Room\n4. Edit Room\n5. Display Rooms\n6. Clear Room\n7. Exit\n";
        cout << "Select operation                   : ";
        getline(cin, choice);

        if (choice == "1") {
            cout << "Room (Number/Seat/Status) to search: ";
            getline(cin, roomNumber);
            manager.search(roomNumber);
        } else if (choice == "2") {
            cout << "Room Number (>=1) to add           : ";
            getline(cin, roomNumber);
            cout << "Room Seat (>=0) to add             : ";
            getline(cin, roomSeat);
            cout << "Room Status (>=0) to add           : ";
            getline(cin, roomStatus);
            manager.addRoom(roomNumber, roomSeat, roomStatus);
        } else if (choice == "3") {
            cout << "Room Number (>=1) to delete        : ";
            getline(cin, roomNumber);
            manager.deleteRoom(roomNumber);
        } else if (choice == "4") {
            cout << "Room Number (>=1)to edit           : ";
            getline(cin, roomNumber);
            cout << "Room Number (>=1) edited           : ";
            getline(cin, newRoomNumber);
            cout << "Room Seat (>=0) edited             : ";
            getline(cin, roomSeat);
            cout << "Room Status (>=0) edited           : ";
            getline(cin, roomStatus);
            manager.editRoom(roomNumber, newRoomNumber, roomSeat, roomStatus);
        } else if (choice == "5") {
            manager.displayRooms();
        } else if (choice == "6") {
            manager.clearRooms();
        } else if (choice != "7") {
            cout << "Invalid choice. Please try again." << endl << endl;
        }
    } while (choice != "7");

    cout << "Exiting..." << endl;

    return 0;
}
