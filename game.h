#ifndef GAME_H_
#define GAME_H_

#define EMPTY 0
#define PLAYER_X 1
#define PLAYER_O -1

#define MENU_STATE 5
#define RUNNING_STATE 0
#define PLAYER_X_WON_STATE 1
#define PLAYER_O_WON_STATE 2
#define TIE_STATE 3
#define QUIT_STATE 4

#define P_VS_P 1
#define P_VS_IAE 2
#define P_VS_IAH 3
#define IAE_VS_IAH 4
#define IAE_VS_IAE 5
#define IAH_VS_IAH 6

typedef struct{
    int tab[9] ;
}grid;

typedef struct{
    grid tab[9] ;
    int player ;
    int num_grid;
    int last_grid;
    int state;
    int vs;
}board;

board init(board main_board);

#endif  // GAME_H_
