#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Book {
    std::string isbn;
    std::string title;
    std::string author;
    bool available;
    std::string borrower;
};

int main() {
    std::vector<Book> books = {
        {"123", "C++ Primer", "Lippman", true, ""},
        {"456", "The C++ Programming Language", "Stroustrup", false, "Alice"}
    };
    
    // Test search
    auto it = std::find_if(books.begin(), books.end(),
                          [](const Book& b) { return b.isbn == "123"; });
    assert(it != books.end());
    assert(it->available == true);
    
    // Test borrow logic
    Book& b = books[0];
    assert(b.available);
    b.available = false;
    b.borrower = "Bob";
    assert(!b.available);
    assert(b.borrower == "Bob");
    
    // Test return
    b.available = true;
    b.borrower = "";
    assert(b.available);
    
    std::cout << "All library tests passed\n";
    return 0;
}
