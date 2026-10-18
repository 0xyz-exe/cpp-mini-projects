#include <iostream>
#include <string>
#include <random>

std::string generate_password(int length, bool use_upper, bool use_lower, bool use_digits, bool use_symbols) {
    std::string charset;
    if (use_upper) charset += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (use_lower) charset += "abcdefghijklmnopqrstuvwxyz";
    if (use_digits) charset += "0123456789";
    if (use_symbols) charset += "!@#$%^&*()_+-=[]{}|;:,.<>?";
    
    if (charset.empty()) {
        std::cout << "Error: No character sets selected\n";
        return "";
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, charset.size() - 1);
    
    std::string password;
    for (int i = 0; i < length; i++) {
        password += charset[dist(gen)];
    }
    return password;
}

int main() {
    std::cout << "=== Password Generator ===\n";
    std::cout << "Note: Uses std::random_device (not cryptographically secure)\n";
    std::cout << "For production use, integrate platform-specific secure RNG\n\n";
    
    int length;
    char choice;
    
    std::cout << "Password length (8-64): ";
    std::cin >> length;
    
    if (length < 8 || length > 64) {
        std::cout << "Invalid length, using 12\n";
        length = 12;
    }
    
    bool use_upper, use_lower, use_digits, use_symbols;
    
    std::cout << "Include uppercase? (y/n): ";
    std::cin >> choice;
    use_upper = (choice == 'y' || choice == 'Y');
    
    std::cout << "Include lowercase? (y/n): ";
    std::cin >> choice;
    use_lower = (choice == 'y' || choice == 'Y');
    
    std::cout << "Include digits? (y/n): ";
    std::cin >> choice;
    use_digits = (choice == 'y' || choice == 'Y');
    
    std::cout << "Include symbols? (y/n): ";
    std::cin >> choice;
    use_symbols = (choice == 'y' || choice == 'Y');
    
    std::string password = generate_password(length, use_upper, use_lower, use_digits, use_symbols);
    
    if (!password.empty()) {
        std::cout << "\nGenerated password: " << password << "\n";
        std::cout << "\nDo NOT store this password in plain text.\n";
    }
    
    return 0;
}
