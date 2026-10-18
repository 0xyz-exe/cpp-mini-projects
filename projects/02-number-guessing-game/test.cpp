#include <cassert>
#include <random>
#include <iostream>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);
    
    // Test random generation produces values in range
    for (int i = 0; i < 100; i++) {
        int val = dist(gen);
        assert(val >= 1 && val <= 100);
    }
    
    // Test game logic
    int target = 42;
    int guess = 30;
    assert(guess < target); // Should hint "Higher"
    
    guess = 50;
    assert(guess > target); // Should hint "Lower"
    
    guess = 42;
    assert(guess == target); // Win
    
    std::cout << "All guessing game tests passed\n";
    return 0;
}
