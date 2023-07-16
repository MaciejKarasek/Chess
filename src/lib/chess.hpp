#ifndef CHESS_HPP
#define CHESS_HPP

#include <string>
#include <iostream>

class Piece {
    public:
        Piece();
        std::string uni; // Char that represent piece at chessboard
        int type; // Type of piece
        int color; // Color of piece 0 - Black, 1 - White
        bool attack_king; // If attacking king -> 1, of not -> 0
        int num_moves; // number of moves
        void setvalues(int tp, int cr);
        void setvalues(const Piece& other);
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
        void print_attack(); //debuging
        int move(int arr[4], int who);
        int check_move(int who, int type, Field& move, Field& where, int cords[4]);
        void attack();
        void check();
        ~Board();
    private:
        Field brd[8][8]; // Chessboard
        int last[2]; // Coordinates of last moved piece
        int last_moved;
        bool attacked[8][8]; // Fields under attack
};

#endif