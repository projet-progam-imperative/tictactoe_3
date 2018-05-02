#ifndef IA_H
#define IA_H
    #include<grid.h>
    #include <IAaleatoire.h>
    
    typedef struct{
        float gain;
        float perte;
        float nb_simulation;
    }esperance;
    
    int board_equal(board a, board b);
    int decision(int taille, esperance* tab);
    board turn_IA_simulation(board simul);
    int game_JCP_IA();
#endif // IAH_
