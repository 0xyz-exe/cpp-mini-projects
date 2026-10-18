#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

struct Task {
    int id;
    std::string description;
    char priority;
    bool completed;
};

int main() {
    // Test task creation
    Task t1 = {1, "Test task", 'H', false};
    assert(t1.id == 1);
    assert(t1.description == "Test task");
    assert(t1.priority == 'H');
    assert(!t1.completed);
    
    // Test file write/read
    const char* testfile = "test_tasks.dat";
    std::vector<Task> tasks = {t1, {2, "Second task", 'L', true}};
    
    std::ofstream out(testfile);
    for (const auto& t : tasks) {
        out << t.id << "\n" << t.description << "|\n" 
            << t.priority << " " << t.completed << "\n";
    }
    out.close();
    
    std::vector<Task> loaded;
    std::ifstream in(testfile);
    Task t;
    while (in >> t.id) {
        in.ignore();
        std::getline(in, t.description, '|');
        in >> t.priority >> t.completed;
        in.ignore();
        loaded.push_back(t);
    }
    in.close();
    
    assert(loaded.size() == 2);
    assert(loaded[0].id == 1);
    assert(loaded[1].completed == true);
    
    std::remove(testfile);
    std::cout << "All todo tests passed\n";
    return 0;
}
