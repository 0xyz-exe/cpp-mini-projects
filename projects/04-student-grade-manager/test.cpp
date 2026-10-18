#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Student {
    std::string id;
    std::string name;
    double grade;
};

double calc_average(const std::vector<Student>& students) {
    if (students.empty()) return 0.0;
    double sum = 0;
    for (const auto& s : students) sum += s.grade;
    return sum / students.size();
}

int main() {
    std::vector<Student> students = {
        {"S001", "Alice", 85.5},
        {"S002", "Bob", 92.0},
        {"S003", "Charlie", 78.5}
    };
    
    double avg = calc_average(students);
    assert(avg > 85.3 && avg < 85.4);
    
    // Test sorting
    std::sort(students.begin(), students.end(), 
              [](const Student& a, const Student& b) { return a.grade > b.grade; });
    assert(students[0].name == "Bob");
    
    // Test search
    auto it = std::find_if(students.begin(), students.end(),
                          [](const Student& s) { return s.id == "S001"; });
    assert(it != students.end());
    assert(it->name == "Alice");
    
    std::cout << "All student manager tests passed\n";
    return 0;
}
