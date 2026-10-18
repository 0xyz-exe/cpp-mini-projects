#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <map>

struct Transaction {
    int id;
    int amount_cents;
    std::string category;
    std::string date; // YYYY-MM-DD
    bool is_income;
};

std::vector<Transaction> load_transactions(const std::string& filename) {
    std::vector<Transaction> txns;
    std::ifstream file(filename);
    if (!file) return txns;
    
    Transaction t;
    while (file >> t.id >> t.amount_cents >> t.category >> t.date >> t.is_income) {
        txns.push_back(t);
    }
    return txns;
}

void save_transactions(const std::vector<Transaction>& txns, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& t : txns) {
        file << t.id << " " << t.amount_cents << " " << t.category 
             << " " << t.date << " " << t.is_income << "\n";
    }
}

void print_amount(int cents) {
    std::cout << "$" << cents / 100 << "." << std::setfill('0') << std::setw(2) << cents % 100;
}

void add_transaction(std::vector<Transaction>& txns, int& next_id) {
    Transaction t;
    t.id = next_id++;
    
    int choice;
    std::cout << "1. Income 2. Expense: ";
    std::cin >> choice;
    t.is_income = (choice == 1);
    
    double amount;
    std::cout << "Amount: $";
    std::cin >> amount;
    t.amount_cents = static_cast<int>(amount * 100 + 0.5); // Round to cents
    
    std::cout << "Category: ";
    std::cin >> t.category;
    
    std::cout << "Date (YYYY-MM-DD): ";
    std::cin >> t.date;
    
    txns.push_back(t);
    std::cout << "Transaction added\n";
}

void show_summary(const std::vector<Transaction>& txns) {
    if (txns.empty()) {
        std::cout << "No transactions\n";
        return;
    }
    
    int total_income = 0, total_expense = 0;
    std::map<std::string, int> category_totals;
    
    for (const auto& t : txns) {
        if (t.is_income) {
            total_income += t.amount_cents;
        } else {
            total_expense += t.amount_cents;
            category_totals[t.category] += t.amount_cents;
        }
    }
    
    std::cout << "\n=== Summary ===\n";
    std::cout << "Total Income:  "; print_amount(total_income); std::cout << "\n";
    std::cout << "Total Expense: "; print_amount(total_expense); std::cout << "\n";
    std::cout << "Balance:       "; print_amount(total_income - total_expense); std::cout << "\n";
    
    std::cout << "\nExpenses by Category:\n";
    for (const auto& pair : category_totals) {
        std::cout << "  " << pair.first << ": ";
        print_amount(pair.second);
        std::cout << "\n";
    }
}

void export_csv(const std::vector<Transaction>& txns) {
    std::ofstream file("expenses.csv");
    file << "ID,Type,Amount,Category,Date\n";
    for (const auto& t : txns) {
        file << t.id << "," << (t.is_income ? "Income" : "Expense") << ","
             << t.amount_cents / 100 << "." << std::setfill('0') << std::setw(2) << t.amount_cents % 100 << ","
             << t.category << "," << t.date << "\n";
    }
    file.close();
    std::cout << "Exported to expenses.csv\n";
}

int main() {
    const std::string filename = "transactions.dat";
    std::vector<Transaction> txns = load_transactions(filename);
    
    int next_id = 1;
    for (const auto& t : txns) {
        if (t.id >= next_id) next_id = t.id + 1;
    }
    
    int choice;
    while (true) {
        std::cout << "\n=== Expense Tracker ===\n";
        std::cout << "1. Add transaction\n2. Show summary\n3. Export CSV\n4. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        
        switch (choice) {
            case 1:
                add_transaction(txns, next_id);
                save_transactions(txns, filename);
                break;
            case 2:
                show_summary(txns);
                break;
            case 3:
                export_csv(txns);
                break;
            case 4:
                return 0;
            default:
                std::cout << "Invalid choice\n";
        }
    }
}
