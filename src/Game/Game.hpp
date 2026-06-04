#include "Board.hpp"

// Main game function
class Game
{
    public:
        void Play();
        int HandleMove(std::string move, std::string where, Board *board, int who);
    private:
        void PrintInstructions();
        const std::wstring_view Instructions = L"Welcome, to play, type moves by typing coordinates of piece that you want to move and coordinates of field where do you want to place your piece\
                                                Example: \"Type your move: e2 e4\"";
};