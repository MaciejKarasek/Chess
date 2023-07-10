#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <iostream>
#include "chess.hpp"

// Main game function
void game();
int handle_move(std::string move, std::string where, Board *board);
#endif