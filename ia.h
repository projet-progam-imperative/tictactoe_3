#ifndef IA_H
#define IA_H
    #include<game.h>

    typedef struct{
        float gain;
        float perte;
        float nb_simulation;
    }esperance;

    int board_equal(board a, board *b);
    int decision(int taille, esperance* tab);
    board turn_IA_simulation(board *simul);
    void ia_turn(board *plateau, int x, int y);
#endif // IAH_