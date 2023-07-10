#include "chess.hpp"

// Piece obj
Piece::Piece() {
    uni = " ";
    type = 0;
    fst_move = 0;
}
void Piece::setvalues(int tp, int cr) // tp stands for type, cr for color
{
    if (cr == 0) {
        type = tp;
        color = cr;
        switch(type) {
        case 1:
            uni = "♙";
            break;
        case 2:
            uni = "♘";
            break;
        case 3:
            uni = "♗";
            break;
        case 4:
            uni = "♖";
            break;
        case 5:
            uni = "♕";
            break;
        case 6:
            uni = "♔";
            break;
        default:
            uni = " ";
            break;
        }
    } else if (cr == 1) {
        type = tp;
        color = cr;
        switch(type) {
        case 1:
            uni = "♟";
            break;
        case 2:
            uni = "♞";
            break;
        case 3:
            uni = "♝";
            break;
        case 4:
            uni = "♜";
            break;
        case 5:
            uni = "♛";
            break;
        case 6:
            uni = "♚";
            break;
        default:
            uni = " ";
            break;
        }
    } else {
        type = 0;
        uni = " ";
        color = cr;
    }
}

void Piece::setvalues(const Piece& other) {
    uni = other.uni;
    type = other.type;
    color = other.type;
    fst_move = 1;
}

Piece::~Piece() = default;
// End of Piece obj

// Field obj
Field::Field() 
{
    occupied = 0;
}

void Field::setvalues(int tp, int cr) 
{
    if (tp != 0) {
        occupied = 1; 
        piece.setvalues(tp, cr);
    } else {
        occupied = 0;
        piece.setvalues(tp, cr);
    }
}

void Field::setvalues(const Field& other) 
{
    occupied = 1;
    piece.setvalues(other.piece);
}

Field::~Field() = default;
// End of Field obj

// Board obj
Board::Board() {
    for (int i = 0; i < 4; i++) {
        switch(i) {
        case 0:
            brd[0][i].setvalues(4, 1);
            brd[1][i].setvalues(1, 1);
            brd[0][7 - i].setvalues(4, 1);
            brd[1][7 - i].setvalues(1, 1);

            brd[7][i].setvalues(4, 0);
            brd[6][i].setvalues(1, 0);
            brd[7][7 - i].setvalues(4, 0);
            brd[6][7 - i].setvalues(1, 0);
            break;
        case 1:
            brd[0][i].setvalues(2, 1);
            brd[1][i].setvalues(1, 1);
            brd[0][7 - i].setvalues(2, 1);
            brd[1][7 - i].setvalues(1, 1);

            brd[7][i].setvalues(2, 0);
            brd[6][i].setvalues(1, 0);
            brd[7][7 - i].setvalues(2, 0);
            brd[6][7 - i].setvalues(1, 0);
            break;
        case 2:
            brd[0][i].setvalues(3, 1);
            brd[1][i].setvalues(1, 1);
            brd[0][7 - i].setvalues(3, 1);
            brd[1][7 - i].setvalues(1, 1);

            brd[7][i].setvalues(3, 0);
            brd[6][i].setvalues(1, 0);
            brd[7][7 - i].setvalues(3, 0);
            brd[6][7 - i].setvalues(1, 0);
            break;
        case 3:
            brd[0][i].setvalues(5, 1);
            brd[1][i].setvalues(1, 1);
            brd[0][7 - i].setvalues(6, 1);
            brd[1][7 - i].setvalues(1, 1);

            brd[7][i].setvalues(5, 0);
            brd[6][i].setvalues(1, 0);
            brd[7][7 - i].setvalues(6, 0);
            brd[6][7 - i].setvalues(1, 0);
            break;
        }
    }
}

void Board::print() {
    std::string separator = "---+---+---+---+---+---+---+---+---+";
    for (int i = 0; i < 9; i++) {
        if (i == 0) {
            std::cout << "   | A | B | C | D | E | F | G | H |" << std::endl;
            std::cout<< separator << std::endl;
        }
        else {
            printf(" %i |", 9 - i);
            for (int j = 0; j < 8; j++){
                std::cout << " " << brd[i - 1][j].piece.uni << " |";
            }
            std::cout << std::endl << separator << std::endl;
        }   
    }
}

int Board::move(int arr[4], int who) {
    // Aliases
    Field& move = brd[arr[0]][arr[1]];
    Field& where = brd[arr[2]][arr[3]];
    if (move.occupied && move.piece.color == who) {
        if (!(where.occupied)) {
            switch(move.piece.type) {
                case 1:
                    if (move.piece.fst_move == 0) {
                        if (arr[1] == arr[3] && (arr[0] == (arr[2] + 1) || arr[0] == (arr[2] + 2))) {
                            where.setvalues(move);
                            move.setvalues(0, -1);
                            return 0;
                        }
                    }
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                default:
                    break;
            }
        }
    }
    return 1;
}

Board::~Board() = default;
// End of Board obj