#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int tab[9] ;
}grid;

typedef struct{
    grid tab[9] ;
    int player ;
    int num_grid;
    int last_grid;
}board;

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

board turn(board main_board, int num_case){
    if(main_board.tab[main_board.num_grid].tab[num_case] == 0){
        main_board.last_grid = main_board.num_grid;
        main_board.tab[main_board.num_grid].tab[num_case] = main_board.player;
        main_board.player *= -1;
        main_board.num_grid = num_case;
    }
    return main_board;
}

void draw(board main_board){
    int i,j;
    for(i = 0;i<9;i++){
        for(j = 0;j<9;j++){
            printf("%d ",main_board.tab[i].tab[j]);
        }
        printf("\n \n");
    }
}

int win(board main_board){
    int a, b, c, d, e, f, g, h;
    a = main_board.tab[main_board.last_grid].tab[0] + main_board.tab[main_board.last_grid].tab[1] + main_board.tab[main_board.last_grid].tab[2];
    b = main_board.tab[main_board.last_grid].tab[3] + main_board.tab[main_board.last_grid].tab[4] + main_board.tab[main_board.last_grid].tab[5];
    c = main_board.tab[main_board.last_grid].tab[6] + main_board.tab[main_board.last_grid].tab[7] + main_board.tab[main_board.last_grid].tab[8];
    d = main_board.tab[main_board.last_grid].tab[0] + main_board.tab[main_board.last_grid].tab[3] + main_board.tab[main_board.last_grid].tab[6];
    e = main_board.tab[main_board.last_grid].tab[2] + main_board.tab[main_board.last_grid].tab[4] + main_board.tab[main_board.last_grid].tab[7];
    f = main_board.tab[main_board.last_grid].tab[3] + main_board.tab[main_board.last_grid].tab[5] + main_board.tab[main_board.last_grid].tab[8];
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

int game_JCJ(){
    board plateau;
    plateau = init(plateau);
    int c=0;
    int winner = 0;
    while(winner == 0){
        draw(plateau);
        printf("entrer le num de la case (0 -> 8)");
        scanf("%d",&c);
        plateau = turn(plateau,c);
        winner = win(plateau);
    }
    draw(plateau);
    return winner;
}

int game_JCP_alea(){
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
            int IA_turn;
            IA_turn = rand() % 9;
            plateau = turn(plateau, IA_turn);
        }
        winner = win(plateau);
    }
    draw(plateau);
    return winner;
}

int main(){
    int winner;
    winner = game_JCP_alea();
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
