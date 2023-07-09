#ifndef CHESS_HPP
#define CHESS_HPP

#include <string>
#include <iostream>

class Piece {
    public:
        Piece();
        std::string uni; // Char that represent piece at chessboard
        int type; // Type of piece
        int color; // Color of piece
        bool attack_king; // If attacking king -> 1, of not -> 0
        void setvalues(int tp, int cr);

};

class Field {
    public:
        Field();
        bool occupied;
        Piece piece;
        void setvalues(int tp, int cr);
};

class Board {
    public:
        Board();
        void print();
        Field brd[8][8];
};


#endif