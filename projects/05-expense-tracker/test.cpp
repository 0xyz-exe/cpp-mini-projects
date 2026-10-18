#include <cassert>
#include <iostream>
#include <string>

struct Transaction {
    int id;
    int amount_cents; // Store in cents to avoid float issues
    std::string category;
    std::string date;
    bool is_income;
};

int main() {
    Transaction t1 = {1, 5000, "Food", "2026-10-01", false};
    assert(t1.amount_cents == 5000); // $50.00
    
    Transaction t2 = {2, 100000, "Salary", "2026-10-01", true};
    assert(t2.amount_cents == 100000); // $1000.00
    
    // Test balance calculation
    int balance = 0;
    balance += t2.amount_cents; // +income
    balance -= t1.amount_cents; // -expense
    assert(balance == 95000); // $950.00
    
    // Test category filtering
    assert(t1.category == "Food");
    assert(t2.category == "Salary");
    
    std::cout << "All expense tracker tests passed\n";
    return 0;
}
