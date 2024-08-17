#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
using namespace std;

// Book class
class Book {
private:
    string title;
    string author;
    string publisher;
    string isbn;
    string year;
    string edition;
    string category;
    string description;
    bool available;

public:
    // Constructor
    Book(string t, string a, string p, string i, string y, string e, string c, string d) {
        title = t;
        author = a;
        publisher = p;
        isbn = i;
        year = y;
        edition = e;
        category = c;
        description = d;
        available = true;
    }

    // Getter functions
    string getTitle() { return title; }
    string getAuthor() { return author; }
    string getPublisher() { return publisher; }
    string getISBN() { return isbn; }
    string getYear() { return year; }
    string getEdition() { return edition; }
    string getCategory() { return category; }
    string getDescription() { return description; }
    bool isAvailable() { return available; }

    // Setter function
    void setAvailability(bool a) { available = a; }
};

// Member class
class Member {
private:
    string name;
    string email;
    string address;
    string phone;
    string password;
    int id;

public:
    // Constructor
    Member(string n, string e, string a, string p, string pwd, int i) {
        name = n;
        email = e;
        address = a;
        phone = p;
        password = pwd;
        id = i;
    }

    // Getter functions
    string getName() { return name; }
    string getEmail() { return email; }
    string getAddress() { return address; }
    string getPhone() { return phone; }
    string getPassword() { return password; }
    int getId() { return id; }
};

// Issued Book class
class IssuedBook {
private:
    Book* book;
    Member* member;
    string issueDate;
    string dueDate;
    bool returned;
public:
    // Constructor
    IssuedBook(Book* b, Member* m, string i, string d) {
        book = b;
        member = m;
        issueDate = i;
        dueDate = d;
        returned = false;
    }

    // Getter functions
    Book* getBook() { return book; }
    Member* getMember() { return member; }
    string getIssueDate() { return issueDate; }
    string getDueDate() { return dueDate; }
    bool isReturned() { return returned; }


    // Setter functions
    void setReturned(bool r) { returned = r; }

};

// Library class
class Library {
private:
    vector<Book*> books;
    vector<Member*> members;
    vector<IssuedBook*> issuedBooks;
    int nextBookId;
    int nextMemberId;
    int nextIssuedBookId;
    string adminUsername;
    string adminPassword;
public:
    // Constructor
    Library(string u, string p) {
        adminUsername = u;
        adminPassword = p;
        nextBookId = 1;
        nextMemberId = 1;
        nextIssuedBookId = 1;
    }

    // Book functions
    void addBook(string t, string a, string p, string i, string y, string e, string c, string d) {
        Book* b = new Book(t, a, p, i, y, e, c, d);
        b->setAvailability(true);
        books.push_back(b);
        nextBookId++;
    }

