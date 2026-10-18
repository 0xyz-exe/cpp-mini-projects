#include <iostream>
#include <limits>
#include <cmath>

int main() {
    char op, choice;
    double a, b, result;
    
    std::cout << "=== Basic Calculator ===\n";
    
    do {
        std::cout << "\nEnter operation (+, -, *, /, %): ";
        std::cin >> op;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input\n";
            continue;
        }
        
        std::cout << "Enter first number: ";
        std::cin >> a;
        std::cout << "Enter second number: ";
        std::cin >> b;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid numbers\n";
            continue;
        }
        
        bool valid = true;
        switch (op) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/':
                if (b == 0) {
                    std::cout << "Error: Division by zero\n";
                    valid = false;
                } else {
                    result = a / b;
                }
                break;
            case '%':
                if (b == 0) {
                    std::cout << "Error: Modulo by zero\n";
                    valid = false;
                } else {
                    result = std::fmod(a, b);
                }
                break;
            default:
                std::cout << "Invalid operation\n";
                valid = false;
        }
        
        if (valid) {
            std::cout << "Result: " << result << "\n";
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Continue? (y/n): ";
        std::cin >> choice;
        
    } while (choice == 'y' || choice == 'Y');
    
    return 0;
}
