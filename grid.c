#include <stdio.h>
#include<grid.h>
#include <IA.h>
#include <IAaleatoire.h>

//fonction qui initialise le plateau de jeu
board init(board main_board){
    int i,j;
    for(i = 0;i<9;i++){
        for(j = 0;j<9;j++){
            main_board.tab[i].tab[j] = 0;
        }
    }
    main_board.player = 1;
    main_board.num_grid = 4;
    return main_board;
}

//fonction qui test si la grille dans laquelle le joueur joue est remplie
int full_grid(board main_board){
    int i;
    for(i=0;i<9;i++){
        if(main_board.tab[main_board.num_grid].tab[i] == 0){
            return 1;
        }
    }
    return 0;
}

//fonction qui applique la decision des joueur sur le plateau
board turn(board main_board, int num_case){
    if(full_grid(main_board)){
        if(main_board.tab[main_board.num_grid].tab[num_case] == 0){
            main_board.last_grid = main_board.num_grid;
            main_board.tab[main_board.num_grid].tab[num_case] = main_board.player;
            main_board.player *= -1;
            main_board.num_grid = num_case;
        }   
    }else{
        main_board.num_grid = num_case;
    }
    return main_board;
}

//fonction temporaire qui dessine une representation dans le terminal
void draw(board main_board){
    int i,j,k;
    for(i = 0;i<9;i++){
        printf("\n\n");
        for(j = 0;j<3;j++){
            for(k = 0;k<3;k++){
                printf("%d ",main_board.tab[i].tab[j*3+k]);
            }
            printf("   ");
        }
    }
    printf("\n");
}

//fonction qui calcule si un joueur a gagner
int win(board main_board){
    int a, b, c, d, e, f, g, h;
    a = main_board.tab[main_board.last_grid].tab[0] + main_board.tab[main_board.last_grid].tab[1] + main_board.tab[main_board.last_grid].tab[2];
    b = main_board.tab[main_board.last_grid].tab[3] + main_board.tab[main_board.last_grid].tab[4] + main_board.tab[main_board.last_grid].tab[5];
    c = main_board.tab[main_board.last_grid].tab[6] + main_board.tab[main_board.last_grid].tab[7] + main_board.tab[main_board.last_grid].tab[8];
    d = main_board.tab[main_board.last_grid].tab[0] + main_board.tab[main_board.last_grid].tab[3] + main_board.tab[main_board.last_grid].tab[6];
    e = main_board.tab[main_board.last_grid].tab[1] + main_board.tab[main_board.last_grid].tab[4] + main_board.tab[main_board.last_grid].tab[7];
    f = main_board.tab[main_board.last_grid].tab[2] + main_board.tab[main_board.last_grid].tab[5] + main_board.tab[main_board.last_grid].tab[8];
    g = main_board.tab[main_board.last_grid].tab[0] + main_board.tab[main_board.last_grid].tab[4] + main_board.tab[main_board.last_grid].tab[8];
    h = main_board.tab[main_board.last_grid].tab[2] + main_board.tab[main_board.last_grid].tab[4] + main_board.tab[main_board.last_grid].tab[6];
    if(a == 3 || b == 3 || c == 3 || d == 3 || e == 3 || f == 3 || g == 3 || h == 3){
        return 1;
    }
    if(a == -3 || b == -3 || c == -3 || d == -3 || e == -3 || f == -3 || g == -3 || h == -3){
        return -1;
    }
    return 0;
}

//fonction qui gère les tours en joueur vs joueur
int game_JCJ(){
    board plateau;
    plateau = init(plateau);
    int c = 0;
    int winner = 0;
    while(winner == 0){
        draw(plateau);
        printf("entrer le num de la case (0 -> 8)");
        while(c > 57 || c < 47){
            c = getchar();
        }
        c = c - 48;
        plateau = turn(plateau,c);
        winner = win(plateau);
    }
    draw(plateau);
    return winner;
}

int main(){
    int winner;
    winner = game_JCP_IA();
    switch(winner){
        case 1:
            printf("Le joueur 1 a gagné\n");
            break;
        case -1:
            printf("Le joueur 2 a gagné\n");
            break;
    }
    return 0;
}
