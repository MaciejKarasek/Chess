#include "chess.hpp"

// Piece obj
Piece::Piece() {
    uni = " ";
    type = 0;
    num_moves = 0;
    color = -1;
}
void Piece::setvalues(int tp, int cr) // tp stands for type, cr for color
{
    num_moves = 0;
    type = tp;
    color = cr;
    if (cr == 1) {
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
    num_moves = other.num_moves;
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
    occupied = other.occupied;
    piece.setvalues(other.piece);
}

Field::~Field() = default;
// End of Field obj

// Board obj
Board::Board() {
    setvalues(brd);
    setvalues(brd_cpy);
    last[0] = -1;
    last[1] = -1;
    last_moved = 0;     
    white_attack = 0;
    black_attack = 0;
}

void Board::setvalues(Field brd[8][8]) {
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
    int check, king_attack, x, target_x;
    if (move.occupied == 1 && move.piece.color == who) {
        check = check_move(who, move.piece.type, move, where, arr);
        if (move.piece.type == 1) {
            if (check) {
                brd_cpy[arr[0]][arr[1]].setvalues(0, -1);
                brd_cpy[arr[2]][arr[3]].setvalues(move);
                if (check == 2) {
                if (who == 1) { 
                    save[0].setvalues(brd_cpy[arr[2] + 1][arr[3]]);
                    brd_cpy[arr[2] + 1][arr[3]].setvalues(0, -1); 
                    }
                else {
                    save[0].setvalues(brd_cpy[arr[2] - 1][arr[3]]);
                    brd_cpy[arr[2] - 1][arr[3]].setvalues(0, -1); 
                    }
                }
                king_attack = attack(brd_cpy, who);
                if (king_attack == 0) {
                    where.setvalues(move);
                    move.setvalues(0, -1);
                    where.piece.num_moves++;
                    if (check == 2) {
                    if (who == 1) { brd[arr[2] + 1][arr[3]].setvalues(0, -1); } 
                    else { brd[arr[2] - 1][arr[3]].setvalues(0, -1); }
                    }
                    last[0] = arr[2];
                    last[1] = arr[3];
                    last_moved = where.piece.num_moves;
                    return 0;
                } else {
                    brd_cpy[arr[0]][arr[1]].setvalues(move);
                    brd_cpy[arr[2]][arr[3]].setvalues(0, -1);
                    if (check == 2) {
                    if (who == 1) { brd_cpy[arr[2] + 1][arr[3]].setvalues(save[0]); }
                    else { brd_cpy[arr[2] - 1][arr[3]].setvalues(save[0]); }
                    }
                }
            }
        } else if (move.piece.type == 6 && check == 2){ // Castling
            if (attack(brd, who)) {
                return 1;
            }
            x = (arr[3] == 7) ? 1 : -1; 
            target_x = arr[1] + x;
           for (int k = 0; k < 2; k ++) {
                brd_cpy[arr[0]][target_x].setvalues(move);
                brd_cpy[arr[0]][arr[1]].setvalues(0, -1);
                if(attack(brd_cpy, who)) {
                    brd_cpy[arr[0]][target_x].setvalues(brd[arr[0]][target_x]);
                    brd_cpy[arr[0]][arr[1]].setvalues(move);
                    return 1;
                }
                brd_cpy[arr[0]][target_x].setvalues(brd[arr[0]][target_x]);
                brd_cpy[arr[0]][arr[1]].setvalues(move);
                target_x += x;
            }
            target_x -= x;
            move.piece.num_moves++;
            where.piece.num_moves++;
            brd[arr[0]][target_x].setvalues(move);
            brd[arr[0]][target_x - x].setvalues(where);
            brd_cpy[arr[0]][target_x].setvalues(move);
            brd_cpy[arr[0]][target_x - x].setvalues(where);
            move.setvalues(0, -1);
            where.setvalues(0, -1);
            brd_cpy[arr[0]][arr[1]].setvalues(0, -1);
            brd_cpy[arr[2]][arr[3]].setvalues(0, -1);
            last[0] = arr[0];
            last[1] = target_x;
            last_moved = brd[arr[0]][target_x].piece.num_moves;
            return 0;
        } else {
            if (check) {
                brd_cpy[arr[0]][arr[1]].setvalues(0, -1);
                brd_cpy[arr[2]][arr[3]].setvalues(move);
                king_attack = attack(brd_cpy, who);
                if (king_attack == 0) {
                    where.setvalues(move);
                    move.setvalues(0, -1);
                    where.piece.num_moves++;
                    last[0] = arr[2];
                    last[1] = arr[3];
                    last_moved = where.piece.num_moves;
                    return 0;
                } else {
                    brd_cpy[arr[0]][arr[1]].setvalues(brd[arr[0]][arr[1]]);
                    brd_cpy[arr[2]][arr[3]].setvalues(brd[arr[2]][arr[3]]);
                    return 1;
                }
            }     
        }
    }
return 1;
}

int Board::check_move(int who, int type, Field& move, Field& where, int cords[4]) {
    Field where2;
    int x, y, target_x, target_y;
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
                return 0;
            }
            }

            break;
        case 2:
            if ((abs(cords[0] - cords[2]) == 1 && abs(cords[1] - cords[3]) == 2)
                || (abs(cords[0] - cords[2]) == 2 && abs(cords[1] - cords[3]) == 1)) {
                if (!(where.occupied == 1)) { return 1; }
                else if (where.piece.color != move.piece.color) { return 1; }
                else { return 0; }
            } else { return 0; }
            break;
        case 3:
            if (abs(cords[0] - cords[2]) == abs(cords[1] - cords[3])) {
            x = (cords[3] > cords[1]) ? 1 : -1;
            y = (cords[2] > cords[0]) ? 1 : -1;
            target_x = cords[1] + x;
            target_y = cords[0] + y;
            while (abs(target_x - cords[3]) >= 1) {
                if (brd[target_y][target_x].occupied == 1) { return 0; }
                target_x += x;
                target_y += y;
            }
            if ((where.occupied == 1 && where.piece.color != who)
                || (where.occupied == 0)) {
                    return 1;
                } else { return 0; }
            } else { return 0; }
            break;
        case 4:
            if (cords[0] == cords[2] || cords[1] == cords[3]) {
            x = (cords[3] > cords[1]) ? 1 : -1;
            y = (cords[2] > cords[0]) ? 1 : -1;
            if (cords[1] != cords[3]) {
                target_x = cords[1] + x;
                while (abs(target_x - cords[3]) >= 1) {
                    if (brd[cords[2]][target_x].occupied == 1) { return 0; }
                    target_x += x;
                }
            } else {
                target_y = cords[0] + y;
                while (abs(target_y - cords[2]) >= 1) {
                    if (brd[target_y][cords[3]].occupied == 1) { return 0; }
                    target_y += y;
                }
            }
            if ((where.occupied == 1 && where.piece.color != who)
                || (where.occupied == 0)) {
                    return 1;
                } else { return 0; }
            } else { return 0; }
            break;
        case 5:
            if (abs(cords[0] - cords[2]) == abs(cords[1] - cords[3])) {
            x = (cords[3] > cords[1]) ? 1 : -1;
            y = (cords[2] > cords[0]) ? 1 : -1;
            target_x = cords[1] + x;
            target_y = cords[0] + y;
            while (abs(target_x - cords[3]) >= 1) {
                if (brd[target_y][target_x].occupied == 1) { return 0; }
                target_x += x;
                target_y += y;
            }
            if ((where.occupied == 1 && where.piece.color != who)
                || (where.occupied == 0)) {
                    return 1;
                } else { return 0; }
            } else if (cords[0] == cords[2] || cords[1] == cords[3]) {
            x = (cords[3] > cords[1]) ? 1 : -1;
            y = (cords[2] > cords[0]) ? 1 : -1;
            if (cords[1] != cords[3]) {
                target_x = cords[1] + x;
                while (abs(target_x - cords[3]) >= 1) {
                    if (brd[cords[2]][target_x].occupied == 1) { return 0; }
                    target_x += x;
                }
            } else {
                target_y = cords[0] + y;
                while (abs(target_y - cords[2]) >= 1) {
                    if (brd[target_y][cords[3]].occupied == 1) { return 0; }
                    target_y += y;
                }
            }
            if ((where.occupied == 1 && where.piece.color != who)
                || (where.occupied == 0)) {
                    return 1;
                } else { return 0; }
            } else { return 0; }
            break;
        case 6:
            if((abs(cords[0] - cords[2]) == 1 || abs(cords[0] - cords[2]) == 0)
                && (abs(cords[1] - cords[3]) == 1 || abs(cords[1] - cords[3]) == 0)) {
                    if (where.occupied == 0 
                        || (where.occupied == 1 && where.piece.color != who)) {
                        return 1;
                    }
            } else if (cords[0] == cords[2] && (cords[3] == 0 || cords[3] == 7)  // Castling
                    && cords[1] == 4
                    && where.occupied && where.piece.type == 4
                    && move.piece.num_moves == 0 && where.piece.num_moves == 0) {
                x = (cords[3] > cords[1]) ? 1 : -1;
                target_x = cords[1] + x;
                while (abs(target_x - cords[3]) >= 1) {
                    if (brd[cords[0]][target_x].occupied == 1) {
                        return 0; 
                        }
                    target_x += x;
                }
                return 2;
            }
            return 0;
            break;
        default:
            return 0;
            break;
        }
    return 0;
}

