/*
    (I've been forgetting to add this sorry haha)
    Name: Nikolas Guerrero
    Date: 11/09/2026
    Purpose:
    Book Inventory System using RAII.
    The code uses an Inventory class in order to manage allocated
    Book objects. The Inventory destructor automatically
    frees all allocated memory when the Inventory object goes out
    of scope, preventing memory leaks.
*/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Book Class //
class Book {
private:
    string title;
    string author;
    double price;

public:
    // Constructor //
    Book(string t, string a, double p) {
        title = t;
        author = a;
        price = p;
    }

    // Display book information //
    void displayInfo() const {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Price: $" << fixed << setprecision(2) << price << endl;
    }
};

// Inventory Class //
class Inventory {
private:
    vector<Book*> books;

public:
    // Add a book pointer to inventory
    void addBook(Book* bookPtr) {
        books.push_back(bookPtr);
    }

    // Display all books //
    void displayAll() const {
        if (books.empty()) {
            cout << "Inventory is empty." << endl;
            return;
        }

        for (size_t i = 0; i < books.size(); i++) {
            cout << "\nBook Index: " << i << endl;
            books[i]->displayInfo();
            cout << "------------------------" << endl;
        }
    }

    // Remove a book at an index //
    void removeBook(int index) {
        if (index >= 0 && index < static_cast<int>(books.size())) {
            delete books[index];
            books.erase(books.begin() + index);

            cout << "Book removed successfully." << endl;
        }
        else {
            cout << "Invalid index." << endl;
        }
    }

    // Destructor //
    ~Inventory() {
        for (Book* ptr : books) {
            delete ptr;
        }

        cout << "\nInventory destructor called." << endl;
        cout << "All dynamically allocated books have been deleted." << endl;
    }
};

int main() {
    Inventory store;

    int choice;

    do {
        cout << "\n===== BOOK INVENTORY MENU =====" << endl;
        cout << "1. Add New Book" << endl;
        cout << "2. Display All Books" << endl;
        cout << "3. Remove Book" << endl;
        cout << "4. Quit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string title;
            string author;
            double price;

            cout << "Enter title: ";
            getline(cin, title);

            cout << "Enter author: ";
            getline(cin, author);

            cout << "Enter price: ";
            cin >> price;
            cin.ignore();

            Book* newBook = new Book(title, author, price);

            store.addBook(newBook);

            cout << "Book added successfully." << endl;
        }
        else if (choice == 2) {
            store.displayAll();
        }
        else if (choice == 3) {
            int index;

            store.displayAll();

            cout << "Enter index of book to remove: ";
            cin >> index;

            store.removeBook(index);
        }
        else if (choice == 4) {
            cout << "Exiting program..." << endl;
        }
        else {
            cout << "Invalid choice." << endl;
        }

    } while (choice != 4);

    return 0;
}