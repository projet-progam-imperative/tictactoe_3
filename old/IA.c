#include <stdio.h>
#include <IA.h>
#include <grid.h>
#include <IAaleatoire.h>

//fonction qui test si deux plateaux sont egaux
int board_equal(board a, board b){
    int i, j;
    for(i = 0;i<9;i++){
        for(j = 0;j<9;j++){
            if(a.tab[i].tab[j] != b.tab[i].tab[j]){
                return 0;
            }
        }
    }
    if(a.num_grid != b.num_grid) return 0;
    if(a.player != b.player) return 0;
    if(a.last_grid != b.last_grid) return 0;
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
board turn_IA_simulation(board simul){
    int i,taille = 0;
    board possible_tmp[9];
    for(i=0;i<9;i++){
        possible_tmp[i] = turn(simul,i);
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
                winner = win(test);
            }
            switch(winner){
                case -1:
                    possible_val[i].gain +=1;
                    break;
                case 1:
                    possible_val[i].perte +=1;
                    break;
            }
        }
    }
    return simul = possible[decision(taille, possible_val)];
}

//fonction qui gère les tours en joueur vs IA "réfléchi"
int game_JCP_IA(){
    board plateau;
    plateau = init(plateau);
    int c=0;
    int winner = 0;
    while(winner == 0){
        if(plateau.player == 1){
            draw(plateau);
            printf("entrer le num de la case (0 -> 8)");
            scanf("%d",&c);
            plateau = turn(plateau,c);
        }else{
            plateau = turn_IA_simulation(plateau);
        }
        winner = win(plateau);
    }
    draw(plateau);
    return winner;
}
