#include "game.hpp"

// Main game function
void game() {
    Board *board;
    board = new Board;
    int error, possible, material, who = 1;
    std::wcout << L"Welcome, to play, type moves by typing ";
    std::wcout << L"coordinates of piece that you want to ";
    std::wcout << L"move and coordinates of field where do ";
    std::wcout << L"you want to place your piece\n";
    std::wcout << L"Example: \"Type your move: e2 e4\" \n";
    std::vector<std::wstring> who_moves = { L"Black ", L"White " };
    //board->brd[6][4].piece.uni = "E";
    while (true) {
        std::wcout << who_moves[who] << L"move!" << std::endl;
        board->print();
        possible = board->possible(who);
        material = board->material();
        if (material == 2) {
            std::wcout << L"Game ended!" << std::endl;
            std::wcout << L"Not enought material, Draw!" << std::endl;
            break;
        }
        std::wcout << std::endl;
        if (possible == 0) {
            std::wcout << "Game ended!" << std::endl;
            if (board->attack(board->brd, who)) {
                who = (who == 1) ? 0 : 1;
                std::wcout << who_moves[who] << "won!" << std::endl;
            } else {
                std::wcout << "Draw!" << std::endl;
            }
            break;
        }
        std::string move, where;
        std::wcout << L"Type your move: ";
        std::cin >> move >> where;
        std::wcout << std::endl;
        if (move.length() != 2 || where.length() != 2) {
            std::wcout << L"Wrong move, try again\n";
            continue;
        }
        error = handle_move(move, where, board, who);
        if (error == 1) {
            std::wcout << L"Wrong move, try again\n";
            continue;
        }
        who = (who == 0) ? 1 : 0;
    }
    delete board;
}

int handle_move(std::string move, std::string where, Board *board, int who) {
    std::vector<int> move_arr{0, 0, 0, 0};
    std::map<char, int> char_to_int{{'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, 
                                    {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7}};
    std::map<char, int>::iterator mp_iter;
    if (!isalpha(move[0]) || !isalpha(where[0]) || !isdigit(move[1]) || !isdigit(where[1])) return 1;

    move_arr[0] = 8 - ((move[1] - '0')); // Converting to integer
    move_arr[2] = 8 - ((where[1] - '0'));

    if (move_arr[0] < 0 || move_arr[0] > 7 ||
        move_arr[2] < 0 || move_arr[2] > 7) return 1; // If out of range <0, 7> return 1 -> wrong move
    
    mp_iter = char_to_int.find(tolower(move[0])); // If out of range <a, h> return 1
    if (mp_iter == char_to_int.end()) return 1;
    move_arr[1] = mp_iter->second;

    mp_iter = char_to_int.find(tolower(where[0])); // If out of range <a, h> return 1
    if (mp_iter == char_to_int.end()) return 1;
    move_arr[3] = mp_iter->second;
    // std::wcout << move_arr[0] <<move_arr[1] << move_arr[2] << move_arr[3] << std::endl;
    return board->move(move_arr, who);
    }