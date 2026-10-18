#include <iostream>
#include <random>
#include <limits>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    char play_again;
    
    do {
        int difficulty;
        std::cout << "\n=== Number Guessing Game ===\n";
        std::cout << "Select difficulty:\n1. Easy (1-50)\n2. Medium (1-100)\n3. Hard (1-200)\n";
        std::cout << "Choice: ";
        std::cin >> difficulty;
        
        if (std::cin.fail() || difficulty < 1 || difficulty > 3) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice, using Medium\n";
            difficulty = 2;
        }
        
        int max_val = (difficulty == 1) ? 50 : (difficulty == 2) ? 100 : 200;
        std::uniform_int_distribution<> dist(1, max_val);
        int target = dist(gen);
        int attempts = 0;
        int guess;
        
        std::cout << "Guess the number between 1 and " << max_val << "\n";
        
        while (true) {
            std::cout << "Enter guess: ";
            std::cin >> guess;
            
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input\n";
                continue;
            }
            
            attempts++;
            
            if (guess == target) {
                std::cout << "Correct! You won in " << attempts << " attempts\n";
                break;
            } else if (guess < target) {
                std::cout << "Higher!\n";
            } else {
                std::cout << "Lower!\n";
            }
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Play again? (y/n): ";
        std::cin >> play_again;
        
    } while (play_again == 'y' || play_again == 'Y');
    
    return 0;
}
