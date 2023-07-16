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
    white_attack = 0;
    black_attack = 0;
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

void Board::print_attack() {
    std::string separator = "---+---+---+---+---+---+---+---+---+";
    int index;
    for (int i = 0; i < 9; i++) {
        if (i == 0) {
            std::cout << "   | A | B | C | D | E | F | G | H |" << std::endl;
            std::cout<< separator << std::endl;
        }
        else {
            printf(" %i |", 9 - i);
            for (int j = 0; j < 8; j++){
                std::cout << " " << attacked[i - 1][j] << " |";
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
        check = check_move(who, move.piece.type, move, where, arr);
        if (move.piece.type == 1) {
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
        } else {
            if (check) {
                    where.setvalues(move);
                    move.setvalues(0, -1);
                    last[0] = arr[2];
                    last[1] = arr[3];
                    last_moved = where.piece.num_moves;
                    return 0;
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
                    if (where.occupied == 0 && attacked[cords[2]][cords[3]] == 0) {
                        return 1;
                    }
                    if (where.occupied == 1 && where.piece.color != who) {
                        return 1;
                    }
                }
            return 0;
            break;
        default:
            return 0;
            break;
        }
    return 0;
}

void Board::attack() {
    int ii, jj, index, knight[4] = {1, -1, 2, -2};
    bool branch[8] = {1, 1, 1, 1, 1, 1, 1, 1};
    for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
        attacked[i][j] = 0;
        }
    }
    for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
    if (brd[i][j].occupied == 1) {
        switch(brd[i][j].piece.type) { // Switch
            case 1:
            if (brd[i][j].piece.color == 1) {
                jj = j;
                ii = i - 1;
                for (int k = 1; k < 3; k++) {
                jj = (jj > j) ? j - 1 : j + 1;
                index = (7 * ii) + (ii + jj);
                if (ii >= 0 && jj < 8 && jj >=0
                    && brd[ii][jj].occupied == 1 && brd[ii][jj].piece.type == 6
                    && brd[ii][jj].piece.color == 0) {
                        black_attack = 1;
                    }
                if ((ii >= 0 && jj < 8 && jj >=0 && attacked[ii][jj] == 0)
                    && ((brd[ii][jj].occupied == 1 
                    && brd[ii][jj].piece.color != brd[i][j].piece.color)
                    || brd[ii][jj].occupied == 0)) {
                    attacked[ii][jj] = 1;
                }
                }
            } else {
                jj = j;
                ii = i + 1;
                for (int k = 1; k < 3; k++) {
                jj = (jj > j) ? j - 1 : j + 1;
                index = (7 * ii) + (ii + jj);
                if (ii < 8 && jj < 8 && jj >=0
                    && brd[ii][jj].occupied == 1 && brd[ii][jj].piece.type == 6
                    && brd[ii][jj].piece.color == 0) {
                        black_attack = 1;
                }
                if ((ii < 8 && jj < 8 && jj >=0 && attacked[ii][jj] == 0)
                    && ((brd[ii][jj].occupied == 1 
                    && brd[ii][jj].piece.color != brd[i][j].piece.color)
                    || brd[ii][jj].occupied == 0)) {
                    attacked[ii][jj] = 1;
                }
                }
            }
                break;
            case 2: // Knight
                for (int k = 0; k < 4; k++) {
                    ii = i + knight[k];
                    jj = (abs(knight[k]) > 1) ? 1 : 2;
                    for (int l = 0; l < 2; l++) {
                        index = (7 * ii) + (ii + (j + jj));
                        if (ii < 8 && (jj + j) < 8
                            && ii >= 0 && (jj + j) >= 0
                            && brd[ii][jj + j].occupied == 1 
                            && brd[ii][jj + j].piece.type == 6) {
                            if (brd[ii][jj + j].piece.color == 0 
                                && brd[i][j].piece.color == 1) {
                                black_attack = true;
                            } else if (brd[ii][jj + j].piece.color == 1 
                                        && brd[i][j].piece.color == 0) {
                                white_attack = true;
                            }
                            }
                        if ((ii < 8 && (jj + j) < 8
                            && ii >= 0 && (jj + j) >= 0 && attacked[ii][jj + j] == 0)
                            && ((brd[ii][jj + j].occupied == 1 
                            && brd[ii][jj + j].piece.color != brd[i][j].piece.color)
                            || brd[ii][jj + j].occupied == 0)) {
                            attacked[ii][jj + j] = 1;
                        }
                        jj = jj * -1;
                    }
                }
                break;
            case 3: // Bishop
                for (int i = 0; i < 4; i++) {
                    branch[i] = 1;
                }
                ii = 0;
                while (branch[0] == 1 || branch[1] == 1
                    || branch[2] == 1 || branch[3] == 1) {
                        ii++;
                        if (branch[0] == 1) {
                        if ((i + ii) >=0 && (i + ii) < 8
                        && (j + ii) >=0 && (j + ii) < 8) {
                            if (brd[i + ii][j + ii].occupied 
                            && brd[i + ii][j + ii].piece.type == 6) {
                            if (brd[i + ii][j + ii].piece.color == 0 
                                && brd[i][j].piece.color == 1) {
                                black_attack = true;
                            } else if (brd[ii + i][j + ii].piece.color == 1 
                                        && brd[i][j].piece.color == 0) {
                                white_attack = true;
                            }
                            }
                            if ((brd[i + ii][j + ii].occupied == 1
                            && brd[i + ii][j + ii].piece.color != brd[i][j].piece.color)
                            || brd[i + ii][j + ii].occupied == 0) {
                                branch[0] = (brd[i + ii][j + ii].occupied == 1) ? 0 : 1;
                                attacked[i + ii][j + ii] = 1;
                            } else { branch[0] = 0; }
                        } else { branch[0] = 0; }
                        }
                        if (branch[1] == 1) {
                        if ((i - ii) >=0 && (i - ii) < 8
                        && (j + ii) >=0 && (j + ii) < 8) {
                            if (brd[i - ii][j + ii].occupied 
                            && brd[i - ii][j + ii].piece.type == 6) {
                            if (brd[i - ii][j + ii].piece.color == 0 
                                && brd[i][j].piece.color == 1) {
                                black_attack = true;
                            } else if (brd[ii - i][j + ii].piece.color == 1 
                                        && brd[i][j].piece.color == 0) {
                                white_attack = true;
                            }
                            }
                            if ((brd[i - ii][j + ii].occupied == 1
                            && brd[i - ii][j + ii].piece.color != brd[i][j].piece.color)
                            || brd[i - ii][j + ii].occupied == 0) {
                                branch[1] = (brd[i - ii][j + ii].occupied == 1) ? 0 : 1;
                                attacked[i - ii][j + ii] = 1;
                            } else { branch[1] = 0; }
                        } else { branch[1] = 0; }
                        }
                        if (branch[2] == 1) {
                        if ((i - ii) >=0 && (i - ii) < 8
                        && (j - ii) >=0 && (j - ii) < 8) {
                            if (brd[i - ii][j - ii].occupied 
                            && brd[i - ii][j - ii].piece.type == 6) {
                            if (brd[i - ii][j - ii].piece.color == 0 
                                && brd[i][j].piece.color == 1) {
                                black_attack = true;
                            } else if (brd[ii - i][j - ii].piece.color == 1 
                                        && brd[i][j].piece.color == 0) {
                                white_attack = true;
                            }
                            }
                            if ((brd[i - ii][j - ii].occupied == 1
                            && brd[i - ii][j - ii].piece.color != brd[i][j].piece.color)
                            || brd[i - ii][j - ii].occupied == 0) {
                                attacked[i - ii][j - ii] = 1;
                                branch[2] = (brd[i - ii][j - ii].occupied == 1) ? 0 : 1;
                            } else { branch[2] = 0; }
                        } else { branch[2] = 0; }
                        }
                        if (branch[3] == 1) {
                        if ((i + ii) >=0 && (i + ii) < 8
                        && (j - ii) >=0 && (j - ii) < 8) {
                            if (brd[i + ii][j - ii].occupied 
                            && brd[i + ii][j - ii].piece.type == 6) {
                            if (brd[i + ii][j - ii].piece.color == 0 
                                && brd[i][j].piece.color == 1) {
                                black_attack = true;
                            } else if (brd[ii + i][j - ii].piece.color == 1 
                                        && brd[i][j].piece.color == 0) {
                                white_attack = true;
                            }
                            }
                            if (brd[i + ii][j - ii].occupied == 1
                            && brd[i + ii][j - ii].piece.color != brd[i][j].piece.color) {
                                branch[3] = (brd[i + ii][j - ii].occupied == 1) ? 0 : 1;
                                attacked[i + ii][j - ii] = 1;
                            } else { branch[3] = 0; }
                        } else { branch[3] = 0; }
                        }
                    }
                break;
            case 4: // Rook
                for (int i = 4; i < 8; i++) {
                    branch[i] = 1;
                }
                ii = 0;
                while (branch[4] == 1 || branch[5] == 1
                    || branch[6] == 1 || branch[7] == 1) {
                        ii++;
                        if (branch[4] == 1) {
                        if ((j + ii) < 8) {
                            if (brd[i][j + ii].occupied 
                            && brd[i][j + ii].piece.type == 6) {
                            if (brd[i][j + ii].piece.color == 0 
                                && brd[i][j].piece.color == 1) {
                                black_attack = true;
                            } else if (brd[i][j + ii].piece.color == 1 
                                        && brd[i][j].piece.color == 0) {
                                white_attack = true;
                            }
                            }
                            if ((brd[i][j + ii].occupied == 1
                            && brd[i][j + ii].piece.color != brd[i][j].piece.color)
                            || brd[i][j + ii].occupied == 0) {
                                attacked[i][j + ii] = 1;
                                branch[4] = (brd[i][j + ii].occupied == 1) ? 0 : 1;
                            } else { branch[4] = 0; }
                        } else { branch[4] = 0; }
                        }
                        if (branch[5] == 1) {
                        if ((j - ii) >= 0) {
                            if (brd[i][j - ii].occupied 
                            && brd[i][j - ii].piece.type == 6) {
                            if (brd[i][j - ii].piece.color == 0 
                                && brd[i][j].piece.color == 1) {
                                black_attack = true;
                            } else if (brd[i][j - ii].piece.color == 1 
                                        && brd[i][j].piece.color == 0) {
                                white_attack = true;
                            }
                            }
                            if ((brd[i][j - ii].occupied == 1
                            && brd[i][j - ii].piece.color != brd[i][j].piece.color)
                            || brd[i][j - ii].occupied == 0) {
                                attacked[i][j - ii] = 1;
                                branch[5] = (brd[i][j - ii].occupied == 1) ? 0 : 1;
                            } else { branch[5] = 0; }
                        } else { branch[5] = 0; }
                        }
                        if (branch[6] == 1) {
                        if ((i + ii) < 8) {
                            if (brd[i + ii][j].occupied 
                            && brd[i + ii][j].piece.type == 6) {
                            if (brd[i + ii][j].piece.color == 0 
                                && brd[i][j].piece.color == 1) {
                                black_attack = true;
                            } else if (brd[i + ii][j].piece.color == 1 
                                        && brd[i][j].piece.color == 0) {
                                white_attack = true;
                            }
                            }
                            if ((brd[i + ii][j].occupied == 1
                            && brd[i + ii][j].piece.color != brd[i][j].piece.color)
                            || brd[i + ii][j].occupied == 0) {
                                attacked[i + ii][j] = 1;
                                branch[6] = (brd[i + ii][j].occupied == 1) ? 0 : 1;
                            } else { branch[6] = 0; }
                        } else { branch[6] = 0; }
                        }
                        if (branch[7] == 1) {
                        if ((i - ii) >= 0) {
                            if (brd[i - ii][j].occupied 
                            && brd[i - ii][j].piece.type == 6) {
                            if (brd[i - ii][j].piece.color == 0 
                                && brd[i][j].piece.color == 1) {
                                black_attack = true;
                            } else if (brd[i - ii][j].piece.color == 1 
                                        && brd[i][j].piece.color == 0) {
                                white_attack = true;
                            }
                            }
                            if ((brd[i - ii][j].occupied == 1
                            && brd[i - ii][j].piece.color != brd[i][j].piece.color)
                            || brd[i - ii][j].occupied == 0) {
                                attacked[i - ii][j] = 1;
                                branch[7] = (brd[i - ii][j].occupied == 1) ? 0 : 1;
                            } else { branch[7] = 0; }
                        } else { branch[7] = 0; }
                        }
                    }
                break;
            case 5: // Queen
                for (int i = 0; i < 8; i++) {
                    branch[i] = 1;
                }
                ii = 0;
                while (branch[0] == 1 || branch[1] == 1
                    || branch[2] == 1 || branch[3] == 1
                    || branch[4] == 1 || branch[5] == 1
                    || branch[6] == 1 || branch[7] == 1) {
                    ii++;
                    if (branch[0] == 1) {
                    if ((i + ii) >=0 && (i + ii) < 8
                    && (j + ii) >=0 && (j + ii) < 8) {
                        if (brd[i + ii][j + ii].occupied 
                        && brd[i + ii][j + ii].piece.type == 6) {
                        if (brd[i + ii][j + ii].piece.color == 0 
                            && brd[i][j].piece.color == 1) {
                            black_attack = true;
                        } else if (brd[ii + i][j + ii].piece.color == 1 
                                    && brd[i][j].piece.color == 0) {
                            white_attack = true;
                        }
                        }
                    if ((brd[i + ii][j + ii].occupied == 1
                        && brd[i + ii][j + ii].piece.color != brd[i][j].piece.color)
                        || brd[i + ii][j + ii].occupied == 0) {
                            attacked[i + ii][j + ii] = 1;
                            branch[0] = (brd[i + ii][j + ii].occupied == 1) ? 0 : 1;
                    } else { branch[0] = 0; }
                    } else { branch[0] = 0; }
                    }
                    if (branch[1] == 1) {
                    if ((i - ii) >=0 && (i - ii) < 8
                    && (j + ii) >=0 && (j + ii) < 8) {
                    if (brd[i - ii][j + ii].occupied 
                        && brd[i - ii][j + ii].piece.type == 6) {
                        if (brd[i - ii][j + ii].piece.color == 0 
                            && brd[i][j].piece.color == 1) {
                            black_attack = true;
                        } else if (brd[i - ii][j + ii].piece.color == 1 
                                    && brd[i][j].piece.color == 0) {
                            white_attack = true;
                        }
                        }
                        if ((brd[i - ii][j + ii].occupied == 1
                        && brd[i - ii][j + ii].piece.color != brd[i][j].piece.color)
                        || brd[i - ii][j + ii].occupied == 0) {
                            attacked[i - ii][j + ii] = 1;
                            branch[1] = (brd[i - ii][j + ii].occupied == 1) ? 0 : 1;
                        } else { branch[1] = 0; }
                    } else { branch[1] = 0; }
                    }
                    if (branch[2] == 1) {
                    if ((i - ii) >=0 && (i - ii) < 8
                    && (j - ii) >=0 && (j - ii) < 8) {
                        if (brd[i - ii][j - ii].occupied 
                            && brd[i - ii][j - ii].piece.type == 6) {
                        if (brd[i - ii][j - ii].piece.color == 0 
                            && brd[i][j].piece.color == 1) {
                            black_attack = true;
                        } else if (brd[i - ii][j - ii].piece.color == 1 
                                    && brd[i][j].piece.color == 0) {
                            white_attack = true;
                        }
                            }
                        if ((brd[i - ii][j - ii].occupied == 1
                        && brd[i - ii][j - ii].piece.color != brd[i][j].piece.color)
                        || brd[i - ii][j - ii].occupied == 0) {
                            attacked[i - ii][j - ii] = 1;
                            branch[2] = (brd[i - ii][j - ii].occupied == 1) ? 0 : 1;
                        } else { branch[2] = 0; }
                    } else { branch[2] = 0; }
                    }
                    if (branch[3] == 1) {
                    if ((i + ii) >=0 && (i + ii) < 8
                    && (j - ii) >=0 && (j - ii) < 8) {
                        if (brd[i + ii][j - ii].occupied 
                        && brd[i + ii][j - ii].piece.type == 6) {
                        if (brd[i + ii][j - ii].piece.color == 0 
                                && brd[i][j].piece.color == 1) {
                            black_attack = true;
                        } else if (brd[ii + i][j - ii].piece.color == 1 
                                    && brd[i][j].piece.color == 0) {
                            white_attack = true;
                        }
                        }
                        if (brd[i + ii][j - ii].occupied == 1
                        && brd[i + ii][j - ii].piece.color != brd[i][j].piece.color) {
                                branch[3] = 0;
                            attacked[i + ii][j - ii] = 1;
                            branch[3] = (brd[i + ii][j - ii].occupied == 1) ? 0 : 1;
                        } else { branch[3] = 0; }
                    } else { branch[3] = 0; }
                    }
                    if (branch[4] == 1) {
                    if ((j + ii) < 8) {
                        if (brd[i][j + ii].occupied 
                        && brd[i][j + ii].piece.type == 6) {
                        if (brd[i][j + ii].piece.color == 0 
                        && brd[i][j].piece.color == 1) {
                            black_attack = true;
                        } else if (brd[i][j + ii].piece.color == 1 
                                    && brd[i][j].piece.color == 0) {
                            white_attack = true;
                        }
                        }
                        if ((brd[i][j + ii].occupied == 1
                        && brd[i][j + ii].piece.color != brd[i][j].piece.color)
                        || brd[i][j + ii].occupied == 0) {
                            attacked[i][j + ii] = 1;
                            branch[4] = (brd[i][j + ii].occupied == 1) ? 0 : 1;
                        } else { branch[4] = 0; }
                    } else { branch[4] = 0; }
                    }
                    if (branch[5] == 1) {
                    if ((j - ii) >= 0) {
                        if (brd[i][j - ii].occupied 
                        && brd[i][j - ii].piece.type == 6) {
                        if (brd[i][j - ii].piece.color == 0 
                            && brd[i][j].piece.color == 1) {
                            black_attack = true;
                        } else if (brd[i][j - ii].piece.color == 1 
                                    && brd[i][j].piece.color == 0) {
                            white_attack = true;
                        }
                        }
                        if ((brd[i][j - ii].occupied == 1
                        && brd[i][j - ii].piece.color != brd[i][j].piece.color)
                        || brd[i][j - ii].occupied == 0) {
                            attacked[i][j - ii] = 1;
                            branch[5] = (brd[i][j - ii].occupied == 1) ? 0 : 1;
                        } else { branch[5] = 0; }
                } else { branch[5] = 0; }
                    }
                    if (branch[6] == 1) {
                    if ((i + ii) < 8) {
                        if (brd[i + ii][j].occupied 
                        && brd[i + ii][j].piece.type == 6) {
                        if (brd[i + ii][j].piece.color == 0 
                            && brd[i][j].piece.color == 1) {
                            black_attack = true;
                        } else if (brd[i + ii][j].piece.color == 1 
                                    && brd[i][j].piece.color == 0) {
                            white_attack = true;
                        }
                        }
                        if ((brd[i + ii][j].occupied == 1
                            && brd[i + ii][j].piece.color != brd[i][j].piece.color)
                            || brd[i + ii][j].occupied == 0) {
                            attacked[i + ii][j] = 1;
                            branch[6] = (brd[i + ii][j].occupied == 1) ? 0 : 1;
                        } else { branch[6] = 0; }
                    } else { branch[6] = 0; }
                    }
                    if (branch[7] == 1) {
                    if ((i - ii) >= 0) {
                        if (brd[i - ii][j].occupied 
                        && brd[i - ii][j].piece.type == 6) {
                        if (brd[i - ii][j].piece.color == 0 
                            && brd[i][j].piece.color == 1) {
                            black_attack = true;
                        } else if (brd[i - ii][j].piece.color == 1 
                                    && brd[i][j].piece.color == 0) {
                            white_attack = true;
                        }
                        }
                        if ((brd[i - ii][j].occupied == 1
                        && brd[i - ii][j].piece.color != brd[i][j].piece.color)
                        || brd[i - ii][j].occupied == 0) {
                            attacked[i - ii][j] = 1;
                            branch[7] = (brd[i - ii][j].occupied == 1) ? 0 : 1;
                        } else { branch[7] = 0; }
                    } else { branch[7] = 0; }
                }
            }
            break;
            case 6: // King
                if (i + 1 < 8) {
                    if ((brd[i + 1][j].occupied == 1 
                        && brd[i + 1][j].piece.color != brd[i][j].piece.color) 
                        || brd[i + 1][j].occupied == 0) {
                        attacked[i + 1][j] = 1;
                    }
                    if (j + 1 < 8) {
                        if ((brd[i + 1][j + 1].occupied == 1 
                        && brd[i + 1][j + 1].piece.color != brd[i][j].piece.color) 
                        || brd[i + 1][j + 1].occupied == 0) {
                        attacked[i + 1][j + 1] = 1;
                        }
                        if ((brd[i][j + 1].occupied == 1 
                        && brd[i][j + 1].piece.color != brd[i][j].piece.color) 
                        || brd[i][j + 1].occupied == 0) {
                        attacked[i][j + 1] = 1;
                        }
                    }
                    if (j - 1 >= 0) {
                        if ((brd[i + 1][j - 1].occupied == 1 
                        && brd[i + 1][j - 1].piece.color != brd[i][j].piece.color) 
                        || brd[i + 1][j - 1].occupied == 0) {
                        attacked[i + 1][j - 1] = 1;
                        }
                    }
                    }
                if (i - 1 >= 0) {
                    if ((brd[i - 1][j].occupied == 1 
                        && brd[i - 1][j].piece.color != brd[i][j].piece.color) 
                        || brd[i - 1][j].occupied == 0) {
                        attacked[i - 1][j] = 1;
                    }
                    if (j + 1 < 8) {
                        if ((brd[i - 1][j + 1].occupied == 1 
                        && brd[i - 1][j + 1].piece.color != brd[i][j].piece.color) 
                        || brd[i - 1][j + 1].occupied == 0) {
                        attacked[i - 1][j + 1] = 1;
                        }
                    }
                    if (j - 1 >= 0) {
                        if ((brd[i - 1][j - 1].occupied == 1 
                        && brd[i - 1][j - 1].piece.color != brd[i][j].piece.color) 
                        || brd[i - 1][j - 1].occupied == 0) {
                        attacked[i - 1][j - 1] = 1;
                        }
                        if ((brd[i][j - 1].occupied == 1 
                        && brd[i][j - 1].piece.color != brd[i][j].piece.color) 
                        || brd[i][j - 1].occupied == 0) {
                        attacked[i][j - 1] = 1;
                        }
                    }
                }
                break;
            default:
                break;
        } // Switch
    } // if occupied
    } // j loop
    } // i loop
}

void Board::check() { // Checks which king is under attack
    std::cout << "White: " << white_attack << std::endl;
    std::cout << "Black: " << black_attack << std::endl;
}

Board::~Board() = default;
// End of Board obj