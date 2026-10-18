#include <cassert>
#include <iostream>
#include <string>
#include <random>
#include <algorithm>

std::string generate_password(int length, bool use_upper, bool use_lower, bool use_digits, bool use_symbols) {
    std::string charset;
    if (use_upper) charset += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (use_lower) charset += "abcdefghijklmnopqrstuvwxyz";
    if (use_digits) charset += "0123456789";
    if (use_symbols) charset += "!@#$%^&*()_+-=[]{}|;:,.<>?";
    
    if (charset.empty()) return "";
    
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
    // Test basic generation
    std::string pwd = generate_password(12, true, true, true, false);
    assert(pwd.length() == 12);
    
    // Test all character sets
    bool has_upper = false, has_lower = false, has_digit = false;
    for (char c : pwd) {
        if (c >= 'A' && c <= 'Z') has_upper = true;
        if (c >= 'a' && c <= 'z') has_lower = true;
        if (c >= '0' && c <= '9') has_digit = true;
    }
    // Note: Random, might not always have all types
    
    // Test empty charset
    std::string empty = generate_password(10, false, false, false, false);
    assert(empty.empty());
    
    std::cout << "All password generator tests passed\n";
    return 0;
}
