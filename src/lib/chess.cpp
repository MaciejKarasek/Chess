#include "chess.hpp"

// Piece obj
Piece::Piece() {
    uni = " ";
    type = 0;
    num_moves = 0;
}
void Piece::setvalues(int tp, int cr) // tp stands for type, cr for color
{
    num_moves = 0;
    if (cr == 1) {
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
    } else if (cr == 0) {
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
    color = other.color;
    num_moves = other.num_moves + 1;
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
            brd[0][i].setvalues(4, 0);
            brd[1][i].setvalues(1, 0);
            brd[0][7 - i].setvalues(4, 0);
            brd[1][7 - i].setvalues(1, 0);

            brd[7][i].setvalues(4, 1);
            brd[6][i].setvalues(1, 1);
            brd[7][7 - i].setvalues(4, 1);
            brd[6][7 - i].setvalues(1, 1);
            break;
        case 1:
            brd[0][i].setvalues(2, 0);
            brd[1][i].setvalues(1, 0);
            brd[0][7 - i].setvalues(2, 0);
            brd[1][7 - i].setvalues(1, 0);

            brd[7][i].setvalues(2, 1);
            brd[6][i].setvalues(1, 1);
            brd[7][7 - i].setvalues(2, 1);
            brd[6][7 - i].setvalues(1, 1);
            break;
        case 2:
            brd[0][i].setvalues(3, 0);
            brd[1][i].setvalues(1, 0);
            brd[0][7 - i].setvalues(3, 0);
            brd[1][7 - i].setvalues(1, 0);

            brd[7][i].setvalues(3, 1);
            brd[6][i].setvalues(1, 1);
            brd[7][7 - i].setvalues(3, 1);
            brd[6][7 - i].setvalues(1, 1);
            break;
        case 3:
            brd[0][i].setvalues(5, 0);
            brd[1][i].setvalues(1, 0);
            brd[0][7 - i].setvalues(6, 0);
            brd[1][7 - i].setvalues(1, 0);

            brd[7][i].setvalues(5, 1);
            brd[6][i].setvalues(1, 1);
            brd[7][7 - i].setvalues(6, 1);
            brd[6][7 - i].setvalues(1, 1);
            break;
        }
    }
    last[0] = -1;
    last[1] = -1;
    last_moved = 0;
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
    int check;
    if (move.occupied == 1 && move.piece.color == who) {
        switch(move.piece.type) {
            case 1:
                check = check_move(who, 1, move, where, brd, arr, last, last_moved);
                if (check) {
                    where.setvalues(move);
                    move.setvalues(0, -1);
                    if (check == 2) {
                    if (who == 1) { brd[arr[2] + 1][arr[3]].setvalues(0, -1); }
                    else { brd[arr[2] - 1][arr[3]].setvalues(0, -1); }
                    }
                    last[0] = arr[2];
                    last[1] = arr[3];
                    last_moved = where.piece.num_moves;
                    return 0;
                }
                break;
            /**case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;**/
            default:
                return 0;
                break;
        }
        }
    return 1;
}

Board::~Board() = default;
// End of Board obj

// Functions
int check_move(int who, int type, Field& move, Field& where, 
                Field brd[8][8], int cords[4], int last[2], int last_moved) {
    Field where2;
    if (type == 1 && who == 0 && cords[2] + 1 < 8) {
        where2 = brd[cords[2] - 1][cords[3]];
    }
    else if (type == 1 && who == 1 && cords[2] - 1 > 0)
    {
        where2 = brd[cords[2] + 1][cords[3]];
    }
    
    
    switch (type) {
        case 1:
            if (who == 1) {
            if ((cords[1] == (cords[3] - 1) || cords[1] == (cords[3] + 1)) 
                && cords[0] == (cords[2] + 1) 
                && where.occupied && where.piece.color == 0) {
                return 1;
            }
            // En passant
            if ((cords[1] == (cords[3] - 1) || cords[1] == (cords[3] + 1))
                && cords[0] == (cords[2] + 1)
                && where2.occupied == 1 && where2.piece.color == 0 
                && last[0] == (cords[2] + 1) && last[1] == cords[3]
                && last_moved == 1 && last[0] == 3) {
                return 2;
                }
            if (cords[1] == cords[3] && cords[0] == (cords[2] + 1)
                && !where.occupied) {
                return 1;
            }
            if (cords[1] == cords[3] && cords[0] == (cords[2] + 2)
                && !(brd[cords[2] + 1][cords[3]].occupied == 1)
                && !(where.occupied == 1)
                && move.piece.num_moves == 0) {
                return 1;
                }
            else {
                std::cout << "elow" << std::endl;
                return 0;
            }
            } else {
            if ((cords[1] == (cords[3] - 1) || cords[1] == (cords[3] + 1)) 
                && cords[0] == (cords[2] - 1) 
                && where.occupied == 1 && where.piece.color == 1) {
                return 1;
            }
            // En passant
            if ((cords[1] == (cords[3] - 1) || cords[1] == (cords[3] + 1))
                && cords[0] == (cords[2] - 1)
                && where2.occupied == 1 && where2.piece.color == 1 
                && last[0] == (cords[2] - 1) && last[1] == cords[3]
                && last_moved == 1 && last[0] == 4) {
                return 2;
                }
            if (cords[1] == cords[3] && cords[0] == (cords[2] - 1)
                && !(where.occupied == 1)) {
                return 1;
            }
            if (cords[1] == cords[3] && cords[0] == (cords[2] - 2)
                && !(brd[cords[2] - 1][cords[3]].occupied == 1)
                && !(where.occupied == 1)
                && move.piece.num_moves == 0) {
                return 1;
                }
            else {
                std::cout << "elob" << std::endl;
                return 0;
            }
            }

            break;
        /**case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;**/
        default:
            return 0;
            break;
        }
    return 0;
}
