#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

struct Book {
    std::string isbn;
    std::string title;
    std::string author;
    bool available;
    std::string borrower;
};

std::vector<Book> load_books(const std::string& filename) {
    std::vector<Book> books;
    std::ifstream file(filename);
    if (!file) return books;
    
    Book b;
    while (std::getline(file, b.isbn, '|')) {
        std::getline(file, b.title, '|');
        std::getline(file, b.author, '|');
        file >> b.available;
        file.ignore();
        std::getline(file, b.borrower);
        books.push_back(b);
    }
    return books;
}

void save_books(const std::vector<Book>& books, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& b : books) {
        file << b.isbn << "|" << b.title << "|" << b.author << "|" 
             << b.available << "|" << b.borrower << "\n";
    }
}

void add_book(std::vector<Book>& books) {
    Book b;
    std::cout << "ISBN: ";
    std::cin >> b.isbn;
    std::cin.ignore();
    std::cout << "Title: ";
    std::getline(std::cin, b.title);
    std::cout << "Author: ";
    std::getline(std::cin, b.author);
    b.available = true;
    b.borrower = "";
    books.push_back(b);
    std::cout << "Book added\n";
}

void search_books(const std::vector<Book>& books) {
    std::string query;
    std::cout << "Search (title or author): ";
    std::cin.ignore();
    std::getline(std::cin, query);
    
    bool found = false;
    for (const auto& b : books) {
        if (b.title.find(query) != std::string::npos || 
            b.author.find(query) != std::string::npos) {
            std::cout << "[" << b.isbn << "] " << b.title << " by " << b.author
                     << " - " << (b.available ? "Available" : "Borrowed by " + b.borrower) << "\n";
            found = true;
        }
    }
    if (!found) std::cout << "No matches\n";
}

void borrow_book(std::vector<Book>& books) {
    std::string isbn, member;
    std::cout << "Book ISBN: ";
    std::cin >> isbn;
    std::cout << "Borrower name: ";
    std::cin.ignore();
    std::getline(std::cin, member);
    
    auto it = std::find_if(books.begin(), books.end(),
                          [&isbn](const Book& b) { return b.isbn == isbn; });
    if (it == books.end()) {
        std::cout << "Book not found\n";
    } else if (!it->available) {
        std::cout << "Book already borrowed\n";
    } else {
        it->available = false;
        it->borrower = member;
        std::cout << "Book borrowed\n";
    }
}

void return_book(std::vector<Book>& books) {
    std::string isbn;
    std::cout << "Book ISBN: ";
    std::cin >> isbn;
    
    auto it = std::find_if(books.begin(), books.end(),
                          [&isbn](const Book& b) { return b.isbn == isbn; });
    if (it == books.end()) {
        std::cout << "Book not found\n";
    } else if (it->available) {
        std::cout << "Book not borrowed\n";
    } else {
        it->available = true;
        it->borrower = "";
        std::cout << "Book returned\n";
    }
}

int main() {
    const std::string filename = "library.dat";
    std::vector<Book> books = load_books(filename);
    int choice;
    
    while (true) {
        std::cout << "\n=== Library Management ===\n";
        std::cout << "1. Add book\n2. Search\n3. Borrow\n4. Return\n5. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        
        switch (choice) {
            case 1: add_book(books); save_books(books, filename); break;
            case 2: search_books(books); break;
            case 3: borrow_book(books); save_books(books, filename); break;
            case 4: return_book(books); save_books(books, filename); break;
            case 5: return 0;
            default: std::cout << "Invalid choice\n";
        }
    }
}