bool Board::attack(Field bord[8][8], int who) {
    int ii, jj, index, knight[4] = {1, -1, 2, -2};
    int x, y;
    std::vector <bool> branch;
    branch = {true, true, true, true, true, true, true, true};
    who = (who == 0) ? 1 : 0;
    for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
    if (bord[i][j].occupied == 1 && bord[i][j].piece.color == who) {
        switch(bord[i][j].piece.type) { // Switch
            case 1:
            if (who == 1) {
                jj = j;
                ii = i - 1;
                for (int k = 1; k < 3; k++) {
                jj = (jj > j) ? j - 1 : j + 1;
                if (ii >= 0 && jj < 8 && jj >=0
                    && bord[ii][jj].occupied == 1 && bord[ii][jj].piece.type == 6
                    && bord[ii][jj].piece.color != who) {
                        return 1;
                    }
                }
            } else {
                jj = j;
                ii = i + 1;
                for (int k = 1; k < 3; k++) {
                jj = (jj > j) ? j - 1 : j + 1;
                if (ii < 8 && jj < 8 && jj >=0
                    && bord[ii][jj].occupied == 1 && bord[ii][jj].piece.type == 6
                    && bord[ii][jj].piece.color != who) {
                        return 1;
                }
                }
            }
                break;
            case 2: // Knight
                for (int k = 0; k < 4; k++) {
                    ii = i + knight[k];
                    jj = (abs(knight[k]) > 1) ? 1 : 2;
                    for (int l = 0; l < 2; l++) {
                        if (ii < 8 && (jj + j) < 8
                            && ii >= 0 && (jj + j) >= 0
                            && bord[ii][jj + j].occupied == 1 
                            && bord[ii][jj + j].piece.type == 6) {
                            if (bord[ii][jj + j].piece.color != who) {
                                return 1;
                            }
                    }
                    jj = jj * -1;
                    }
                }
                break;
            case 3: // Bishop
                for (int b = 0; b < 4; b++) {
                    branch[b] = true;
                }
                ii = 0;
                while (branch[0] || branch[1]
                    || branch[2] || branch[3]) {
                    ii++;
                    if (branch[0]) {
                    x = i - ii;
                    y = j - ii;
                    if (x >= 0 && y >= 0) {
                        branch[0] = (bord[x][y].occupied == 1) ? false : true;
                        if (bord[x][y].occupied == 1
                        && bord[x][y].piece.type == 6
                        && bord[x][y].piece.color != who) {
                            return 1;
                        }
                    } else { branch[0] = false; }
                    }
                    if (branch[1]) {
                    x = i - ii;
                    y = j + ii;
                    if (x >= 0 && y < 8) {
                        branch[1] = (bord[x][y].occupied == 1) ? false : true;
                        if (bord[x][y].occupied == 1
                        && bord[x][y].piece.type == 6
                        && bord[x][y].piece.color != who) {
                            return 1;
                        }
                    } else { branch[1] = false; }
                    }
                    if (branch[2]) {
                    x = i + ii;
                    y = j + ii;
                    if (x < 8 && y < 8) {
                        branch[2] = (bord[x][y].occupied == 1) ? false : true;
                        if (bord[x][y].occupied == 1
                        && bord[x][y].piece.type == 6
                        && bord[x][y].piece.color != who) {
                            return 1;
                        }
                    } else { branch[2] = false; }
                    }
                    if (branch[3]) {
                    x = i + ii;
                    y = j - ii;
                    if (x < 8 && y >= 0) {
                        branch[3] = (bord[x][y].occupied == 1) ? false : true;
                        if (bord[x][y].occupied == 1
                        && bord[x][y].piece.type == 6
                        && bord[x][y].piece.color != who) {
                            return 1;
                        }
                    } else { branch[3] = false; }
                    }
                    }
                break;
            case 4: // Rook
                for (int b = 4; b < 8; b++) {
                    branch[b] = true;
                }
                ii = 0;
                while (branch[4] || branch[5]
                    || branch[6] || branch[7]) {
                ii++;
                if (branch[4]) {
                x = i - ii;
                y = j;
                if (x >= 0) {
                    branch[4] = (bord[x][y].occupied == 1) ? false : true;
                    if (bord[x][y].occupied == 1 && bord[x][y].piece.type == 6
                        && bord[x][y].piece.color != who) {
                        return 1;
                    }
                } else { branch[4] = false; }
                }
                if (branch[5]) {
                x = i;
                y = j + ii;
                if (y < 8) {
                    branch[5] = (bord[x][y].occupied == 1) ? false : true;
                    if (bord[x][y].occupied == 1 && bord[x][y].piece.type == 6
                        && bord[x][y].piece.color != who) {
                        return 1;
                    }
                } else { branch[5] = false; }
                }
                if (branch[6]) {
                x = i + ii;
                y = j;
                if (x < 8) {
                    branch[6] = (bord[x][y].occupied == 1) ? false : true;
                    if (bord[x][y].occupied == 1 && bord[x][y].piece.type == 6
                        && bord[x][y].piece.color != who) {
                        return 1;
                    }
                } else { branch[6] = false; }
                }
                if (branch[7]) {
                x = i;
                y = j - ii;
                if (y >= 0) {
                    branch[7] = (bord[x][y].occupied == 1) ? false : true;
                    if (bord[x][y].occupied == 1 && bord[x][y].piece.type == 6
                        && bord[x][y].piece.color != who) {
                        return 1;
                    }
                } else { branch[7] = false; }
                }
                }
                break;
            case 5: // Queen
                for (int b = 0; b < 8; b++) {
                    branch[b] = true;
                }
                ii = 0;
                while (branch[0] || branch[1]
                    || branch[2] || branch[3]
                    || branch[4] || branch[5]
                    || branch[6] || branch[7]) {
                    ii++;
                    if (branch[0]) {
                    x = i - ii;
                    y = j - ii;
                    if (x >= 0 && y >= 0) {
                        branch[0] = (bord[x][y].occupied == 1) ? false : true;
                        if (bord[x][y].occupied == 1
                        && bord[x][y].piece.type == 6
                        && bord[x][y].piece.color != who) {
                            return 1;
                        }
                    } else { branch[0] = false; }
                    }
                    if (branch[1]) {
                    x = i - ii;
                    y = j + ii;
                    if (x >= 0 && y < 8) {
                        branch[1] = (bord[x][y].occupied == 1) ? false : true;
                        if (bord[x][y].occupied == 1
                        && bord[x][y].piece.type == 6
                        && bord[x][y].piece.color != who) {
                            return 1;
                        }
                    } else { branch[1] = false; }
                    }
                    if (branch[2]) {
                    x = i + ii;
                    y = j + ii;
                    if (x < 8 && y < 8) {
                        branch[2] = (bord[x][y].occupied == 1) ? false : true;
                        if (bord[x][y].occupied == 1
                        && bord[x][y].piece.type == 6
                        && bord[x][y].piece.color != who) {
                            return 1;
                        }
                    } else { branch[2] = false; }
                    }
                    if (branch[3]) {
                    x = i + ii;
                    y = j - ii;
                    if (x < 8 && y >= 0) {
                        branch[3] = (bord[x][y].occupied == 1) ? false : true;
                        if (bord[x][y].occupied == 1
                        && bord[x][y].piece.type == 6
                        && bord[x][y].piece.color != who) {
                            return 1;
                        }
                    } else { branch[3] = false; }
                    }
                    if (branch[4]) {
                    x = i - ii;
                    y = j;
                    if (x >= 0) {
                        branch[4] = (bord[x][y].occupied == 1) ? false : true;
                        if (bord[x][y].occupied == 1 && bord[x][y].piece.type == 6
                            && bord[x][y].piece.color != who) {
                            return 1;
                        }
                    } else { branch[4] = false; }
                    }
                    if (branch[5]) {
                    x = i;
                    y = j + ii;
                    if (y < 8) {
                        branch[5] = (bord[x][y].occupied == 1) ? false : true;
                        if (bord[x][y].occupied == 1 && bord[x][y].piece.type == 6
                            && bord[x][y].piece.color != who) {
                            return 1;
                        }
                    } else { branch[5] = false; }
                    }
                    if (branch[6]) {
                    x = i + ii;
                    y = j;
                    if (x < 8) {
                        branch[6] = (bord[x][y].occupied == 1) ? false : true;
                        if (bord[x][y].occupied == 1 && bord[x][y].piece.type == 6
                            && bord[x][y].piece.color != who) {
                            return 1;
                        }
                    } else { branch[6] = false; }
                    }
                    if (branch[7]) {
                    x = i;
                    y = j - ii;
                    if (y >= 0) {
                        branch[7] = (bord[x][y].occupied == 1) ? false : true;
                        if (bord[x][y].occupied == 1 && bord[x][y].piece.type == 6
                            && bord[x][y].piece.color != who) {
                            return 1;
                        }
                    } else { branch[7] = false; }
                    }
                    }
                break;
            case 6: // King
            if (i + 1 < 8) {
                    if (bord[i + 1][j].occupied == 1 && bord[i + 1][j].piece.type == 6) {
                            return 1;
                        }
                    if (j + 1 < 8) {
                        if (bord[i + 1][j + 1].occupied == 1 && bord[i + 1][j + 1].piece.type == 6) {
                            return 1;
                        }
                    }
                    if (j - 1 >= 0) {
                        if (bord[i + 1][j - 1].occupied == 1 && bord[i + 1][j - 1].piece.type == 6) {
                            return 1;
                        }
                    }
                }
                if (i - 1 >= 0) {
                    if (bord[i - 1][j].occupied == 1 && bord[i - 1][j].piece.type == 6) {
                            return 1;
                        }
                    if (j + 1 < 8) {
                        if (bord[i - 1][j + 1].occupied == 1 && bord[i - 1][j + 1].piece.type == 6) {
                            return 1;
                        }
                    }
                    if (j - 1 >= 0) {
                        if (bord[i - 1][j - 1].occupied == 1 && bord[i - 1][j - 1].piece.type == 6) {
                            return 1;
                        }
                    }
                }
                if (j + 1 < 8) {
                    if (bord[i][j + 1].occupied == 1 && bord[i][j + 1].piece.type == 6) {
                        return 1;
                        }
                }
                if (j - 1 >= 0) {
                    if (bord[i][j - 1].occupied == 1 && bord[i][j - 1].piece.type == 6) {
                        return 1;
                    }
                }
                break;
            default:
                continue;
                break;
        } // Switch
    } // if occupied
    } // j loop
    } // i loop
    return 0;
}

