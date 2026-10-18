#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

struct Task {
    int id;
    std::string description;
    char priority; // H, M, L
    bool completed;
};

std::vector<Task> load_tasks(const std::string& filename) {
    std::vector<Task> tasks;
    std::ifstream file(filename);
    if (!file) return tasks;
    
    Task t;
    while (file >> t.id) {
        file.ignore();
        std::getline(file, t.description, '|');
        file >> t.priority;
        file >> t.completed;
        file.ignore();
        tasks.push_back(t);
    }
    return tasks;
}

void save_tasks(const std::vector<Task>& tasks, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& t : tasks) {
        file << t.id << "\n" << t.description << "|\n" 
             << t.priority << " " << t.completed << "\n";
    }
}

int main() {
    const std::string filename = "tasks.dat";
    std::vector<Task> tasks = load_tasks(filename);
    int next_id = 1;
    for (const auto& t : tasks) {
        if (t.id >= next_id) next_id = t.id + 1;
    }
    
    int choice;
    
    while (true) {
        std::cout << "\n=== To-Do List ===\n";
        std::cout << "1. Add task\n2. List tasks\n3. Complete task\n4. Delete task\n5. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        std::cin.ignore();
        
        if (choice == 1) {
            Task t;
            t.id = next_id++;
            std::cout << "Description: ";
            std::getline(std::cin, t.description);
            std::cout << "Priority (H/M/L): ";
            std::cin >> t.priority;
            t.completed = false;
            tasks.push_back(t);
            save_tasks(tasks, filename);
            std::cout << "Task added with ID " << t.id << "\n";
            
        } else if (choice == 2) {
            for (const auto& t : tasks) {
                std::cout << "[" << t.id << "] " << (t.completed ? "[✓] " : "[ ] ")
                         << t.description << " (Priority: " << t.priority << ")\n";
            }
            
        } else if (choice == 3) {
            int id;
            std::cout << "Task ID to complete: ";
            std::cin >> id;
            bool found = false;
            for (auto& t : tasks) {
                if (t.id == id) {
                    t.completed = true;
                    found = true;
                    break;
                }
            }
            if (found) {
                save_tasks(tasks, filename);
                std::cout << "Task marked complete\n";
            } else {
                std::cout << "Task not found\n";
            }
            
        } else if (choice == 4) {
            int id;
            std::cout << "Task ID to delete: ";
            std::cin >> id;
            auto it = tasks.begin();
            bool found = false;
            while (it != tasks.end()) {
                if (it->id == id) {
                    tasks.erase(it);
                    found = true;
                    break;
                }
                ++it;
            }
            if (found) {
                save_tasks(tasks, filename);
                std::cout << "Task deleted\n";
            } else {
                std::cout << "Task not found\n";
            }
            
        } else if (choice == 5) {
            break;
        }
    }
    
    return 0;
}
