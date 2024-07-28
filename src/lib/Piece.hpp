#ifndef PIECE_HPP
#define PIECE_HPP

#ifndef LIBARIES
#define LIBARIES
#include <string>
#include <iostream>
#include <vector>
#include <map>
#endif // LIBARIES

class Piece {
    public:
        Piece();
        std::wstring uni; // Char that represent piece at chessboard
        int type; // Type of piece
        int color; // Color of piece 0 - Black, 1 - White
        int num_moves; // number of moves
        void setvalues(int tp, int cr);
        void setvalues(const Piece& other);
        void changetype(int type);
        ~Piece();

};

#endif // PIECE_HPP