    void removeBook(string isbn) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i]->getISBN() == isbn) {
                // Remove book from issued books
                for (int j = 0; j < issuedBooks.size(); j++) {
                    if (issuedBooks[j]->getBook() == books[i]) {
                        issuedBooks.erase(issuedBooks.begin() + j);
                        j--;
                    }
                }

                // Remove book from library
                books.erase(books.begin() + i);
                i--;
            }
        }
    }

    Book* searchBook(string isbn) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i]->getISBN() == isbn) {
                return books[i];
            }
        }
        return nullptr;
    }

    vector<Book*> searchBooks(string query) {
        vector<Book*> result;
        for (int i = 0; i < books.size(); i++) {
            Book* b = books[i];
            if (b->getTitle().find(query) != string::npos ||
                b->getAuthor().find(query) != string::npos ||
                b->getPublisher().find(query) != string::npos ||
                b->getCategory().find(query) != string::npos ||
                b->getISBN().find(query) != string::npos ||
                b->getDescription().find(query) != string::npos) {
                result.push_back(b);
            }
        }
        return result;
    }
    // Member functions
    void addMember(string n, string e, string a, string p, string pwd,int id) {
        Member* m = new Member(n, e, a, p, pwd, id);
        members.push_back(m);
        nextMemberId++;
    }

    void removeMember(int id) {
        for (int i = 0; i < members.size(); i++) {
            if (members[i]->getId() == id) {
                // Remove member from issued books
                for (int j = 0; j < issuedBooks.size(); j++) {
                    if (issuedBooks[j]->getMember() == members[i]) {
                        issuedBooks.erase(issuedBooks.begin() + j);
                        j--;
                    }
                }

                // Remove member from library
                members.erase(members.begin() + i);
                i--;
            }
        }
    }

    Member* searchMember(string email) {
        for (int i = 0; i < members.size(); i++) {
            if (members[i]->getEmail() == email) {
                return members[i];
            }
        }
        return nullptr;
    }

    // Issued Book functions
    IssuedBook* issueBook(Book* b, Member* m, string d) {
        if (b->isAvailable()) {
            b->setAvailability(false);
            string dueDate = calculateDueDate(d);
            IssuedBook* ib = new IssuedBook(b, m, d, dueDate);
            issuedBooks.push_back(ib);
            nextIssuedBookId++;
            return ib;
        }
        return nullptr;
    }

    void returnBook(IssuedBook* ib, string d) {
        ib->setReturned(true);
        ib->getBook()->setAvailability(true);
    }

    IssuedBook* searchIssuedBook(string isbn, int memberId) {
        for (int i = 0; i < issuedBooks.size(); i++) {
            if (issuedBooks[i]->getBook()->getISBN() == isbn && issuedBooks[i]->getMember()->getId() == memberId) {
                return issuedBooks[i];
            }
        }
        return nullptr;
    }

    vector<IssuedBook*> getIssuedBooks() {
        return issuedBooks;
    }

    vector<Book*> getBooks() const {
        return books;
    }

    vector<Member*> getMembers() const {
        return members;
    }

    // Login function
    bool login(string u, string p) {
        return (u == adminUsername && p == adminPassword);
    }

    // Helper functions
    string calculateDueDate(string d) {
        // Calculate due date as 14 days from issue date
        int year = stoi(d.substr(0, 4));
        int month = stoi(d.substr(5, 2));
        int day = stoi(d.substr(8, 2));
        day += 14;
        if (day > 30) {
            month++;
            day -= 30;
        }
        if (month > 12) {
            year++;
            month -= 12;
        }

        ostringstream os;
        os << setw(4) << setfill('0') << year << "-" << setw(2) << setfill('0') << month << "-" << setw(2) << setfill('0') << day;
        return os.str();
    }

    int calculateDaysOverdue(IssuedBook* ib, string d) {
        int year1 = stoi(ib->getDueDate().substr(0, 4));
        int month1 = stoi(ib->getDueDate().substr(5, 2));
        int day1 = stoi(ib->getDueDate().substr(8, 2));

        int year2 = stoi(d.substr(0, 4));
        int month2 = stoi(d.substr(5, 2));
        int day2 = stoi(d.substr(8, 2));

        int days1 = year1 * 365 + month1 * 30 + day1;
        int days2 = year2 * 365 + month2 * 30 + day2;

        return days2 - days1;
    }

    // Destructor
    ~Library() {
        for (int i = 0; i < books.size(); i++) {
            delete books[i];
        }
        for (int i = 0; i < members.size(); i++) {
            delete members[i];
        }
        for (int i = 0; i < issuedBooks.size(); i++) {
            delete issuedBooks[i];
        }
    }
};

void saveBooks(Library& lib) {
    ofstream file("books.txt");
    vector<Book*> books = lib.getBooks();
    for (Book* book : books) {
        file << book->getTitle() << '\t' << book->getAuthor() << '\t' << book->getPublisher() << '\t' << book->getISBN()
            << '\t' << book->getYear() << '\t' << book->getEdition() << '\t' << book->getCategory() << '\t'
            << book->getDescription() << '\t' << book->isAvailable() << endl;
    }
    file.close();
}

void loadBooks(Library& lib) {
    ifstream file("books.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string title, author, publisher, isbn, year, edition, category, description, isAvailableStr;
        getline(ss, title, '\t');
        getline(ss, author, '\t');
        getline(ss, publisher, '\t');
        getline(ss, isbn, '\t');
        getline(ss, year, '\t');
        getline(ss, edition, '\t');
        getline(ss, category, '\t');
        getline(ss, description, '\t');
        getline(ss, isAvailableStr, '\t');
        bool isAvailable = stoi(isAvailableStr);
        lib.addBook(title, author, publisher, isbn, year, edition, category, description);
    }
    file.close();
}

void saveMembers(Library& lib) {
    ofstream file("members.txt");
    vector<Member*> members = lib.getMembers();
    for (Member* member : members) {
        file << member->getName() << '\t' << member->getId() << '\t' << member->getEmail() << '\t' << member->getAddress() << '\t'
            << member->getPhone() << '\t' << member->getPassword() << endl;
    }
    file.close();
}

