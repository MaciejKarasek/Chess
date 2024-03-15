#ifndef GAME_HPP
#define GAME_HPP

#ifndef LIBARIES
#define LIBARIES
#include <string>
#include <iostream>
#include <vector>
#include <map>
#endif // LIBARIES
#include "Board.hpp"

// Main game function
void game();
int handle_move(std::string move, std::string where, Board *board, int who);
#endif