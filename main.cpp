#include <iostream>
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

        // this function will call all the book id when called in the function

    void displayBook() const {
        cout << "Book Id: " << bookId << "\nBook Name: " << bookName
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
};

class Librarian {
public:
    int staffID;
    int salary;
    string name;
    string address;
    string email;
};


void processCSVData(const vector<Book>& books) {
    for (const auto& book : books) {
        book.displayBook();
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

    books.displayBooks();

     return 0;
}


