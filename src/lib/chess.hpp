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
        bool fst_move; // Piece has been already moved once -> else -> 0
        void setvalues(int tp, int cr);
        ~Piece();

};

class Field {
    public:
        Field();
        bool occupied; // 1 -> Piece standing on field, else -> 0
        Piece piece;
        void setvalues(int tp, int cr);
        ~Field();
};

class Board {
    public:
        Board();
        void print();
        Field brd[8][8]; // Chessboard
        ~Board();
};


#endif