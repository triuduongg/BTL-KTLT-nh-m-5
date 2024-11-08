#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

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
    }

    void deleteReview(const string& timeDate) {
        for (int i = 0; i < reviews.size(); i++) {
            if (reviews[i].reviewTimeDate == timeDate) {
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
                reviews[i].reviewTimeDate = newTimeDate; // Cho phép nhập lại chính thời gian
                reviews[i].reviewStar = newStar;
                reviews[i].reviewFeedback = newFeedback;

                saveReviews();
                cout << "Review edited successfully." << endl << endl;
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
        for (int i = 0; i < reviews.size(); i++) {
            display(reviews[i]);
        }
    }
    
    void clearReviews() {
        reviews.clear();
        ofstream file("Review.txt", ios::trunc);
        file.close();
        cout << "All Review cleared." << endl << endl;
    }

    void display(const Entry& review) const {
        cout << "Review TimeDate: " << review.reviewTimeDate << endl;
        cout << "Review Star    : " << review.reviewStar << endl;
        cout << "Review Feedback: " << review.reviewFeedback << endl;
        cout << endl;
    }
};

int main() {
    Review manager;
    string choice;
    string timeDate, newTimeDate, star, feedback;

    do {
        cout << "Review Manager\n";
        cout << "1. Search Review\n2. Add Review\n3. Delete Review\n4. Edit Review\n5. Display Review\n6. Clear Review\n7. Exit\n";
        cout << "Select operation                                 : ";
        getline(cin, choice);

        if (choice == "1") {
            cout << "Review (TimeDate/Star/Feedback) to search        : ";
            getline(cin, timeDate);
            manager.search(timeDate);
        } else if (choice == "2") {
            cout << "Review TimeDate (hh:mm:ss-dd/mm/>=2024) to add   : ";
            getline(cin, timeDate);
            cout << "Review Star (1-5) to add                         : ";
            getline(cin, star);
            cout << "Review Feedback to add                           : ";
            getline(cin, feedback);
            manager.addReview(timeDate, star, feedback);
        } else if (choice == "3") {
            cout << "Review TimeDate (hh:mm:ss-dd/mm/>=2024) to delete: ";
            getline(cin, timeDate);
            manager.deleteReview(timeDate);
        } else if (choice == "4") {
            cout << "Review TimeDate (hh:mm:ss-dd/mm/>=2024) to edit  : ";
            getline(cin, timeDate);
            cout << "Review TimeDate (hh:mm:ss-dd/mm/>=2024) edited   : ";
            getline(cin, newTimeDate);
            cout << "Review Star (1-5) edited                         : ";
            getline(cin, star);
            cout << "Review Feedback edited                           : ";
            getline(cin, feedback);
            manager.editReview(timeDate, newTimeDate, star, feedback);
        } else if (choice == "5") {
            manager.displayReviews();
        } else if (choice == "6") {
            manager.clearReviews();
        } else if (choice != "7") {
            cout << "Invalid choice. Please try again." << endl << endl;
        }
    } while (choice != "7");

    cout << "Exiting..." << endl;

    return 0;
}

