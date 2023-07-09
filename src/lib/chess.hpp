#ifndef CHESS_HPP
#define CHESS_HPP

#include <string>
#include <iostream>

class Piece {
    public:
        std::string uni = " "; // Char that represent piece at chessboard
        int type = 0; // Type of piece
        int color; // Color of piece
        bool attack_king = 0; // If attacking king -> 1, of not -> 0

};

class Field {
    public:
        bool occupied;
        Piece piece;
};

void print_chessboard(Field chess_brd[8][8]);

#endif