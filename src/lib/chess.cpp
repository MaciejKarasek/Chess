#include "chess.hpp"

// Piece obj
Piece::Piece() {
    uni = " ";
    type = 0;
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
    }
}
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
    }
}
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
// End of Board obj
