#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Book {
public:
    string title;
    string author;
    bool isAvailable;

    Book(string t, string a) : title(t), author(a), isAvailable(true) {}
};

class Library {
private:
    vector<Book> books;

public:
    void addBook(const string &title, const string &author) {
        books.push_back(Book(title, author));
        cout << "Book added: " << title << " by " << author << endl;
    }

    void displayBooks() {
        cout << "Available Books: \n";
        for (size_t i = 0; i < books.size(); ++i) {
            cout << i + 1 << ". " << books[i].title << " by " << books[i].author
                 << (books[i].isAvailable ? " (Available)" : " (Not Available)") << endl;
        }
    }

    void borrowBook(int index) {
        if (index >= 0 && index < books.size() && books[index].isAvailable) {
            books[index].isAvailable = false;
            cout << "You borrowed: " << books[index].title << endl;
        } else {
            cout << "Book not available or invalid index!" << endl;
        }
    }

    void returnBook(int index) {
        if (index >= 0 && index < books.size() && !books[index].isAvailable) {
            books[index].isAvailable = true;
            cout << "You returned: " << books[index].title << endl;
        } else {
            cout << "Book was not borrowed or invalid index!" << endl;
        }
    }

    void searchBook(const string &searchTerm) {
        cout << "Search Results: \n";
        for (const auto &book : books) {
            if (book.title.find(searchTerm) != string::npos || book.author.find(searchTerm) != string::npos) {
                cout << book.title << " by " << book.author
                     << (book.isAvailable ? " (Available)" : " (Not Available)") << endl;
            }
        }
    }

    void saveToFile(const string &filename) {
        ofstream file(filename);
        for (const auto &book : books) {
            file << book.title << "," << book.author << "," << book.isAvailable << endl;
        }
        file.close();
    }

    void loadFromFile(const string &filename) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            string title = line.substr(0, pos1);
            string author = line.substr(pos1 + 1, pos2 - pos1 - 1);
            bool isAvailable = (line.substr(pos2 + 1) == "1");
            books.push_back(Book(title, author));
            books.back().isAvailable = isAvailable;
        }
        file.close();
    }
};

int main() {
    Library library;
    library.loadFromFile("library.txt");  // Load existing books from file

    int choice;
    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. Search Book\n";
        cout << "6. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string title, author;
                cout << "Enter book title: ";
                cin.ignore(); // Clear the input buffer
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                library.addBook(title, author);
                break;
            }
            case 2:
                library.displayBooks();
                break;
            case 3: {
                int index;
                cout << "Enter book index to borrow: ";
                cin >> index;
                library.borrowBook(index - 1);
                break;
            }
            case 4: {
                int index;
                cout << "Enter book index to return: ";
                cin >> index;
                library.returnBook(index - 1);
                break;
            }
            case 5: {
                string searchTerm;
                cout << "Enter title or author to search: ";
                cin.ignore(); // Clear the input buffer
                getline(cin, searchTerm);
                library.searchBook(searchTerm);
                break;
            }
            case 6:
                library.saveToFile("library.txt"); // Save books to file
                cout << "Exiting the system. Books saved!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
