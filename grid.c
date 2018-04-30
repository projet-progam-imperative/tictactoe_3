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

int full_grid(board main_board){
    int i;
    for(i=0;i<9;i++){
        if(main_board.tab[main_board.num_grid].tab[i] == 0){
            return 1;
        }
    }
    return 0;
}

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

board turn_IA_alea(board main_board){
    int IA_turn;
    IA_turn = rand() % 9;
    main_board = turn(main_board, IA_turn);
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

int decision(int taille, int* tab){
    int max, i, index;
    index = 0;
    max = tab[0];
    for(i=0;i<taille;i++){
        if(max > tab[i]){
            max = tab[i];
            index = i;
        }
    }
    return index;
}

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
    int possible_val[taille] ;
    for(i=0;i<taille;i++){
        possible_val[i] = 0;
        int j;
        for(j=0;j<100;j++){
            board test = possible[i];
            int winner = 0;
            while(winner == 0){
                test = turn_IA_alea(test);
                winner = win(test);
            }
            possible_val[i] += winner;
        }
    }
    return simul = possible[decision(taille, possible_val)];
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
            plateau = turn_IA_alea(plateau);
        }
        winner = win(plateau);
    }
    draw(plateau);
    return winner;
}

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
