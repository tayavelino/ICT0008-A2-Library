#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
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

    // Insertion Sort por ISBN (ordem crescente)
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Book> books(5);
    books[0].setBookDetails("Networks 101", "Alice", "9780001", true, "2025-11-20");
    books[1].setBookDetails("Graph Theory", "Bob",   "9780003", true, "2025-11-20");
    books[2].setBookDetails("C++ Basics",   "Cara",  "9780002", true, "2025-11-20");
    books[3].setBookDetails("Data Flows",   "Dion",  "9780005", true, "2025-11-20");
    books[4].setBookDetails("Sorting Algo", "Eve",   "9780004", true, "2025-11-20");

    // Ordenar por ISBN
    Book::sortBookData(books);

    cout << "==== Library System ====\n";
    for (const auto& b : books) b.displayBookDetails();
    cout << "\n";

    // >>> o loop fica DENTRO do main e ANTES do return 0;
    while (true) {
        cout << "Enter ISBN to borrow (0 to quit): ";
        string in; 
        if (!(cin >> in)) break;

        if (in == "0") {
            cout << "Program ended. Goodbye!\n";
            break;
        }

        int idx = findByISBN(books, in);
        if (idx < 0) {
            cout << "Book not found: " << in << "\n";
            continue;
        }

        if (books[idx].borrowBook()) {
            cout << "Borrowed successfully: " << in << "\n";
        } else {
            cout << "ERROR: Book " << in << " is currently unavailable.\n";
        }
    }

    return 0;
    // A2 evidence
    
    
} 