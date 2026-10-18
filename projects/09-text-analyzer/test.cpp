#include <cassert>
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <cctype>

std::string to_lower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), 
                   [](unsigned char c){ return std::tolower(c); });
    return s;
}

std::string strip_punct(const std::string& word) {
    std::string result;
    for (char c : word) {
        if (std::isalnum(static_cast<unsigned char>(c))) result += c;
    }
    return result;
}

int main() {
    // Test word counting
    std::string text = "Hello world! Hello C++ world.";
    std::istringstream iss(text);
    std::map<std::string, int> freq;
    std::string word;
    
    while (iss >> word) {
        word = strip_punct(word);
        word = to_lower(word);
        if (!word.empty()) freq[word]++;
    }
    
    assert(freq["hello"] == 2);
    assert(freq["world"] == 2);
    assert(freq["c"] == 1);
    
    std::cout << "All text analyzer tests passed\n";
    return 0;
}
