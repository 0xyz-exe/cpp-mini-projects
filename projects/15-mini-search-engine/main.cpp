#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

namespace fs = std::filesystem;

const size_t MAX_FILE_SIZE = 1024 * 1024; // 1MB

std::string normalize_token(const std::string& token) {
    std::string result;
    for (char c : token) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            result += std::tolower(static_cast<unsigned char>(c));
        }
    }
    return result;
}

class SearchEngine {
    // term -> (file -> frequency)
    std::map<std::string, std::map<std::string, int>> index;
    std::map<std::string, std::string> file_content; // For excerpts
    
public:
    void index_directory(const std::string& dir_path) {
        if (!fs::exists(dir_path) || !fs::is_directory(dir_path)) {
            std::cout << "Invalid directory\n";
            return;
        }
        
        int indexed = 0;
        for (const auto& entry : fs::directory_iterator(dir_path)) {
            if (!entry.is_regular_file()) continue;
            if (entry.file_size() > MAX_FILE_SIZE) {
                std::cout << "Skip (too large): " << entry.path().filename() << "\n";
                continue;
            }
            
            std::string path = entry.path().string();
            std::ifstream file(path);
            if (!file) continue;
            
            std::stringstream buffer;
            buffer << file.rdbuf();
            std::string content = buffer.str();
            file_content[path] = content;
            
            std::istringstream iss(content);
            std::string word;
            std::map<std::string, int> term_freq;
            
            while (iss >> word) {
                word = normalize_token(word);
                if (!word.empty()) {
                    term_freq[word]++;
                }
            }
            
            for (const auto& pair : term_freq) {
                index[pair.first][path] = pair.second;
            }
            
            indexed++;
        }
        
        std::cout << "Indexed " << indexed << " files\n";
        std::cout << "Unique terms: " << index.size() << "\n";
    }
    
    void search(const std::string& query) {
        std::string normalized_query = normalize_token(query);
        
        if (index.find(normalized_query) == index.end()) {
            std::cout << "No results found\n";
            return;
        }
        
        // Get matching files and scores
        std::vector<std::pair<std::string, int>> results;
        for (const auto& pair : index[normalized_query]) {
            results.emplace_back(pair.first, pair.second);
        }
        
        // Sort by frequency (descending)
        std::sort(results.begin(), results.end(),
                 [](const auto& a, const auto& b) { return a.second > b.second; });
        
        std::cout << "\nFound " << results.size() << " results for \"" << query << "\":\n\n";
        
        for (size_t i = 0; i < results.size() && i < 10; i++) {
            const auto& result = results[i];
            fs::path file_path(result.first);
            
            std::cout << "[" << (i+1) << "] " << file_path.filename().string()
                     << " (matches: " << result.second << ")\n";
            
            // Show excerpt
            const std::string& content = file_content[result.first];
            size_t pos = content.find(query);
            if (pos == std::string::npos) {
                // Try lowercase search
                std::string lower_content = content;
                std::transform(lower_content.begin(), lower_content.end(), 
                             lower_content.begin(), ::tolower);
                pos = lower_content.find(normalized_query);
            }
            
            if (pos != std::string::npos) {
                size_t start = (pos > 40) ? pos - 40 : 0;
                size_t length = 100;
                std::string excerpt = content.substr(start, length);
                std::cout << "  ..." << excerpt << "...\n";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    std::cout << "=== Mini Search Engine ===\n\n";
    
    std::string dir;
    std::cout << "Directory to index: ";
    std::getline(std::cin, dir);
    
    if (dir.empty()) {
        std::cout << "No directory specified\n";
        return 1;
    }
    
    SearchEngine engine;
    engine.index_directory(dir);
    
    std::cout << "\nReady to search. Type 'quit' to exit.\n";
    
    while (true) {
        std::cout << "\nSearch query: ";
        std::string query;
        std::getline(std::cin, query);
        
        if (query == "quit" || query == "exit") break;
        if (query.empty()) continue;
        
        engine.search(query);
    }
    
    return 0;
}
