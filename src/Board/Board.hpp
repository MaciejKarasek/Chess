#include <string>
#include <memory>

#include "Field.hpp"

class Board {
    public:
        bool white_attack;
        bool black_attack;
        Board();
        void print();
        Field at(const std::wstring_view chessCoords) const;
        int move(std::vector<int> &arr, int who);
        int check_move(int who, 
                       int type, 
                       Field& move, 
                       Field& where, 
                       std::vector<int> &cords);
        bool attack(std::vector <std::vector<Field>> &bord, int who);
        int possible(int who);
        void setvalues(std::vector <std::vector<Field>> &brd);
        int material();
        std::unique_ptr<Field> board[8][8];
        ~Board();
    private:
        std::unique_ptr<Field> boardCopy[8][8];
        int last[2]; // Coordinates of last moved piece
        int last_moved;
        Field save[3]; // 0 en passant
};