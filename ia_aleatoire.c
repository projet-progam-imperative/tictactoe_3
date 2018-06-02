#include <stdlib.h>
#include <logic.h>
#include <game.h>
#include <ia.h>

//fonction qui applique la decision de l'IA aleatoire sur le plateau
// Codé par Leo
board turn_IA_alea(board main_board){
    int IA_turn;
    IA_turn = rand() % 9;
    main_board = sim_player_turn(main_board, IA_turn);
    return main_board;
}

// Codé par Leo et Thomas
void ia_alea_turn(board *plateau, int x, int y){

  if (plateau->player == PLAYER_O && plateau->vs == IAE_VS_IAH) {
    ia_turn(plateau, x, y);
  }

  else if (plateau->player == PLAYER_X && plateau->vs == P_VS_IAE) {
    player_turn(plateau, x, y);
  }

  else {
    *plateau = turn_IA_alea(*plateau);
    game_over_condition(plateau);
  }
}
