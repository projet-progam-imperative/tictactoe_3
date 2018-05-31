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
  SDL_Surface* croixImg= SDL_LoadBMP("img/croix.bmp");
  SDL_Surface* rondImg= SDL_LoadBMP("img/rond.bmp");
  SDL_Surface* x_winImg= SDL_LoadBMP("img/win_x_note.bmp");
  SDL_Surface* o_winImg= SDL_LoadBMP("img/win_o_note.bmp");
  SDL_Surface* tie_stateImg= SDL_LoadBMP("img/tie_state_note.bmp");


  if (SDL_Init(SDL_INIT_VIDEO) != 0 ){ //Gestion des erreurs d'init
      fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
      return EXIT_FAILURE;
  }

  //Création de la fenêtre
  fenetre = SDL_CreateWindow("TicTacToe - Power 3", SDL_WINDOWPOS_CENTERED,
                                                SDL_WINDOWPOS_CENTERED,
                                                780, 780,
                                                SDL_WINDOW_SHOWN);

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

  //gestion de l'erreur de chargement d'une des images
  if(!menuImg || !grilleImg || !croixImg || !rondImg || ! x_winImg || !o_winImg || !tie_stateImg )
  {
      printf("Erreur de chargement de l'image : %s",SDL_GetError());
      return -1;
  }


  //La texture grilleTexture contient maintenant l'image grilleImg
  SDL_Texture* grilleTexture = SDL_CreateTextureFromSurface(renderer,grilleImg);
  SDL_FreeSurface(grilleImg);

  //La texture de la croix
  SDL_Texture* croixTexture = SDL_CreateTextureFromSurface(renderer,croixImg);
  SDL_FreeSurface(croixImg);

  //La texture du rond
  SDL_Texture* rondTexture = SDL_CreateTextureFromSurface(renderer,rondImg);
  SDL_FreeSurface(rondImg);

  //La texture écran x gagne
  SDL_Texture* x_winTexture = SDL_CreateTextureFromSurface(renderer,x_winImg);
  SDL_FreeSurface(x_winImg);

  //La texture écran o gagne
  SDL_Texture* o_winTexture = SDL_CreateTextureFromSurface(renderer,o_winImg);
  SDL_FreeSurface(o_winImg);

  // La texture écran égalité
  SDL_Texture* tie_stateTexture = SDL_CreateTextureFromSurface(renderer,tie_stateImg);
  SDL_FreeSurface(tie_stateImg);

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

  // Initialisation plateu de jeux
  board plateau;
  plateau = init(plateau);

  if (fenetre){
  char cont = 1; /* Détermine si on continue la boucle principale */

      while ( cont != 0 ){
          SDL_PumpEvents(); // On demande à la SDL de mettre à jour les états sur la souris
          {
              int a;
              int b;

              if(SDL_GetMouseState(&a, &b) & SDL_BUTTON(1) && 300 <= a && 482 >= a && 351 <= b && 411 >= b){
                printf("Jouer\n");
                cont = 0;
                //SDL_Delay(2000);
              }
          }
      }

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

              if (plateau.state != MENU_STATE) {

                  case SDL_MOUSEBUTTONUP:
                    a = e.button.x;
                    b = e.button.y;

                    fprintf(stdout, "Position de la souris : %d;%d\n",a,b);
                    c = a - (a % 60);
                    d = b - (b % 60);
                    fprintf(stdout, "Modulo : %d;%d\n",c,d);
                    fprintf(stdout, "Modulo : %d;%d\n",(a / 60),(b / 60));

                    if ( plateau.state == 0 && (c!=0) && (c!=240) && (c!=480) && (c!=720) && (d!=0) && (d!=240) && (d!=480) && (d!=720) ) {
                      click_on_cell(&plateau, c, d);
                    }
                    else{
                      click_on_cell(&plateau, c, d);
                    }

                    break;
              }

            default: {}
           }
        }

        SDL_RenderClear(renderer);
        render_game(renderer, &plateau, grilleTexture, croixTexture, rondTexture, x_winTexture, o_winTexture, tie_stateTexture);
        SDL_RenderPresent(renderer);

      }

      // Destruction
      SDL_DestroyRenderer(renderer);
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
    main_board.state = MENU_STATE;
    return main_board;
}