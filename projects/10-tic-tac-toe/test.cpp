#include <cassert>
#include <iostream>
#include <array>

class TicTacToe {
    std::array<char, 9> board;
    char current_player;
    
public:
    TicTacToe() : current_player('X') { board.fill(' '); }
    
    bool make_move(int pos) {
        if (pos < 1 || pos > 9 || board[pos-1] != ' ') return false;
        board[pos-1] = current_player;
        return true;
    }
    
    char check_winner() const {
        const int wins[8][3] = {
            {0,1,2}, {3,4,5}, {6,7,8},
            {0,3,6}, {1,4,7}, {2,5,8},
            {0,4,8}, {2,4,6}
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
        for (char c : board) if (c == ' ') return false;
        return true;
    }
    
    void switch_player() { current_player = (current_player == 'X') ? 'O' : 'X'; }
    char get_current_player() const { return current_player; }
};

int main() {
    TicTacToe game;
    
    // Test horizontal win
    assert(game.make_move(1)); // X
    game.switch_player();
    assert(game.make_move(4)); // O
    game.switch_player();
    assert(game.make_move(2)); // X
    game.switch_player();
    assert(game.make_move(5)); // O
    game.switch_player();
    assert(game.make_move(3)); // X wins
    assert(game.check_winner() == 'X');
    
    // Test draw
    TicTacToe game2;
    int moves[] = {1,2,3,5,4,7,6,9,8};
    for (int m : moves) {
        game2.make_move(m);
        game2.switch_player();
    }
    assert(game2.is_full());
    assert(game2.check_winner() == ' ');
    
    // Test invalid move
    TicTacToe game3;
    game3.make_move(1);
    assert(!game3.make_move(1)); // Same position
    
    std::cout << "All tic-tac-toe tests passed\n";
    return 0;
}
