#include <cassert>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>

std::string normalize_token(const std::string& token) {
    std::string result;
    for (char c : token) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            result += std::tolower(static_cast<unsigned char>(c));
        }
    }
    return result;
}

int main() {
    // Test tokenization
    assert(normalize_token("Hello!") == "hello");
    assert(normalize_token("C++17") == "c17");
    assert(normalize_token("test-word") == "testword");
    
    // Test inverted index structure
    std::map<std::string, std::map<std::string, int>> index;
    index["hello"]["file1.txt"] = 2;
    index["hello"]["file2.txt"] = 1;
    index["world"]["file1.txt"] = 1;
    
    assert(index["hello"].size() == 2);
    assert(index["hello"]["file1.txt"] == 2);
    
    std::cout << "All search engine tests passed\n";
    return 0;
}
