#ifndef IA_H
#define IA_H
    #include<game.h>

    // Codé par Leo et Thomas

    typedef struct{
        float gain;
        float perte;
        float nb_simulation;
    }esperance;

    int board_equal(board a, board *b);
    int decision(int taille, esperance* tab);
    board turn_IA_simulation(board *simul);
    void ia_turn(board *plateau, int x, int y);
    board sim_player_turn(board plateau, int num_case);
#endif // IAH_