# Library-Management-System

This is a console-based Library Management System written in C++. The system allows administrators to manage books, members, and issued books within a library. The system includes functionalities for adding, removing, searching, and issuing books, as well as managing members and their borrowing records.

## Features

### Book Management

* **Add Book**: Administrators can add new books to the library by providing details such as title, author, publisher, ISBN, year, edition, category, and description.
* **Remove Book**: Books can be removed from the library using their ISBN.
* **Search Book**: Search for a book using its ISBN or any keyword related to the title, author, publisher, category, or description.

### Member Management

* **Add Member**: New members can be added to the library by entering their name, ID, email, address, phone number, and password.
* **Remove Member**: Members can be removed from the library using their ID.
* **Search Member**: Search for a member using their email address.

### Issued Book Management

* **Issue Book**: Books can be issued to members, with the system automatically calculating the due date (14 days from the issue date).
* **Return Book**: Members can return issued books, updating the book's availability status.
* **Search Issued Book**: Search for issued books by ISBN and member ID.
* **View Issued Books**: View all currently issued books and their details.

### Administrator Login

* **Login**: The system requires an administrator to log in using a username and password before accessing any management functions.

### Data Persistence

* **Save/Load Data**: The system saves the library's books and members to text files (`books.txt` and `members.txt`) and loads them upon starting the application.

## Usage

* Start the program and log in as an administrator using the username 'Admin' and password 'admin1234'.
* Use the menu to navigate through different options, such as adding/removing books, managing members, issuing/returning books, and more.
* The program automatically saves changes to books and members when books are added, removed, or when members are added or removed.


