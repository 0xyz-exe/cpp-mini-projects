#include <iostream>
#include <array>

class TicTacToe {
    std::array<char, 9> board;
    char current_player;
    
public:
    TicTacToe() : current_player('X') {
        board.fill(' ');
    }
    
    void display() const {
        std::cout << "\n";
        for (int i = 0; i < 9; i += 3) {
            std::cout << " " << board[i] << " | " << board[i+1] << " | " << board[i+2] << "\n";
            if (i < 6) std::cout << "---+---+---\n";
        }
        std::cout << "\n";
    }
    
    bool make_move(int pos) {
        if (pos < 1 || pos > 9 || board[pos-1] != ' ') return false;
        board[pos-1] = current_player;
        return true;
    }
    
    char check_winner() const {
        const int wins[8][3] = {
            {0,1,2}, {3,4,5}, {6,7,8},  // rows
            {0,3,6}, {1,4,7}, {2,5,8},  // cols
            {0,4,8}, {2,4,6}            // diagonals
        };
        
        for (const auto& win : wins) {
            if (board[win[0]] != ' ' &&
                board[win[0]] == board[win[1]] &&
                board[win[1]] == board[win[2]]) {
                return board[win[0]];
            }
        }
        return ' ';
    }
    
    bool is_full() const {
        for (char c : board) {
            if (c == ' ') return false;
        }
        return true;
    }
    
    void switch_player() {
        current_player = (current_player == 'X') ? 'O' : 'X';
    }
    
    char get_current_player() const { return current_player; }
    void reset() { board.fill(' '); current_player = 'X'; }
};

int main() {
    TicTacToe game;
    
    std::cout << "=== Tic-Tac-Toe ===\n";
    std::cout << "Positions: 1-9 (top-left to bottom-right)\n";
    
    while (true) {
        game.display();
        
        int pos;
        std::cout << "Player " << game.get_current_player() << ", enter position (1-9): ";
        std::cin >> pos;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input\n";
            continue;
        }
        
        if (!game.make_move(pos)) {
            std::cout << "Invalid move\n";
            continue;
        }
        
        char winner = game.check_winner();
        if (winner != ' ') {
            game.display();
            std::cout << "Player " << winner << " wins!\n";
            break;
        }
        
        if (game.is_full()) {
            game.display();
            std::cout << "Draw!\n";
            break;
        }
        
        game.switch_player();
    }
    
    return 0;
}
