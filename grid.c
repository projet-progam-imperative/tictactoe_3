#include <stdio.h>

typedef struct{
    int tab[9] ;
}grid;

typedef struct{
    grid tab[9] ;
    int player ;
    int num_grid;
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

int win(board main_board ,int choix){
    int i;
    for(i = 0; i; i++){
    }
}

int main(){
    board plateau;
    plateau = init(plateau);
    int c=0;
    while(plateau.num_grid < 9){
        draw(plateau);
        printf("entrer le num de la case (0 -> 8)");
        scanf("%d",&c);
        plateau = turn(plateau,c);
    }
    return 0;
}
