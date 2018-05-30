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

void game_over_condition(board *plateau) {

  if (win(plateau) == 1) {
        plateau->state = PLAYER_X_WON_STATE;
    } else if (win(plateau) == -1) {
        plateau->state = PLAYER_O_WON_STATE;
    } else if (!full_grid(plateau)) {
        plateau->state = RUNNING_STATE;
    }
}

int get_case(int x, int y){

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

    if (plateau->tab[num_case].tab[num_case] == 0) {
        plateau->num_grid = num_case;
        plateau->last_grid = num_case;
        plateau->tab[plateau->num_grid].tab[num_case] = plateau->player;
        plateau->player *= -1;
        plateau->num_grid = num_case;
        game_over_condition(plateau);
    }
}
//void reset_game()

void click_on_cell(board *plateau, int x, int y) {

    if (plateau->state == RUNNING_STATE) {
        player_turn(plateau, x, y);
    }
    //else {
        //reset_game(plateau);
    //}
}