#include <cassert>
#include <cmath>
#include <iostream>

double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b) { return a / b; }
double modulo(double a, double b) { return std::fmod(a, b); }

int main() {
    assert(add(2, 3) == 5);
    assert(subtract(5, 3) == 2);
    assert(multiply(4, 3) == 12);
    assert(divide(10, 2) == 5);
    assert(modulo(10, 3) == 1);
    
    // Division by zero returns inf
    assert(std::isinf(divide(1, 0)));
    
    std::cout << "All calculator tests passed\n";
    return 0;
}
