#include "game.hpp"

// Main game function
void game() {
    Board *board;
    board = new Board;
    std::cout << "Welcome, to play, type moves by typing ";
    std::cout << "coordinates of piece that you want to ";
    std::cout << "move and coordinates of field where do ";
    std::cout << "you want to place your piece\n";
    std::cout << "Example: \"Type your move: e2 e4\" \n";
    bool checkmate = 0;
    std::string who_moves[2] = {"White ", "Black "};
    int error, who = 0;
    while (checkmate == 0) {
        std::cout << who_moves[who] << "move!" << std::endl;
        board->print();
        std::string move, where;
        std::cout << "Type your move: ";
        std::cin >> move >> where;
        std::cout << std::endl;
        if (move.length() != 2 || where.length() != 2) {
            std::cout << "Wrong move, try again\n";
            continue;
        }
        error = handle_move(move, where, board);
        if (error == 1) {
            std::cout << "Wrong move, try again\n";
            continue;
        }
        who = (who == 0) ? 1 : 0;
    }
}

int handle_move(std::string move, std::string where, Board *board) {
    std::cout << move << where << std::endl;
    return 1;
}