#ifndef LOGIC_H_
#define LOGIC_H_

void click_on_cell(board *plateau, int x, int y);
int win(board *plateau);
void player_turn(board *plateau, int x, int y);
int full_grid(board *plateau);

#endif  // LOGIC_H_