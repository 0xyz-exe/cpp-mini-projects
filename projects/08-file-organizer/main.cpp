#include <iostream>
#include <filesystem>
#include <string>
#include <map>

namespace fs = std::filesystem;

std::string get_category(const std::string& ext) {
    static std::map<std::string, std::string> categories = {
        {".jpg", "Images"}, {".jpeg", "Images"}, {".png", "Images"}, {".gif", "Images"},
        {".mp4", "Videos"}, {".avi", "Videos"}, {".mkv", "Videos"},
        {".mp3", "Audio"}, {".wav", "Audio"}, {".flac", "Audio"},
        {".pdf", "Documents"}, {".doc", "Documents"}, {".docx", "Documents"}, {".txt", "Documents"},
        {".zip", "Archives"}, {".rar", "Archives"}, {".7z", "Archives"},
        {".exe", "Programs"}, {".msi", "Programs"}
    };
    
    auto it = categories.find(ext);
    return (it != categories.end()) ? it->second : "Other";
}

void organize_files(const std::string& source_dir, bool dry_run) {
    if (!fs::exists(source_dir) || !fs::is_directory(source_dir)) {
        std::cout << "Invalid directory\n";
        return;
    }
    
    int moved = 0, skipped = 0;
    
    for (const auto& entry : fs::directory_iterator(source_dir)) {
        if (!entry.is_regular_file()) continue;
        
        fs::path file_path = entry.path();
        std::string ext = file_path.extension().string();
        std::string category = get_category(ext);
        
        fs::path dest_dir = fs::path(source_dir) / category;
        fs::path dest_path = dest_dir / file_path.filename();
        
        if (fs::exists(dest_path)) {
            std::cout << "Skip (exists): " << file_path.filename() << "\n";
            skipped++;
            continue;
        }
        
        std::cout << (dry_run ? "[DRY-RUN] " : "") 
                  << file_path.filename() << " -> " << category << "/\n";
        
        if (!dry_run) {
            try {
                fs::create_directories(dest_dir);
                fs::rename(file_path, dest_path);
                moved++;
            } catch (const fs::filesystem_error& e) {
                std::cout << "Error: " << e.what() << "\n";
                skipped++;
            }
        }
    }
    
    if (dry_run) {
        std::cout << "\nDry-run complete. Use --execute to apply changes.\n";
    } else {
        std::cout << "\nMoved: " << moved << ", Skipped: " << skipped << "\n";
    }
}

int main(int argc, char* argv[]) {
    std::cout << "=== File Organizer ===\n";
    
    std::string dir;
    std::cout << "Directory to organize: ";
    std::getline(std::cin, dir);
    
    if (dir.empty()) {
        std::cout << "No directory specified\n";
        return 1;
    }
    
    std::cout << "\n--- Preview (Dry-run) ---\n";
    organize_files(dir, true);
    
    char confirm;
    std::cout << "\nExecute these changes? (y/n): ";
    std::cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        std::cout << "\n--- Executing ---\n";
        organize_files(dir, false);
    } else {
        std::cout << "Cancelled\n";
    }
    
    return 0;
}
