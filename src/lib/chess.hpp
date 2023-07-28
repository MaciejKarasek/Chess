#ifndef CHESS_HPP
#define CHESS_HPP

#include <string>
#include <iostream>
#include <vector>

class Piece {
    public:
        Piece();
        std::string uni; // Char that represent piece at chessboard
        int type; // Type of piece
        int color; // Color of piece 0 - Black, 1 - White
        int num_moves; // number of moves
        void setvalues(int tp, int cr);
        void setvalues(const Piece& other);
        void changetype(int type);
        ~Piece();

};

class Field {
    public:
        Field();
        bool occupied; // 1 -> Piece standing on field, else -> 0
        Piece piece;
        void setvalues(int tp, int cr);
        void setvalues(const Field& other);
        ~Field();
};

class Board {
    public:
        bool white_attack; // Attack on White king
        bool black_attack; // Attack on Black king
        Board(); // Default constructor
        void print();
        int move(int arr[4], int who);
        int check_move(int who, int type, Field& move, Field& where, int cords[4]);
        bool attack(Field bord[8][8], int who);
        void check();
        int possible(int who);
        void setvalues(Field brd[8][8]);
        int material();
        Field brd[8][8]; // Chessboard
        ~Board();
    private:
        Field brd_cpy[8][8]; // Chessboard copy
        int last[2]; // Coordinates of last moved piece
        int last_moved;
        Field save[3]; // 0 en passant
};

#endif