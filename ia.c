#include <stdlib.h>
#include <ia.h>
#include <ia_aleatoire.h>
#include <logic.h>
#include <game.h>

//simule le tour de l'autre joueur
board sim_player_turn(board plateau, int num_case){
    if (full_grid(&plateau)) {
      if (plateau.tab[plateau.num_grid].tab[num_case] == 0) {
        plateau.last_grid = plateau.num_grid;
        plateau.tab[plateau.num_grid].tab[num_case] = plateau.player;
        plateau.player *= -1;
        plateau.num_grid = num_case;
      }
    }else{
      plateau.num_grid = num_case;
    }
  return plateau;
}

//fonction qui test si deux plateaux sont egaux
int board_equal(board a, board *b){
    int i, j;
    for(i = 0;i<9;i++){
        for(j = 0;j<9;j++){
            if(a.tab[i].tab[j] != b->tab[i].tab[j]){
                return 0;
            }
        }
    }
    if(a.num_grid != b->num_grid) return 0;
    if(a.player != b->player) return 0;
    if(a.last_grid != b->last_grid) return 0;
    return 1;
}

//fonction qui permet a l'IA de choisir la case sur laquelle jouer
int decision(int taille, esperance* tab){
    int index, i;
    float esp[taille], max;
    for(i=0;i<taille;i++){
        float proba_gain, proba_perte;
        proba_gain = tab[i].gain / tab[i].nb_simulation;
        proba_perte = tab[i].perte / tab[i].nb_simulation;
        esp[i] = (proba_gain * tab[i].gain) - (proba_perte * tab[i].perte);
    }
    index = 0;
    max = esp[0];
    for(i=0;i<taille;i++){
        if(max < esp[i]){
            max = esp[i];
            index = i;
        }
    }
    return index;
}

//fonction qui applique la decision de l'IA "réfléchi" sur le plateau
board turn_IA_simulation(board *simul){
    int i,taille = 0;
    board possible_tmp[9];
    for(i=0;i<9;i++){
        possible_tmp[i] = sim_player_turn(*simul,i);
        if(board_equal(possible_tmp[i], simul) != 1){
            taille += 1;
        }
    }
    board possible[taille];
    int index = 0;
    for(i=0;i<9;i++){
        if(board_equal(possible_tmp[i], simul) != 1){
            possible[index] = possible_tmp[i];
            index +=1;
        }
    }
    esperance possible_val[taille] ;
    for(i=0;i<taille;i++){
        possible_val[i].nb_simulation = 1000;
        possible_val[i].gain = 0;
        possible_val[i].perte = 0;
        int j;
        for(j=0;j<possible_val[0].nb_simulation;j++){
            board test = possible[i];
            int winner = 0;
            while(winner == 0){
                test = turn_IA_alea(test);
                winner = win(&test);
            }
            if (winner == -1) {
              if (simul->player == -1) {
                possible_val[i].gain +=1;
              }
              else{
                possible_val[i].perte +=1;
              }
            }
            if (winner == 1){
              if (simul->player == -1) {
                possible_val[i].perte +=1;
              }
              else{
                possible_val[i].gain +=1;
              }
            }
        }
    }
    simul = &possible[decision(taille, possible_val)];
    return *simul;
}


void ia_turn(board *plateau, int x, int y) {

    if (plateau->player == PLAYER_X && plateau->vs == P_VS_IAH) {

        player_turn(plateau, x, y);
  }

  else {
    *plateau = turn_IA_simulation(plateau);
    game_over_condition(plateau);
  }


}