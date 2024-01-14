#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

class Book {
public:
    int bookId;
    string bookName;
    string authorFirstName;
    string authorLastName;
    string bookType;

    Book(int bkId, const string& bkName, const string& arFirstName, const string& arLastName, const string& bkType)
        : bookId(bkId), bookName(bkName), authorFirstName(arFirstName), authorLastName(arLastName), bookType(bkType) {}

    void displayInfo() const {
        cout << "Book ID: " << bookId << "\nBook Name: " << bookName
             << "\nAuthor First Name: " << authorFirstName << "\nAuthor Last Name: " << authorLastName
             << "\nBook Type: " << bookType << "\n\n";
    }
};

class Member {
public:
    int memberID;
    string name;
    string address;
    string email;

    Member(int memID, const string& memName, const string& memAddress, const string& memEmail)
        : memberID(memID), name(memName), address(memAddress), email(memEmail) {}
};






class BooksBorrowed {
public:
    int borrower;
    int bbookid;
    string dateOfIssuance;
    string dateDue;

    BooksBorrowed(int bborrower, int bbkid, const string& date)
        : borrower(bborrower), bbookid(bbkid), dateOfIssuance(date) {
        makeDueDate();
    }
    void makeDueDate() {
        // Extract day, month, and year from dateOfIssuance
        int day, month, year;
        sscanf(dateOfIssuance.c_str(), "%d-%d-%d", &day, &month, &year);

        // Calculate due date (3 days after issuance)
        day += 3;

        // Handle month and year overflow
        while (day > 31) {
            day -= 31;
            month += 1;
        }

        while (month > 12) {
            month -= 12;
            year += 1;
        }

        // Format dueDate as (DD-MM-YYYY)
        dateDue = to_string(day) + "-" + to_string(month) + "-" + to_string(year);
    }
};




class Librarian {
public:
    int staffID;
    int salary;
    string name;
    string address;
    string email;
    vector<Member> members;
    vector<BooksBorrowed> borrowedBooks;

    void setStaffId() {
        cout << "Set Librarian staff ID: ";
        cin >> staffID;
    }

    void getStaffId() const {
        cout << "Staff ID is: " << staffID << "\n";
    }

    void getSalary() const {
        cout << "Staff salary is: $" << salary << "\n";
    }

    void setSalary() {
        cout << "Enter the salary of the librarian: ";
        cin >> salary;
    }

    void issueBook(const vector<Book>& books) {
    int bborrower, bbkid, day, month, year;

    cout << "Enter the Book Id to be issued: ";
    cin >> bbkid;
    cout << "Enter the Member id to whom the book is issued: ";
    cin >> bborrower;

    // Get the date of issue
    cout << "Enter the date of issue (DD MM YYYY): ";
    cin >> day >> month >> year;

    // Validate the date
    if (day < 1 || day > 31 || month < 1 || month > 12) {
        cout << "Invalid date. Please enter a valid date.\n";
        return;
    }

    string dateOfIssuance = to_string(day) + "-" + to_string(month) + "-" + to_string(year);

    bool memberExists = false;
    for (const auto& member : members) {
        if (member.memberID == bborrower) {
            memberExists = true;
            break;
        }
    }

    bool bookFound = false;
    for (const auto& book : books) {
        if (book.bookId == bbkid) {
            bookFound = true;
            break;
        }
    }

    if (!bookFound) {
        cout << "Book with ID " << bbkid << " not found. Unable to issue the book.\n";
    } else {
        // Check if the book ID is already in borrowedBooks
        bool bookAlreadyIssued = false;
        for (const auto& borrowedBook : borrowedBooks) {
            if (borrowedBook.bbookid == bbkid) {
                bookAlreadyIssued = true;
                break;
            }
        }

        if (bookAlreadyIssued) {
            cout << "Book with ID " << bbkid << " is already issued. Book unavailable.\n";
        } else if (!memberExists) {
            cout << "Member does not exist.\n\n";
        } else {
            borrowedBooks.emplace_back(bborrower, bbkid, dateOfIssuance);
            cout << "Book issued to the member successfully on " << dateOfIssuance
                 << ". Due date is " << borrowedBooks.back().dateDue << ".\n";
        }
    }
}


