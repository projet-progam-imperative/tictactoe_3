#ifndef LOGIC_H_
#define LOGIC_H_

#include<game.h>

// Codé par Leo et Thomas

void game_over_condition(board *plateau);
void click_on_cell(board *plateau, int x, int y);
int win(board *plateau);
void player_turn(board *plateau, int x, int y);
int full_grid(board *plateau);
int new_board(board *plateau);

#endif  // LOGIC_H_