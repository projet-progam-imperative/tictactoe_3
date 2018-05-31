#include <stdlib.h>
#include <logic.h>
#include <game.h>
#include <ia.h>

//fonction qui applique la decision de l'IA aleatoire sur le plateau
board turn_IA_alea(board main_board){
    int IA_turn;
    IA_turn = rand() % 9;
    main_board = sim_player_turn(main_board, IA_turn);
    return main_board;
}

void ia_alea_turn(board *plateau, int x, int y){
    if (plateau->player == PLAYER_X && plateau->vs == P_VS_IAE) {

        player_turn(plateau, x, y);
  }

  else {
    *plateau = turn_IA_alea(*plateau);
  }
}