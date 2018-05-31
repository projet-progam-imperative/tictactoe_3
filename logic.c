#include <game.h>
#include <logic.h>

int win(board *plateau){
    int a, b, c, d, e, f, g, h;
    a = plateau->tab[plateau->last_grid].tab[0] + plateau->tab[plateau->last_grid].tab[1] + plateau->tab[plateau->last_grid].tab[2];
    b = plateau->tab[plateau->last_grid].tab[3] + plateau->tab[plateau->last_grid].tab[4] + plateau->tab[plateau->last_grid].tab[5];
    c = plateau->tab[plateau->last_grid].tab[6] + plateau->tab[plateau->last_grid].tab[7] + plateau->tab[plateau->last_grid].tab[8];
    d = plateau->tab[plateau->last_grid].tab[0] + plateau->tab[plateau->last_grid].tab[3] + plateau->tab[plateau->last_grid].tab[6];
    e = plateau->tab[plateau->last_grid].tab[1] + plateau->tab[plateau->last_grid].tab[4] + plateau->tab[plateau->last_grid].tab[7];
    f = plateau->tab[plateau->last_grid].tab[2] + plateau->tab[plateau->last_grid].tab[5] + plateau->tab[plateau->last_grid].tab[8];
    g = plateau->tab[plateau->last_grid].tab[0] + plateau->tab[plateau->last_grid].tab[4] + plateau->tab[plateau->last_grid].tab[8];
    h = plateau->tab[plateau->last_grid].tab[2] + plateau->tab[plateau->last_grid].tab[4] + plateau->tab[plateau->last_grid].tab[6];
    if(a == 3 || b == 3 || c == 3 || d == 3 || e == 3 || f == 3 || g == 3 || h == 3){
        return 1;
    }
    if(a == -3 || b == -3 || c == -3 || d == -3 || e == -3 || f == -3 || g == -3 || h == -3){
        return -1;
    }
    return 0;
}

int full_grid(board *plateau){
    int i;
    for(i=0;i<9;i++){
        if(plateau->tab[plateau->num_grid].tab[i] == 0){
            return 1;
        }
    }
    return 0;
}

int new_board(board *plateau){
    for(int i = 0;i<9;i++){
        for(int j = 0;j<9;j++){
            if(plateau->tab[i].tab[j] == 1 || plateau->tab[i].tab[j] == -1){
              return 0;
            }
        }
    }
    return 1;
}

int tie_state(board *plateau){
    for(int i = 0;i<9;i++){
        for(int j = 0;j<9;j++){
            if(plateau->tab[i].tab[j] == 0){
              return 0;
            }
        }
    }
    return 1;
}

void game_over_condition(board *plateau) {

  if (win(plateau) == 1) {
        plateau->state = PLAYER_X_WON_STATE;
    } else if (win(plateau) == -1) {
        plateau->state = PLAYER_O_WON_STATE;
    } else if (tie_state(plateau)) {
        plateau->state = TIE_STATE;
    }
}

int get_case(int x, int y){

    int a[3];
    int b[3];

    if (x == 60 || x == 300 || x == 540) {
      a[0] = 0;
      a[1] = 3;
      a[2] = 6;
    }
    if (x == 120 || x == 360 || x == 600) {
      a[0] = 1;
      a[1] = 4;
      a[2] = 7;
    }
    if (x == 180 || x == 420 || x == 660) {
      a[0] = 2;
      a[1] = 5;
      a[2] = 8;
    }
    if (y == 60 || y == 300 || y == 540) {
      b[0] = 0;
      b[1] = 1;
      b[2] = 2;
    }
    if (y == 120 || y == 360 || y == 600) {
      b[0] = 3;
      b[1] = 4;
      b[2] = 5;
    }
    if (y == 180 || y == 420 || y == 660) {
      b[0] = 6;
      b[1] = 7;
      b[2] = 8;
    }
    for (int i = 0; i < 3; i++) {
      if (a[i] == b[0]) {
        return b[0];
      }
      if (a[i] == b[1]) {
        return b[1];
      }
    }
  return b[2];
}

int get_grid(int x, int y){

  if (x < 240 && y < 240) {
    return 0;
  }
  if (x < 480 && y < 240) {
    return 1;
  }
  if (x < 720 && y < 240) {
    return 2;
  }
  if (x < 240 && y < 480) {
    return 3;
  }
  if (x < 480 && y < 480) {
    return 4;
  }
  if (x < 720 && y < 480) {
    return 5;
  }
  if (x < 240 && y < 720) {
    return 6;
  }
  if (x < 480 && y < 720) {
    return 7;
  }
  else{
    return 8;
  }
}

void player_turn(board *plateau, int x, int y) {
  //if(plateau.tab[plateau.num_grid].tab[num_case] == 0)

    int num_case = get_case(x, y);
    int num_grid = get_grid(x, y);

    if (new_board(plateau)) {
      plateau->num_grid = num_grid;
    }

    if (full_grid(plateau)) {
      if (plateau->tab[num_grid].tab[num_case] == 0) {
        plateau->last_grid = num_grid;
        plateau->tab[plateau->num_grid].tab[num_case] = plateau->player;
        plateau->player *= -1;
        plateau->num_grid = num_case;
      }
    }else{
      plateau->num_grid = num_case;
    }

    game_over_condition(plateau);
}

void reset_game(board *plateau)
{
    plateau->player = PLAYER_X;
    plateau->state = RUNNING_STATE;
    plateau->num_grid = 4;

    for(int i = 0;i<9;i++){
        for(int j = 0;j<9;j++){
            plateau->tab[i].tab[j] = 0;
        }
    }
}

void click_on_cell(board *plateau, int x, int y) {

    if (plateau->state == RUNNING_STATE) {
        player_turn(plateau, x, y);
    }
    else {
        reset_game(plateau);
    }
}