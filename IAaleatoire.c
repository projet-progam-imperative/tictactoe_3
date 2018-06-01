#include <stdio.h>
#include <stdlib.h>
#include <IAaleatoire.h>
#include <grid.h>

//fonction qui applique la decision de l'IA aleatoire sur le plateau
board turn_IA_alea(board main_board){
    int IA_turn;
    IA_turn = rand() % 9;
    main_board = turn(main_board, IA_turn);
    return main_board;
}

//fonction qui gère les tours en joueur vs IA qui joue aleatoirement
int game_JCP_alea(){
    board plateau;
    plateau = init(plateau);
    int c=0;
    int winner = 0;
    while(winner == 0){
        if(plateau.player == 1){
            draw(plateau);
            printf("entrer le num de la case (0 -> 8)");
            while(c > 57 || c < 47){
                c = getchar();
            }
            c = c - 48;
            plateau = turn(plateau,c);
        }else{
            plateau = turn_IA_alea(plateau);
        }
        winner = win(plateau);
    }
    draw(plateau);
    return winner;
}
