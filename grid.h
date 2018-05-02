#ifndef grid_H
#define grid_H
    typedef struct{
        int tab[9] ;
    }grid;

    typedef struct{
        grid tab[9] ;
        int player ;
        int num_grid;
        int last_grid;
    }board;

    board init(board main_board);
    int full_grid(board main_board);
    board turn(board , int);
    void draw(board main_board);
    int win(board main_board);
    int game_JCJ();
#endif // gridH_
