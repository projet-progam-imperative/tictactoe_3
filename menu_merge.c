#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include <game.h>
#include <logic.h>
#include <rendering.h>

//void draw_choice(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y);

int main(int argc, char *argv[]){

  SDL_Window* fenetre; //Déclaration de la fenêtre
  SDL_Renderer* renderer; //Déclaration du renderer
  // Déclaration images
  SDL_Surface* menuImg= SDL_LoadBMP("img/menu.bmp");
  SDL_Surface* grilleImg= SDL_LoadBMP("img/grille.bmp");

  if (SDL_Init(SDL_INIT_VIDEO) != 0 ){ //Gestion des erreurs d'init
      fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
      return EXIT_FAILURE;
  }

  //Création de la fenêtre
  fenetre = SDL_CreateWindow("TicTacToe - Power 3", SDL_WINDOWPOS_CENTERED,
                                                SDL_WINDOWPOS_CENTERED,
                                                780, 780,
                                                SDL_WINDOW_RESIZABLE);

  if(fenetre == NULL) //Gestion des erreurs fenêtre
  {
      printf("Erreur lors de la creation d'une fenetre : %s",SDL_GetError());
      return EXIT_FAILURE;
  }

  renderer = SDL_CreateRenderer(fenetre, -1,
     SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Création du renderer

  if(renderer == NULL)//gestion des erreurs renderer
  {
      printf("Erreur lors de la creation d'un renderer : %s",SDL_GetError());
      return EXIT_FAILURE;
  }

  if(!menuImg || !grilleImg)//gestion des erreurs images
  {
      printf("Erreur de chargement de l'image : %s",SDL_GetError());
      return -1;
  }

  //La texture menuTexture contient maintenant l'image menuImg
  SDL_Texture* menuTexture = SDL_CreateTextureFromSurface(renderer,menuImg);

  SDL_FreeSurface(menuImg); //Destruction surface menu

  //Affichage de menuTexture
  SDL_Rect position;
  position.x = 0;
  position.y = 0;
  SDL_QueryTexture(menuTexture, NULL, NULL, &position.w, &position.h);
  SDL_RenderCopy(renderer,menuTexture,NULL,&position);
  SDL_RenderPresent(renderer);

  if (fenetre){
  char cont = 1; /* Détermine si on continue la boucle principale */

      while ( cont != 0 ){
          SDL_PumpEvents(); // On demande à la SDL de mettre à jour les états sur la souris
          {
              int a;
              int b;

              if(SDL_GetMouseState(&a, &b) & SDL_BUTTON(1) && 300 <= a && 482 >= a && 351 <= b && 411 >= b){
                printf("Jouer\n");

                //La texture grilleTexture contient maintenant l'image menuImg
                SDL_Texture* grilleTexture = SDL_CreateTextureFromSurface(renderer,grilleImg);
                SDL_FreeSurface(grilleImg);

                //Affichage de grilleTexture
                SDL_Rect position;
                position.x = 0;
                position.y = 0;
                SDL_QueryTexture(grilleTexture, NULL, NULL, &position.w, &position.h);
                SDL_RenderCopy(renderer,grilleTexture,NULL,&position);
                SDL_RenderPresent(renderer);

                //game_start();

                //SDL_Delay(500); //Pause de 1/2 seconde

                cont = 0;
              }
          }
      }

      board plateau;
      plateau = init(plateau);

      SDL_Event e;
      while (plateau.state != QUIT_STATE) {

        while (SDL_PollEvent(&e)) {
            int a;
            int b;
            int c;
            int d;

            switch (e.type) {

              case SDL_QUIT:
                plateau.state = QUIT_STATE;
                break;

              //if(SDL_GetMouseState(&a, &b) & SDL_BUTTON(1)) {
              case SDL_MOUSEBUTTONDOWN:
                a = e.button.x;
                b = e.button.y;

                fprintf(stdout, "Position de la souris : %d;%d\n",a,b);
                c = a - (a % 60);
                d = b - (b % 60);
                fprintf(stdout, "Modulo : %d;%d\n",c,d);

                if ( (c!=0) && (c!=240) && (c!=480) && (c!=720) && (d!=0) && (d!=240) && (d!=480) && (d!=720) ) {
                  click_on_cell(&plateau, c, d);
                }

                break;

            default: {}
           }
        }

        SDL_RenderClear(renderer);
        render_game(renderer, &plateau);
        SDL_RenderPresent(renderer);

      }

      // Destruction
      //SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(fenetre);

      // Quitter SDL
      SDL_Quit();

  }

  return 0;

}

board init(board main_board){
    int i,j;
    for(i = 0;i<9;i++){
        for(j = 0;j<9;j++){
            main_board.tab[i].tab[j] = 0;
        }
    }
    main_board.player = PLAYER_X;
    main_board.state = RUNNING_STATE;
    //main_board.num_grid = 4;
    return main_board;
}