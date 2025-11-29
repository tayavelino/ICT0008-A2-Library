# Book Management System (ICT0008 – Assessment 2)

A simple C++ library system used for the assessment. It maintains a small collection of books, supports borrowing with availability checks, and sorts by ISBN.

## Phase 1 – Features

- `Book` class with attributes: `title`, `author`, `isbn`, `available`, `dateAdded`
- Methods:
  - `setBookDetails(...)`
  - `displayBookDetails()`
  - `borrowBook()` / `returnBook()`
  - `sortBookData(...)` (Insertion Sort by ISBN)
- Main application:
  - Seeds 5 books
  - Prints the list (sorted by ISBN)
  - Prompts for an ISBN to borrow
  - Shows error if unavailable
  - Exits when user enters `0`

## How to Run (Replit)

1. Open the Replit project and click **Run**.  
2. At the prompt, type an ISBN like `9780002` to borrow.  
3. Typing the same ISBN again shows the “unavailable” error.  
4. Enter `0` to exit.

### Sample Output
==== Library System ====

Title: Networks 101 | Author: Alice | ISBN: 9780001 | Available: Yes | DateAdded: 2025-11-20
Title: C++ Basics | Author: Cara | ISBN: 9780002 | Available: Yes | DateAdded: 2025-11-20
Title: Graph Theory | Author: Bob | ISBN: 9780003 | Available: Yes | DateAdded: 2025-11-20
Title: Sorting Algo | Author: Eve | ISBN: 9780004 | Available: Yes | DateAdded: 2025-11-20
Title: Data Flows | Author: Dion | ISBN: 9780005 | Available: Yes | DateAdded: 2025-11-20

Enter ISBN to borrow (0 to quit): 9780002
Borrowed successfully: 9780002
Enter ISBN to borrow (0 to quit): 9780002
ERROR: Book 9780002 is currently unavailable.
Enter ISBN to borrow (0 to quit): 0
Program ended. Goodbye!


## Phase 2 – Design Extension

To handle two categories (hardcopy and e-books) without changing existing behaviour, the model is extended by inheritance:

- `HardcopyBook` (adds `shelfNo`)
- `EBook` (adds `licenseEndDate`)
- Both inherit from `Book` and reuse the core behaviour (borrow/return/display/sort).

### Mermaid – Phase 2 Class Diagram

```mermaid
classDiagram
direction LR

class Book {
  +string title
  +string author
  +string isbn
  +bool   available
  +string dateAdded
  +setBookDetails(t,a,i,avail,date)
  +displayBookDetails()
  +borrowBook() bool
  +returnBook() void
}

class HardcopyBook {
  +string shelfNo
}

class EBook {
  +string licenseEndDate
}

Book <|-- HardcopyBook
Book <|-- EBook
