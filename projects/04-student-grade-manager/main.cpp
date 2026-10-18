#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iomanip>

struct Student {
    std::string id;
    std::string name;
    double grade;
};

void add_student(std::vector<Student>& students) {
    Student s;
    std::cout << "Student ID: ";
    std::cin >> s.id;
    std::cin.ignore();
    std::cout << "Name: ";
    std::getline(std::cin, s.name);
    std::cout << "Grade (0-100): ";
    std::cin >> s.grade;
    
    if (s.grade < 0 || s.grade > 100) {
        std::cout << "Invalid grade\n";
        return;
    }
    students.push_back(s);
    std::cout << "Student added\n";
}

void list_students(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "No students\n";
        return;
    }
    std::cout << "\n" << std::left << std::setw(10) << "ID" 
              << std::setw(20) << "Name" << "Grade\n";
    std::cout << std::string(40, '-') << "\n";
    for (const auto& s : students) {
        std::cout << std::setw(10) << s.id << std::setw(20) << s.name 
                  << std::fixed << std::setprecision(2) << s.grade << "\n";
    }
}

void search_student(const std::vector<Student>& students) {
    std::string id;
    std::cout << "Student ID: ";
    std::cin >> id;
    
    auto it = std::find_if(students.begin(), students.end(),
                          [&id](const Student& s) { return s.id == id; });
    if (it != students.end()) {
        std::cout << "Found: " << it->name << ", Grade: " << it->grade << "\n";
    } else {
        std::cout << "Student not found\n";
    }
}

void calc_average(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "No students\n";
        return;
    }
    double sum = 0;
    for (const auto& s : students) sum += s.grade;
    std::cout << "Average grade: " << std::fixed << std::setprecision(2) 
              << sum / students.size() << "\n";
}

void export_csv(const std::vector<Student>& students) {
    std::ofstream file("students.csv");
    file << "ID,Name,Grade\n";
    for (const auto& s : students) {
        file << s.id << "," << s.name << "," << s.grade << "\n";
    }
    file.close();
    std::cout << "Exported to students.csv\n";
}

int main() {
    std::vector<Student> students;
    int choice;
    
    while (true) {
        std::cout << "\n=== Student Grade Manager ===\n";
        std::cout << "1. Add student\n2. List all\n3. Search\n4. Average\n5. Export CSV\n6. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        
        switch (choice) {
            case 1: add_student(students); break;
            case 2: list_students(students); break;
            case 3: search_student(students); break;
            case 4: calc_average(students); break;
            case 5: export_csv(students); break;
            case 6: return 0;
            default: std::cout << "Invalid choice\n";
        }
    }
}
