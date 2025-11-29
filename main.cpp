#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Book {
    string title, author, isbn, dateAdded;
    bool available = true;

    void setBookDetails(const string& t, const string& a, const string& i,
                        bool avail, const string& date) {
        title = t; author = a; isbn = i; available = avail; dateAdded = date;
    }

    void displayBookDetails() const {
        cout << "Title: " << title
             << " | Author: " << author
             << " | ISBN: " << isbn
             << " | Available: " << (available ? "Yes" : "No")
             << " | DateAdded: " << dateAdded << "\n";
    }

    bool borrowBook() {
        if (available) { available = false; return true; }
        return false;
    }

    void returnBook() { available = true; }

    // Insertion Sort by ISBN (ascending)
    static void sortBookData(vector<Book>& books) {
        for (size_t i = 1; i < books.size(); ++i) {
            Book key = books[i];
            size_t j = i;
            while (j > 0 && books[j-1].isbn > key.isbn) {
                books[j] = books[j-1];
                --j;
            }
            books[j] = key;
        }
    }
};

int findByISBN(const vector<Book>& books, const string& isbn) {
    for (size_t i = 0; i < books.size(); ++i)
        if (books[i].isbn == isbn) return (int)i;
    return -1;
}

int main() {
    // keep default i/o settings to avoid buffering issues on Replit

    // --- sample data (5 books) ---
    vector<Book> books(5);
    books[0].setBookDetails("Networks 101", "Alice", "9780001", true, "2025-11-20");
    books[1].setBookDetails("Graph Theory", "Bob",   "9780003", true, "2025-11-20");
    books[2].setBookDetails("C++ Basics",   "Cara",  "9780002", true, "2025-11-20");
    books[3].setBookDetails("Data Flows",   "Dion",  "9780005", true, "2025-11-20");
    books[4].setBookDetails("Sorting Algo", "Eve",   "9780004", true, "2025-11-20");

    // sort by ISBN
    Book::sortBookData(books);

    // header + initial list
    cout << "==== Library System ====" << endl;
    for (const auto& b : books) b.displayBookDetails();
    cout << endl;

    // command loop
    while (true) {
        cout << "Command [B isbn / R isbn / L / 0]: " << flush;

        string cmd;
        if (!(cin >> cmd)) break;

        if (cmd == "0") {
            cout << "Program ended. Goodbye!" << endl;
            break;
        }

        if (cmd == "L" || cmd == "l") {
            for (const auto& b : books) b.displayBookDetails();
            cout << endl;
            continue;
        }

        if (cmd == "B" || cmd == "b" || cmd == "borrow") {
            string isbn;
            if (!(cin >> isbn)) break;
            int idx = findByISBN(books, isbn);
            if (idx < 0) {
                cout << "Book not found: " << isbn << endl;
            } else if (books[idx].borrowBook()) {
                cout << "Borrowed successfully: " << isbn << endl;
            } else {
                cout << "ERROR: Book " << isbn << " is currently unavailable." << endl;
            }
            continue;
        }

        if (cmd == "R" || cmd == "r" || cmd == "return") {
            string isbn;
            if (!(cin >> isbn)) break;
            int idx = findByISBN(books, isbn);
            if (idx < 0) {
                cout << "Book not found: " << isbn << endl;
            } else if (!books[idx].available) {
                books[idx].returnBook();
                cout << "Returned successfully: " << isbn << endl;
            } else {
                cout << "Book " << isbn << " was not borrowed." << endl;
            }
            continue;
        }

        // Back-compat: if user types only an ISBN, treat it as a borrow
        string isbn = cmd;  // 'cmd' is actually the ISBN the user typed
        int idx = findByISBN(books, isbn);
        if (idx < 0) {
            cout << "Book not found: " << isbn << endl;
            continue;
        }
        if (books[idx].borrowBook()) {
            cout << "Borrowed successfully: " << isbn << endl;
        } else {
            cout << "ERROR: Book " << isbn << " is currently unavailable." << endl;
        }
    }

    return 0;
}
