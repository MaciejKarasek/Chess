#include "Piece.hpp"

Piece::Piece() {
    uni = L' ';
    type = 0;
    num_moves = 0;
    color = 0;
}
void Piece::setvalues(int tp, int cr) // tp stands for type, cr for color
{
    std::vector <std::vector<std::wstring>> pieces{
        {L" ", L"♟", L"♞", L"♝", L"♜", L"♛", L"♚"},
        {L" ", L"♙", L"♘", L"♗", L"♖", L"♕", L"♔"}};

    num_moves = 0;
    type = tp;
    color = cr;
    if (color != -1) {
        uni = pieces[color][type];
    } else uni = L' ';
}

void Piece::setvalues(const Piece& other) {
    uni = other.uni;
    type = other.type;
    color = other.color;
    num_moves = other.num_moves;
}

void Piece::changetype(int tp) {
    std::vector<std::wstring> uni_white{ L"♘", L"♗", L"♖", L"♕" };
    std::vector<std::wstring> uni_black{ L"♞", L"♝", L"♜", L"♛" };
    type = tp;
    if (color == 1) {
        uni = uni_white[tp - 2];
    } else {
        uni = uni_black[tp - 2];
    }
}

Piece::~Piece() = default;