    void returnBook() {
        int memberId, bookId, returnDay, returnMonth, returnYear;

        cout << "Enter Member ID to return the book: ";
        cin >> memberId;
        cout << "Enter Book ID to return: ";
        cin >> bookId;
        cout << "Enter the return date (DD-MM-YYYY): ";
        cin >> returnDay >> returnMonth >> returnYear;

        bool bookAlreadyIssued = false;
        size_t indexToRemove = 0;

        for (size_t i = 0; i < borrowedBooks.size(); ++i) {
            if (borrowedBooks[i].bbookid == bookId && borrowedBooks[i].borrower == memberId) {
                bookAlreadyIssued = true;
                indexToRemove = i;
                break;
            }
        }

        if (bookAlreadyIssued) {
            // Extract day, month, and year from dueDate
            int dueDay, dueMonth, dueYear;
            sscanf(borrowedBooks[indexToRemove].dateDue.c_str(), "%d-%d-%d", &dueDay, &dueMonth, &dueYear);

            // Calculate fine
            int fine = 0;
            if (returnYear > dueYear || (returnYear == dueYear && returnMonth > dueMonth) ||
                (returnYear == dueYear && returnMonth == dueMonth && returnDay > dueDay)) {
                fine = (returnYear - dueYear) * 365 + (returnMonth - dueMonth) * 30 + (returnDay - dueDay);
            }

            // Display fine
            if (fine > 0) {
                cout << "Member has recived a fine of : £" << fine << " for returning book "<< fine << " later than the due date" "\n";
            }

            // Remove book from borrowedBooks
            borrowedBooks.erase(borrowedBooks.begin() + indexToRemove);
            cout << "Book returned successfully.\n";
        } else {
            cout << "Book with ID " << bookId << " was not issued to Member ID " << memberId
                 << ". Unable to return the book.\n";
        }
    }

    void displayBorrowedBooks() const {
        cout << "List of books issued to members:\n";
        for (const auto& borrowedBook : borrowedBooks) {
            cout << "Member ID: " << borrowedBook.borrower << "\nBook ID: " << borrowedBook.bbookid
                 << "\nDate of Issue: " << borrowedBook.dateOfIssuance
                 << "\nDue Date: " << borrowedBook.dateDue << "\n\n";
        }
    }

    void addMember() {
        int memID;
        string memName, memAddress, memEmail;
        cout << "Enter Member ID: ";
        cin >> memID;
        cout << "Enter Member Name: ";
        cin.ignore();
        getline(cin, memName);
        cout << "Enter Member Address: ";
        getline(cin, memAddress);
        cout << "Enter Member Email: ";
        getline(cin, memEmail);

        members.emplace_back(memID, memName, memAddress, memEmail);
        cout << "Member added successfully.\n";
    }

    void displayMembers() const {
        cout << "List of Members:\n";
        for (const auto& member : members) {
            cout << "Member ID: " << member.memberID << "\nName: " << member.name
                 << "\nAddress: " << member.address << "\nEmail: " << member.email << "\n\n";
        }
    }
};

void processCSVData(const vector<Book>& books) {
    for (const auto& book : books) {
        book.displayInfo();
    }
}

int main() {
    ifstream file("library_books.csv");

    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    vector<Book> books;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);

        int bookId;
        string bookName, authorFirstName, authorLastName, bookType;

        if (ss >> bookId >> bookName >> authorFirstName >> authorLastName >> bookType) {
            books.emplace_back(bookId, bookName, authorFirstName, authorLastName, bookType);
        }
    }

    file.close();

    Librarian librarian;

    cout << "Initializing! Please set values \n";

    librarian.setStaffId();
    cout << "Staff name: ";
    cin >> librarian.name;
    cout << "Address: ";
    cin >> librarian.address;
    cout << "Email: ";
    cin >> librarian.email;
    librarian.setSalary();

    cout << "Welcome to the Library management system \n\n";

    int firstInput;

    // Infinite loop for menu options
    while (true) {
        cout << "TO ISSUE BOOK = 1  ||  TO RETURN BOOK = 2 || TO ADD MEMBER = 3 || EXIT = 0 \n\n";
        cin >> firstInput;

        switch (firstInput) {
            case 1:
                librarian.issueBook(books);
                break;
            case 2:
                librarian.returnBook();
                break;
            case 3:
                librarian.addMember();
                break;

            case 0:
                cout << "Exiting the Library management system.\n";
                return 0;
            default:
                cout << "Invalid input. Please try again.\n";
        }

        librarian.displayMembers();
        librarian.displayBorrowedBooks();
    }

    return 0;
}
