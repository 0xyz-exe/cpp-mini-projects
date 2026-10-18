#include <cassert>
#include <iostream>
#include <string>

bool is_valid_json_string(const std::string& s) {
    if (s.empty() || s[0] != '"') return false;
    size_t i = 1;
    while (i < s.length()) {
        if (s[i] == '\\' && i+1 < s.length()) {
            i += 2;
        } else if (s[i] == '"') {
            return i == s.length() - 1;
        } else {
            i++;
        }
    }
    return false;
}

int main() {
    assert(is_valid_json_string("\"hello\""));
    assert(is_valid_json_string("\"hello\\nworld\""));
    assert(!is_valid_json_string("hello"));
    assert(!is_valid_json_string("\"unclosed"));
    
    std::cout << "All JSON parser tests passed\n";
    return 0;
}
