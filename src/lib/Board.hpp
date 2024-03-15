#ifndef BOARD_HPP
#define BOARD_HPP

#ifndef LIBARIES
#define LIBARIES
#include <string>
#include <iostream>
#include <vector>
#include <map>
#endif // LIBARIES

#include "Field.hpp"

class Board {
    public:
        bool white_attack; // Attack on White king
        bool black_attack; // Attack on Black king
        Board(); // Default constructor
        void print();
        int move(std::vector<int> &arr, int who);
        int check_move(int who, 
                       int type, 
                       Field& move, 
                       Field& where, 
                       std::vector<int> &cords);
        bool attack(std::vector <std::vector<Field>> &bord, int who);
        void check();
        int possible(int who);
        void setvalues(std::vector <std::vector<Field>> &brd);
        int material();
        std::vector <std::vector<Field>> brd = {8, std::vector<Field>(8, Field())};
        ~Board();
    private:
        std::vector <std::vector<Field>> brd_cpy = {8, std::vector<Field>(8, Field())};
        int last[2]; // Coordinates of last moved piece
        int last_moved;
        Field save[3]; // 0 en passant
};
#endif // BORARD