void Board::check() { // Checks which king is under attack
    std::cout << "White: " << white_attack << std::endl;
    std::cout << "Black: " << black_attack << std::endl;
}

int Board::possible(int who) {
    int ii, jj, index, knight[4] = {1, -1, 2, -2}, king_attack, count = 0;
    int x, y;
    std::vector <bool> branch;
    branch = {true, true, true, true, true, true, true, true};

    for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
    if (brd[i][j].occupied == 1 && brd[i][j].piece.color == who) {
        switch(brd[i][j].piece.type) {
            case 1:
            if (who == 1) {
                if (i - 1 >= 0 && brd[i - 1][j].occupied == 0) {
                    brd_cpy[i - 1][j].setvalues(brd_cpy[i][j]);
                    brd_cpy[i][j].setvalues(0, -1);
                    if (!attack(brd_cpy, who)) {
                        count++;
                    }
                    brd_cpy[i - 1][j].setvalues(brd[i - 1][j]);
                    brd_cpy[i][j].setvalues(brd[i][j]);
                }
                if (i - 2 >= 0 && brd[i - 2][j].occupied == 0 && brd_cpy[i][j].piece.num_moves == 0) {
                    brd_cpy[i - 2][j].setvalues(brd_cpy[i][j]);
                    brd_cpy[i][j].setvalues(0, -1);
                    if (!attack(brd_cpy, who)) {
                        count++;
                    }
                    brd_cpy[i - 2][j].setvalues(brd[i - 2][j]);
                    brd_cpy[i][j].setvalues(brd[i][j]);
                }
                if (i - 1 >= 0 && j + 1 < 8 && brd[i - 1][j + 1].occupied == 1
                    && brd[i - 1][j + 1].piece.color != who) {
                    brd_cpy[i - 1][j + 1].setvalues(brd_cpy[i][j]);
                    brd_cpy[i][j].setvalues(0, -1);
                    if (!attack(brd_cpy, who)) {
                        count++;
                    }
                    brd_cpy[i - 1][j + 1].setvalues(brd[i - 1][j + 1]);
                    brd_cpy[i][j].setvalues(brd[i][j]);
                }
                if (i - 1 >= 0 && j - 1 >= 0 && brd[i - 1][j - 1].occupied == 1
                    && brd[i - 1][j - 1].piece.color != who) {
                    brd_cpy[i - 1][j - 1].setvalues(brd_cpy[i][j]);
                    brd_cpy[i][j].setvalues(0, -1);
                    if (!attack(brd_cpy, who)) {
                        count++;
                    }
                    brd_cpy[i - 1][j - 1].setvalues(brd[i - 1][j - 1]);
                    brd_cpy[i][j].setvalues(brd[i][j]);
                }
            } else {
                if (i + 1 < 8 && brd[i + 1][j].occupied == 0) {
                    brd_cpy[i + 1][j].setvalues(brd_cpy[i][j]);
                    brd_cpy[i][j].setvalues(0, -1);
                    if (!attack(brd_cpy, who)) {
                        count++;
                    }
                    brd_cpy[i + 1][j].setvalues(brd[i + 1][j]);
                    brd_cpy[i][j].setvalues(brd[i][j]);
                }
                if (i + 2 < 8 && brd[i + 2][j].occupied == 0 && brd_cpy[i][j].piece.num_moves == 0) {
                    brd_cpy[i + 2][j].setvalues(brd_cpy[i][j]);
                    brd_cpy[i][j].setvalues(0, -1);
                    if (!attack(brd_cpy, who)) {
                        count++;
                    }
                    brd_cpy[i + 2][j].setvalues(brd[i + 2][j]);
                    brd_cpy[i][j].setvalues(brd[i][j]);
                }
                if (i + 1 < 8 && j + 1 < 8 && brd[i + 1][j + 1].occupied == 1
                    && brd[i + 1][j + 1].piece.color != who) {
                    brd_cpy[i + 1][j + 1].setvalues(brd_cpy[i][j]);
                    brd_cpy[i][j].setvalues(0, -1);
                    if (!attack(brd_cpy, who)) {
                        count++;
                    }
                    brd_cpy[i + 1][j + 1].setvalues(brd[i + 1][j + 1]);
                    brd_cpy[i][j].setvalues(brd[i][j]);
                }
                if (i + 1 < 8 && j - 1 >= 0 && brd[i + 1][j - 1].occupied == 1
                    && brd[i + 1][j - 1].piece.color != who) {
                    brd_cpy[i + 1][j - 1].setvalues(brd_cpy[i][j]);
                    brd_cpy[i][j].setvalues(0, -1);
                    if (!attack(brd_cpy, who)) {
                        count++;
                    }
                    brd_cpy[i + 1][j - 1].setvalues(brd[i + 1][j - 1]);
                    brd_cpy[i][j].setvalues(brd[i][j]);
                }
            }
                break;
            case 2: // Knight
                for (int k = 0; k < 4; k++) {
                    ii = i + knight[k];
                    jj = (abs(knight[k]) > 1) ? 1 : 2;
                    for (int l = 0; l < 2; l++) {
                        if ((ii < 8 && (jj + j) < 8
                            && ii >= 0 && (jj + j) >= 0)
                            && ((brd[ii][jj + j].occupied == 1 
                            && brd[ii][jj + j].piece.color != who)
                            || brd[ii][jj + j].occupied == 0)) {
                            brd_cpy[ii][jj + j].setvalues(brd_cpy[i][j]);
                            brd_cpy[i][j].setvalues(0, -1);
                            if (!attack(brd_cpy, who)) {
                                count++;
                            }
                            brd_cpy[ii][jj + j].setvalues(brd[ii][jj + j]);
                            brd_cpy[i][j].setvalues(brd[i][j]);
                            }
                        jj = jj * -1;
                    }
                }
                break;
            case 3: // Bishop
                for (int b = 0; b < 4; b++) {
                    branch[b] = true;
                }
                ii = 0;
                while (branch[0] || branch[1]
                    || branch[2] || branch[3]) {
                    ii++;
                    if (branch[0]) {
                        x = i - ii;
                        y = j - ii;
                    if ((x >= 0) && (y >= 0)) {
                        branch[0] = (brd[x][y].occupied == 1) ? false : true;
                        if (brd[x][y].occupied == 0
                        || (brd[x][y].occupied == 1 && brd[x][y].piece.color != who)) {
                            brd_cpy[x][y].setvalues(brd[i][j]);
                            brd_cpy[i][j].setvalues(0, -1);
                            if (!attack(brd_cpy, who)) {
                                count++;
                            }
                            brd_cpy[x][y].setvalues(brd[x][y]);
                            brd_cpy[i][j].setvalues(brd[i][j]);
                        }
                    } { branch[0] = false; }
                    }
                    if (branch[1]) {
                        x = i - ii;
                        y = j + ii;
                    if ((x >= 0) && (y < 8)) {
                        branch[1] = (brd[x][y].occupied == 1) ? false : true;
                        if (brd[x][y].occupied == 0
                        || (brd[x][y].occupied == 1 && brd[x][y].piece.color != who)) {
                            brd_cpy[x][y].setvalues(brd[i][j]);
                            brd_cpy[i][j].setvalues(0, -1);
                            if (!attack(brd_cpy, who)) {
                                count++;
                            }
                            brd_cpy[x][y].setvalues(brd[x][y]);
                            brd_cpy[i][j].setvalues(brd[i][j]);
                        }
                    } else { branch[1] = false; }
                    }
                    if (branch[2]) {
                        x = i + ii;
                        y = j + ii;
                    if ((x < 8) && (y < 8)) {
                        branch[2] = (brd[x][y].occupied == 1) ? false : true;
                        if (brd[x][y].occupied == 0
                        || (brd[x][y].occupied == 1 && brd[x][y].piece.color != who)) {
                            brd_cpy[x][y].setvalues(brd[i][j]);
                            brd_cpy[i][j].setvalues(0, -1);
                            if (!attack(brd_cpy, who)) {
                                count++;
                            }
                            brd_cpy[x][y].setvalues(brd[x][y]);
                            brd_cpy[i][j].setvalues(brd[i][j]);
                        }
                    } { branch[2] = false; }
                    }
                    if (branch[3]) {
                        x = i + ii;
                        y = j - ii;
                    if ((x < 8) && (y >= 0)) {
                        branch[0] = (brd[x][y].occupied == 1) ? false : true;
                        if (brd[x][y].occupied == 0
                        || (brd[x][y].occupied == 1 && brd[x][y].piece.color != who)) {
                            brd_cpy[x][y].setvalues(brd[i][j]);
                            brd_cpy[i][j].setvalues(0, -1);
                            if (!attack(brd_cpy, who)) {
                                count++;
                            }
                            brd_cpy[x][y].setvalues(brd[x][y]);
                            brd_cpy[i][j].setvalues(brd[i][j]);
                        }
                    } { branch[3] = false; }
                    }
                    }
                break;
            case 4: // Rook
                for (int b = 4; b < 8; b++) {
                    branch[b] = true;
                }
                ii = 0;
                while (branch[4] || branch[5]
                    || branch[6] || branch[7]){
                ii++;
                if (branch[4]) {
                x = i - ii;
                y = j;
                if (x >= 0) {
                    branch[4] = (brd[x][y].occupied == 1) ? false : true;
                    if (brd[x][y].occupied == 0 
                    || (brd[x][y].occupied == 1 && brd[x][y].piece.color != who)) {
                        brd_cpy[x][y].setvalues(brd_cpy[i][j]);
                        brd_cpy[i][j].setvalues(0, -1);
                        if (!attack(brd_cpy, who)) {
                            count++;
                        }
                        brd_cpy[x][y].setvalues(brd[x][y]);
                        brd_cpy[i][j].setvalues(brd[i][j]);
                    }
                } else { branch[4] = false; }
                }
                if (branch[5]) {
                x = i;
                y = j + ii;
                if (y < 8) {
                    branch[5] = (brd[x][y].occupied == 1) ? false : true;
                    if (brd[x][y].occupied == 0 
                    || (brd[x][y].occupied == 1 && brd[x][y].piece.color != who)) {
                        brd_cpy[x][y].setvalues(brd_cpy[i][j]);
                        brd_cpy[i][j].setvalues(0, -1);
                        if (!attack(brd_cpy, who)) {
                            count++;
                        }
                        brd_cpy[x][y].setvalues(brd[x][y]);
                        brd_cpy[i][j].setvalues(brd[i][j]);
                    }
                } else { branch[5] = false; }
                }
                if (branch[6]) {
                x = i + ii;
                y = j;
                if (x < 8) {
                    branch[6] = (brd[x][y].occupied == 1) ? false : true;
                    if (brd[x][y].occupied == 0 
                    || (brd[x][y].occupied == 1 && brd[x][y].piece.color != who)) {
                        brd_cpy[x][y].setvalues(brd_cpy[i][j]);
                        brd_cpy[i][j].setvalues(0, -1);
                        if (!attack(brd_cpy, who)) {
                            count++;
                        }
                        brd_cpy[x][y].setvalues(brd[x][y]);
                        brd_cpy[i][j].setvalues(brd[i][j]);
                    }
                } else { branch[6] = false; }
                }
                if (branch[7]) {
                x = i;
                y = j - ii;
                if (y >= 0) {
                    branch[7] = (brd[x][y].occupied == 1) ? false : true;
                    if (brd[x][y].occupied == 0 
                    || (brd[x][y].occupied == 1 && brd[x][y].piece.color != who)) {
                        brd_cpy[x][y].setvalues(brd_cpy[i][j]);
                        brd_cpy[i][j].setvalues(0, -1);
                        if (!attack(brd_cpy, who)) {
                            count++;
                        }
                        brd_cpy[x][y].setvalues(brd[x][y]);
                        brd_cpy[i][j].setvalues(brd[i][j]);
                    }
                } else { branch[7] = false; }
                }
                }
                break;
            case 5: // Queen
                for (int b = 0; b < 8; b++) {
                    branch[b] = true;
                }
                ii = 0;
                while (branch[0] || branch[1]
                    || branch[2] || branch[3]
                    || branch[4] || branch[5]
                    || branch[6] || branch[7]) {
                    ii++;
                    if (branch[0]) {
                        x = i - ii;
                        y = j - ii;
                    if ((x >= 0) && (y >= 0)) {
                        branch[0] = (brd[x][y].occupied == 1) ? false : true;
                        if (brd[x][y].occupied == 0
                        || (brd[x][y].occupied == 1 && brd[x][y].piece.color != who)) {
                            brd_cpy[x][y].setvalues(brd_cpy[i][j]);
                            brd_cpy[i][j].setvalues(0, -1);
                            if (!attack(brd_cpy, who)) {
                                count++;
                            }
                            brd_cpy[x][y].setvalues(brd[x][y]);
                            brd_cpy[i][j].setvalues(brd[i][j]);
                        }
                    } { branch[0] = false; }
                    }
                    if (branch[1]) {
                        x = i - ii;
                        y = j + ii;
                    if ((x >= 0) && (y < 8)) {
                        branch[1] = (brd[x][y].occupied == 1) ? false : true;
                        if (brd[x][y].occupied == 0
                        || (brd[x][y].occupied == 1 && brd[x][y].piece.color != who)) {
                            brd_cpy[x][y].setvalues(brd_cpy[i][j]);
                            brd_cpy[i][j].setvalues(0, -1);
                            if (!attack(brd_cpy, who)) {
                                count++;
                            }
                            brd_cpy[x][y].setvalues(brd[x][y]);
                            brd_cpy[i][j].setvalues(brd[i][j]);
                        }
                    } else { branch[1] = false; }
                    }
                    if (branch[2]) {
                        x = i + ii;
                        y = j + ii;
                    if ((x < 8) && (y < 8)) {
                        branch[2] = (brd[x][y].occupied == 1) ? false : true;
                        if (brd[x][y].occupied == 0
                        || (brd[x][y].occupied == 1 && brd[x][y].piece.color != who)) {
                            brd_cpy[x][y].setvalues(brd_cpy[i][j]);
                            brd_cpy[i][j].setvalues(0, -1);
                            if (!attack(brd_cpy, who)) {
                                count++;
                            }
                            brd_cpy[x][y].setvalues(brd[x][y]);
                            brd_cpy[i][j].setvalues(brd[i][j]);
                        }
                    } { branch[2] = false; }
                    }
                    if (branch[3]) {
                        x = i + ii;
                        y = j - ii;
                    if ((x < 8) && (y >= 0)) {
                        branch[0] = (brd[x][y].occupied == 1) ? false : true;
                        if (brd[x][y].occupied == 0
                        || (brd[x][y].occupied == 1 && brd[x][y].piece.color != who)) {
                            brd_cpy[x][y].setvalues(brd_cpy[i][j]);
                            brd_cpy[i][j].setvalues(0, -1);
                            if (!attack(brd_cpy, who)) {
                                count++;
                            }
                            brd_cpy[x][y].setvalues(brd[x][y]);
                            brd_cpy[i][j].setvalues(brd[i][j]);
                        }
                    } { branch[3] = false; }
                    }
                    if (branch[4]) {
                    x = i - ii;
                    y = j;
                    if (x >= 0) {
                        branch[4] = (brd[x][y].occupied == 1) ? false : true;
                        if (brd[x][y].occupied == 0 
                        || (brd[x][y].occupied == 1 && brd[x][y].piece.color != who)) {
                            brd_cpy[x][y].setvalues(brd_cpy[i][j]);
                            brd_cpy[i][j].setvalues(0, -1);
                            if (!attack(brd_cpy, who)) {
                                count++;
                            }
                            brd_cpy[x][y].setvalues(brd[x][y]);
                            brd_cpy[i][j].setvalues(brd[i][j]);
                        }
                    } else { branch[4] = false; }
                    }
                    if (branch[5]) {
                    x = i;
                    y = j + ii;
                    if (y < 8) {
                        branch[5] = (brd[x][y].occupied == 1) ? false : true;
                        if (brd[x][y].occupied == 0 
                        || (brd[x][y].occupied == 1 && brd[x][y].piece.color != who)) {
                            brd_cpy[x][y].setvalues(brd_cpy[i][j]);
                            brd_cpy[i][j].setvalues(0, -1);
                            if (!attack(brd_cpy, who)) {
                                count++;
                            }
                            brd_cpy[x][y].setvalues(brd[x][y]);
                            brd_cpy[i][j].setvalues(brd[i][j]);
                        }
                    } else { branch[5] = false; }
                    }
                    if (branch[6]) {
                    x = i + ii;
                    y = j;
                    if (x < 8) {
                        branch[6] = (brd[x][y].occupied == 1) ? false : true;
                        if (brd[x][y].occupied == 0 
                        || (brd[x][y].occupied == 1 && brd[x][y].piece.color != who)) {
                            brd_cpy[x][y].setvalues(brd_cpy[i][j]);
                            brd_cpy[i][j].setvalues(0, -1);
                            if (!attack(brd_cpy, who)) {
                                count++;
                            }
                            brd_cpy[x][y].setvalues(brd[x][y]);
                            brd_cpy[i][j].setvalues(brd[i][j]);
                        }
                    } else { branch[6] = false; }
                    }
                    if (branch[7]) {
                    x = i;
                    y = j - ii;
                    if (y >= 0) {
                        branch[7] = (brd[x][y].occupied == 1) ? false : true;
                        if (brd[x][y].occupied == 0 
                        || (brd[x][y].occupied == 1 && brd[x][y].piece.color != who)) {
                            brd_cpy[x][y].setvalues(brd_cpy[i][j]);
                            brd_cpy[i][j].setvalues(0, -1);
                            if (!attack(brd_cpy, who)) {
                                count++;
                            }
                            brd_cpy[x][y].setvalues(brd[x][y]);
                            brd_cpy[i][j].setvalues(brd[i][j]);
                        }
                    } else { branch[7] = false; }
                    }
                    }
                break;
            case 6: // King
                if (i + 1 < 8) {
                    if ((brd[i + 1][j].occupied == 1 && brd[i + 1][j].piece.color != who)
                        || brd[i + 1][j].occupied == 0) {
                            brd_cpy[i + 1][j].setvalues(brd_cpy[i][j]);
                            brd_cpy[i][j].setvalues(0, -1);
                            if (!attack(brd_cpy, who)) {
                                count++;
                            }
                            brd_cpy[i + 1][j].setvalues(brd[i + 1][j]);
                            brd_cpy[i][j].setvalues(brd[i][j]);
                        }
                    if (j + 1 < 8) {
                        if ((brd[i + 1][j + 1].occupied == 1 && brd[i + 1][j + 1].piece.color != who)
                        || brd[i + 1][j + 1].occupied == 0) {
                            brd_cpy[i + 1][j + 1].setvalues(brd_cpy[i][j]);
                            brd_cpy[i][j].setvalues(0, -1);
                            if (!attack(brd_cpy, who)) {
                                count++;
                            }
                            brd_cpy[i + 1][j + 1].setvalues(brd[i + 1][j + 1]);
                            brd_cpy[i][j].setvalues(brd[i][j]);
                        }
                    }
                    if (j - 1 >= 0) {
                        if ((brd[i + 1][j - 1].occupied == 1 && brd[i + 1][j - 1].piece.color != who)
                        || brd[i + 1][j - 1].occupied == 0) {
                            brd_cpy[i + 1][j - 1].setvalues(brd_cpy[i][j]);
                            brd_cpy[i][j].setvalues(0, -1);
                            if (!attack(brd_cpy, who)) {
                                count++;
                            }
                            brd_cpy[i + 1][j - 1].setvalues(brd[i + 1][j - 1]);
                            brd_cpy[i][j].setvalues(brd[i][j]);
                        }
                    }
                }
                if (i - 1 >= 0) {
                    if ((brd[i - 1][j].occupied == 1 && brd[i - 1][j].piece.color != who)
                        || brd[i - 1][j].occupied == 0) {
                            brd_cpy[i - 1][j].setvalues(brd_cpy[i][j]);
                            brd_cpy[i][j].setvalues(0, -1);
                            if (!attack(brd_cpy, who)) {
                                count++;
                            }
                            brd_cpy[i - 1][j].setvalues(brd[i - 1][j]);
                            brd_cpy[i][j].setvalues(brd[i][j]);
                        }
                    if (j + 1 < 8) {
                        if ((brd[i - 1][j + 1].occupied == 1 && brd[i - 1][j + 1].piece.color != who)
                        || brd[i - 1][j + 1].occupied == 0) {
                            brd_cpy[i - 1][j + 1].setvalues(brd_cpy[i][j]);
                            brd_cpy[i][j].setvalues(0, -1);
                            if (!attack(brd_cpy, who)) {
                                count++;
                            }
                            brd_cpy[i - 1][j + 1].setvalues(brd[i - 1][j + 1]);
                            brd_cpy[i][j].setvalues(brd[i][j]);
                        }
                    }
                    if (j - 1 >= 0) {
                        if ((brd[i - 1][j - 1].occupied == 1 && brd[i - 1][j - 1].piece.color != who)
                        || brd[i - 1][j - 1].occupied == 0) {
                            brd_cpy[i - 1][j - 1].setvalues(brd_cpy[i][j]);
                            brd_cpy[i][j].setvalues(0, -1);
                            if (!attack(brd_cpy, who)) {
                                count++;
                            }
                            brd_cpy[i - 1][j - 1].setvalues(brd[i - 1][j - 1]);
                            brd_cpy[i][j].setvalues(brd[i][j]);
                        }
                    }
                }
                if (j + 1 < 8) {
                    if ((brd[i][j + 1].occupied == 1 && brd[i][j + 1].piece.color != who)
                        || brd[i][j + 1].occupied == 0) {
                        brd_cpy[i][j + 1].setvalues(brd_cpy[i][j]);
                        brd_cpy[i][j].setvalues(0, -1);
                        if (!attack(brd_cpy, who)) {
                            count++;
                        }
                        brd_cpy[i][j + 1].setvalues(brd[i][j + 1]);
                        brd_cpy[i][j].setvalues(brd[i][j]);
                        }
                }
                if (j - 1 >= 0) {
                    if ((brd[i][j - 1].occupied == 1 && brd[i][j - 1].piece.color != who)
                        || brd[i][j - 1].occupied == 0) {
                        brd_cpy[i][j - 1].setvalues(brd_cpy[i][j]);
                        brd_cpy[i][j].setvalues(0, -1);
                        if (!attack(brd_cpy, who)) {
                            count++;
                        }
                        brd_cpy[i][j - 1].setvalues(brd[i][j - 1]);
                        brd_cpy[i][j].setvalues(brd[i][j]);
                    }
                }
                break;
            default:
                continue;
                break;
        } // Switch
    } // if occupied
    } // j loop
    } // i loop
    return count;
}

Board::~Board() = default;
// End of Board obj