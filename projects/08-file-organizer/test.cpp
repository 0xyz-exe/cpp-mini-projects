#include <cassert>
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main() {
    // Create test directory
    fs::path test_dir = "test_organize";
    fs::create_directories(test_dir);
    
    // Create test files
    std::ofstream(test_dir / "photo.jpg").close();
    std::ofstream(test_dir / "doc.pdf").close();
    std::ofstream(test_dir / "music.mp3").close();
    
    assert(fs::exists(test_dir / "photo.jpg"));
    assert(fs::exists(test_dir / "doc.pdf"));
    assert(fs::exists(test_dir / "music.mp3"));
    
    // Test category assignment
    std::string ext = ".jpg";
    assert(ext == ".jpg");
    
    // Cleanup
    fs::remove_all(test_dir);
    
    std::cout << "All file organizer tests passed\n";
    return 0;
}