void loadMembers(Library& lib) {
    ifstream file("members.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, email, address, phone, password;
        int ID=0;
        getline(ss, name, '\t');
        getline(ss, email, '\t');
        getline(ss, address, '\t');
        getline(ss, phone, '\t');
        getline(ss, password, '\t');
        lib.addMember(name, email, address, phone, password,ID);
    }
    file.close();
}

int main() {
    // Create library object
    Library lib("Admin", "admin1234");
    loadBooks(lib);
    loadMembers(lib);
    //// Add some books to the library
    //lib.addBook("Harry Potter", "J.K Rowling", "fScribner", "100", 1997, 1, "Fantasy", "A fantasy novel about the magic.");
    //lib.addBook("Rich Dad Poor Dad", "Robert Kiyosaki", "Plata Publishing", "101", 1998, 1, "Financial", "A book about managing finances.");
    //lib.addBook("The Kite Runner", "Khalid Hosseni", "Riverhead Books", "102", 2003, 1, "Novel Drama", "Amazing story about boy.");

    //// Add some members to the library
    //lib.addMember("Huzkail", "hux@gmail.com", "123 Street 2, Clifton, Karachi", "555-1234", "password");
    //lib.addMember("Muhammad Ali", "mali@gmail.com", "456 Street 5, Defence, Hyderabad", "555-5678", "password");

    // Login as admin
    cout << "Welcome to the Library Management System\n";
    cout << "Please log in as admin:\n";
    string username, password;
    cout << "Username: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);
    if (lib.login(username, password)) {
        cout << "Login successful!\n";

        // Display menu
        int choice;
        do {
            cout << "\nMenu:\n";
            cout << "1. Add book\n";
            cout << "2. Remove book\n";
            cout << "3. Search book\n";
            cout << "4. Add member\n";
            cout << "5. Remove member\n";
            cout << "6. Search member\n";
            cout << "7. Issue book\n";
            cout << "8. Return book\n";
            cout << "9. Search issued book\n";
            cout << "10. View issued books\n";
            cout << "11. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore(); // Ignore newline character
            switch (choice) {
            case 1: {
                // Add book
                cout << "Enter book details:\n";
                string title, author, publisher, isbn, category, description;
                string year, edition;
                cout << "Title: ";
                getline(cin, title);
                cout << "Author: ";
                getline(cin, author);
                cout << "Publisher: ";
                getline(cin, publisher);
                cout << "ISBN: ";
                getline(cin, isbn);
                cout << "Year: ";
                cin >> year;
                cout << "Edition: ";
                cin >> edition;
                cin.ignore(); // Ignore newline character
                cout << "Category: ";
                getline(cin, category);
                cout << "Description: ";
                getline(cin, description);
                lib.addBook(title, author, publisher, isbn, year, edition, category, description);
                saveBooks(lib);
                cout << "Book added.\n";
                break;
            }
            case 2: {
                // Remove book
                cout << "Enter ISBN of book to remove: ";
                string isbn;
                getline(cin, isbn);
                lib.removeBook(isbn);
                cout << "Book removed.\n";
                break;
            }
            case 3: {
                // Search book
                cout << "Enter ISBN of book to search: ";
                string isbn;
                getline(cin, isbn);
                Book* b = lib.searchBook(isbn);
                if (b != nullptr) {
                    cout << "Title: " << b->getTitle() << endl;
                    cout << "Author: " << b->getAuthor() << endl;
                    cout << "Publisher: " << b->getPublisher() << endl;
                    cout << "ISBN: " << b->getISBN() << endl;
                    cout << "Year: " << b->getYear() << endl;
                    cout << "Edition: " << b->getEdition() << endl;
                    cout << "Category: " << b->getCategory() << endl;
                    cout << "Description: " << b->getDescription() << endl;
                    cout << "Availability: " << (b->isAvailable() ? "Available" : "Not available") << endl;
                }
                else {
                    cout << "Book not found.\n";
                }
                break;
            }
            case 4: {
                // Add member
                cout << "Enter member details:\n";
                string name, email, address, phone, password;
                int id;
                cout << "Name: ";
                getline(cin, name);
                cout << "ID: ";
                cin >> id;
                cin.ignore();
                cout << "Email: ";
                getline(cin, email);
                cout << "Address: ";
                getline(cin, address);
                cout << "Phone: ";
                getline(cin, phone);
                cout << "Password: ";
                getline(cin, password);
                lib.addMember(name, email, address, phone, password,id);
                saveMembers(lib);
                cout << "Member added.\n";
                break;
            }
            case 5: {
                // Remove member
                cout << "Enter ID of member to remove: ";
                int id;
                cin >> id;
                cin.ignore(); // Ignore newline character
                lib.removeMember(id);
                saveMembers(lib);
                cout << "Member removed.\n";
                break;
            }
            case 6: {
                // Search member
                cout << "Enter email of member to search: ";
                string email;
                getline(cin, email);
                Member* m = lib.searchMember(email);
                if (m != nullptr) {
                    cout << "Name: " << m->getName() << endl;
                    cout << "Email: " << m->getEmail() << endl;
                    cout << "Address: " << m->getAddress() << endl;
                    cout << "Phone: " << m->getPhone() << endl;
                    cout << "ID: " << m->getId() << endl;
                }
                else {
                    cout << "Member not found.\n";
                }
                break;
            }
            case 7: {
                // Issue book
                cout << "Enter details of book to issue:\n";
                string isbn, email, date;
                cout << "ISBN: ";
                getline(cin, isbn);
                cout << "Member email: ";
                getline(cin, email);
                cout << "Issue date (yyyy-mm-dd): ";
                getline(cin, date);
                Book* b = lib.searchBook(isbn);
                Member* m = lib.searchMember(email);
                if (b != nullptr && m != nullptr) {
                    IssuedBook* ib = lib.issueBook(b, m, date);
                    if (ib != nullptr) {
                        cout << "Book issued.\n";
                    }
                    else {
                        cout << "Book not available.\n";
                    }
                }
                else {
                    cout << "Book or member not found.\n";
                }
                break;
            }
            case 8: {
                // Return book
                cout << "Enter details of book to return:\n";
                string isbn, email, date;
                cout << "ISBN: ";
                getline(cin, isbn);
                cout << "Member email: ";
                getline(cin, email);
                cout << "Return date (yyyy-mm-dd): ";
                getline(cin, date);
                IssuedBook* ib = lib.searchIssuedBook(isbn, lib.searchMember(email)->getId());
                if (ib != nullptr) {
                    lib.returnBook(ib, date);
                    cout << "Book returned.\n";
                }
                else {
                    cout << "Book not issued to that member.\n";
                }
                break;
            }
            case 9: {
                // Search issued book
                cout << "Enter details of issued book to search:\n";
                string isbn, email;
                cout << "ISBN: ";
                getline(cin, isbn);
                cout << "Member email: ";
                getline(cin, email);
                IssuedBook* ib = lib.searchIssuedBook(isbn, lib.searchMember(email)->getId());
                if (ib != nullptr) {
                    cout << "Book title: " << ib->getBook()->getTitle() << endl;
                    cout << "Member name: " << ib->getMember()->getName() << endl;
                    cout << "Issue date: " << ib->getIssueDate() << endl;
                    cout << "Due date: " << ib->getDueDate() << endl;
                    cout << "Returned: " << (ib->isReturned() ? "Yes" : "No") << endl;

                }
                else {
                    cout << "Issued book not found.\n";
                }
                break;
            }
            case 10: {
                // View issued books
                vector < IssuedBook*> ibs = lib.getIssuedBooks();
                if (ibs.empty()) {
                    cout << "No books currently issued.\n";
                }
                else {
                    cout << "Books currently issued:\n";
                    for (int i = 0; i < ibs.size(); i++) {
                        cout << "Book title: " << ibs[i]->getBook()->getTitle() << endl;
                        cout << "Member name: " << ibs[i]->getMember()->getName() << endl;
                        cout << "Issue date: " << ibs[i]->getIssueDate() << endl;
                        cout << "Due date: " << ibs[i]->getDueDate() << endl;
                        cout << "Returned: " << (ibs[i]->isReturned() ? "Yes" : "No") << endl;

                        cout << endl;
                    }
                }
                break;
            }
            case 11: {
                // Logout
                cout << "Logging out...\n";
                exit(0);
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
                break;
            }
            }
        } while (choice != 12);
    }
    else {
        cout << "Login failed. Exiting...\n";
    }
    return 0;
}