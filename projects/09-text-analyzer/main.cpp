#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
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

void analyze_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Cannot open file: " << filename << "\n";
        return;
    }
    
    int lines = 0, words = 0, chars = 0;
    std::map<std::string, int> word_freq;
    std::string line, word;
    
    while (std::getline(file, line)) {
        lines++;
        chars += line.length();
        
        std::istringstream iss(line);
        while (iss >> word) {
            words++;
            word = strip_punct(word);
            word = to_lower(word);
            if (!word.empty()) word_freq[word]++;
        }
    }
    
    file.close();
    
    std::cout << "\n=== Statistics ===\n";
    std::cout << "Lines: " << lines << "\n";
    std::cout << "Words: " << words << "\n";
    std::cout << "Characters: " << chars << "\n";
    std::cout << "Unique words: " << word_freq.size() << "\n";
    
    // Top 10 most common words
    std::vector<std::pair<std::string, int>> sorted_words(word_freq.begin(), word_freq.end());
    std::sort(sorted_words.begin(), sorted_words.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });
    
    std::cout << "\n=== Top 10 Words ===\n";
    int count = 0;
    for (const auto& pair : sorted_words) {
        if (count++ >= 10) break;
        std::cout << pair.first << ": " << pair.second << "\n";
    }
}

int main() {
    std::cout << "=== Text File Analyzer ===\n";
    std::cout << "Counts lines, words, characters\n";
    std::cout << "Shows word frequency (case-insensitive, punctuation stripped)\n\n";
    
    std::string filename;
    std::cout << "File path: ";
    std::getline(std::cin, filename);
    
    if (filename.empty()) {
        std::cout << "No file specified\n";
        return 1;
    }
    
    analyze_file(filename);
    
    return 0;
}
