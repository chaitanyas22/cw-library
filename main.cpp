#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

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

    BooksBorrowed(int bborrower, int bbkid)
        : borrower(bborrower), bbookid(bbkid) {}
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

    void issueBook() {
        int bborrower, bbkid;

        cout << "Enter the Book Id to be issued: ";
        cin >> bbkid;
        cout << "Enter the Member id to whom the book is issued: ";
        cin >> bborrower;

        borrowedBooks.emplace_back(bborrower, bbkid);
        cout << "Book issued to the member successfully.\n";
    }

    void displayBorrowedBooks() const {
        cout << "List of books issued to members:\n";
        for (const auto& borrowedBook : borrowedBooks) {
            cout << "Member ID: " << borrowedBook.borrower << "\nBook ID: " << borrowedBook.bbookid << "\n\n";
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
    // librarian.availableBooks = books;  // Removed this line as availableBooks is not used in the code

    int firstInput;

    cout << "Welcome to the Library management system \n";

    cout << "TO ISSUE BOOK = 1  ||  TO RETURN BOOK = 2 || TO ADD MEMBER = 3 \n";
    cin >> firstInput;

    if (firstInput == 1) {
        librarian.issueBook();
    } else if (firstInput == 2) {
       
    } else if (firstInput == 3) {
        librarian.addMember();
    }

    librarian.displayMembers();
    librarian.displayBorrowedBooks();

    return 0;
}
