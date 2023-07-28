#include "game.hpp"

// Main game function
void game() {
    Board *board;
    board = new Board;
    int error, possible, material, who = 1;
    std::cout << "Welcome, to play, type moves by typing ";
    std::cout << "coordinates of piece that you want to ";
    std::cout << "move and coordinates of field where do ";
    std::cout << "you want to place your piece\n";
    std::cout << "Example: \"Type your move: e2 e4\" \n";
    std::string who_moves[2] = {"Black ", "White "};
    //board->brd[6][4].piece.uni = "E";
    while (true) {
        std::cout << who_moves[who] << "move!" << std::endl;
        board->print();
        possible = board->possible(who);
        material = board->material();
        if (material == 2) {
            std::cout << "Game ended!" << std::endl;
            std::cout << "Not enought material, Draw!" << std::endl;
            break;
        }
        std::cout << std::endl;
        if (possible == 0) {
            std::cout << "Game ended!" << std::endl;
            if (board->attack(board->brd, who)) {
                who = (who == 1) ? 0 : 1;
                std::cout << who_moves[who] << "won!" << std::endl;
            } else {
                std::cout << "Draw!" << std::endl;
            }
            break;
        }
        std::string move, where;
        std::cout << "Type your move: ";
        std::cin >> move >> where;
        std::cout << std::endl;
        if (move.length() != 2 || where.length() != 2) {
            std::cout << "Wrong move, try again\n";
            continue;
        }
        error = handle_move(move, where, board, who);
        if (error == 1) {
            std::cout << "Wrong move, try again\n";
            continue;
        }
        who = (who == 0) ? 1 : 0;
    }
}

int handle_move(std::string move, std::string where, Board *board, int who) {
    int move_arr[4] = {0, 0, 0, 0};
    if (isalpha(move[0]) && isalpha(where[0]) && isdigit(move[1]) && isdigit(where[1]))
    {
        move_arr[0] = 8 - ((move[1] - '0')); // Converting to 
        move_arr[2] = 8 - ((where[1] - '0'));
        if (!(move_arr[1] == std::clamp(move_arr[1], 0, 7)) 
            || !(move_arr[3] == std::clamp(move_arr[3], 0, 7)))
            { return 1; }
        switch (tolower(move[0])) {
            case 'a':
                move_arr[1] = 0;
                break;
            case 'b':
                move_arr[1] = 1;
                break;
            case 'c':
                move_arr[1] = 2;
                break;
            case 'd':
                move_arr[1] = 3;
                break;
            case 'e':
                move_arr[1] = 4;
                break;
            case 'f':
                move_arr[1] = 5;
                break;
            case 'g':
                move_arr[1] = 6;
                break;
            case 'h':
                move_arr[1] = 7;
                break;
            default:
                return 1;
                break;
        }
        switch (tolower(where[0])) {
            case 'a':
                move_arr[3] = 0;
                break;
            case 'b':
                move_arr[3] = 1;
                break;
            case 'c':
                move_arr[3] = 2;
                break;
            case 'd':
                move_arr[3] = 3;
                break;
            case 'e':
                move_arr[3] = 4;
                break;
            case 'f':
                move_arr[3] = 5;
                break;
            case 'g':
                move_arr[3] = 6;
                break;
            case 'h':
                move_arr[3] = 7;
                break;
            default:
                return 1;
                break;
        }
        // std::cout << move_arr[0] <<move_arr[1] << move_arr[2] << move_arr[3] << std::endl;
        return board->move(move_arr, who);
    }
    return 1;
}