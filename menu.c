#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include <game.h>
#include <logic.h>
#include <rendering.h>

// Inspiration pour l'utilisation de SDL
//https://github.com/tsoding/profun/tree/master/procedural

// Fichier codé par Thomas


void game(board *plateau, SDL_Renderer *renderer, SDL_Texture* grilleTexture,
  SDL_Texture* croixTexture, SDL_Texture* rondTexture, SDL_Texture* x_winTexture,
   SDL_Texture* o_winTexture, SDL_Texture* tie_stateTexture,
   SDL_Texture* contour_xTexture, SDL_Texture* contour_oTexture);

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
  SDL_Surface* contour_xImg= SDL_LoadBMP("img/contour_x.bmp");
  SDL_Surface* contour_oImg= SDL_LoadBMP("img/contour_o.bmp");


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

  // La texture du contour
  SDL_Texture* contour_xTexture = SDL_CreateTextureFromSurface(renderer,contour_xImg);
  SDL_FreeSurface(contour_xImg);

  // La texture du contour
  SDL_Texture* contour_oTexture = SDL_CreateTextureFromSurface(renderer,contour_oImg);
  SDL_FreeSurface(contour_oImg);

  //La texture menuTexture contient maintenant l'image menuImg
  SDL_Texture* menuTexture = SDL_CreateTextureFromSurface(renderer,menuImg);

  SDL_FreeSurface(menuImg); //Destruction surface menu

  // Initialisation plateu de jeux
  board plateau;
  plateau = init(plateau);

  if (fenetre){

    int cont = 1;
    /* Boucle principale */
      while ( cont != 0 ){
        plateau.state = MENU_STATE;
        // Gestion des événements
          SDL_Event e;
          while (SDL_PollEvent(&e)) {
              int a;
              int b;

              switch (e.type) {

                case SDL_QUIT:
                  cont = 0;
                  break;

                case SDL_MOUSEBUTTONDOWN:
                  a = e.button.x;
                  b = e.button.y;

                  //Choix des différents modes de jeu

                  if(SDL_GetMouseState(&a, &b) & SDL_BUTTON(1) && 263 <= a && 518 >= a && 334 <= b && 367 >= b){
                    plateau.vs = P_VS_P;
                    game(&plateau, renderer, grilleTexture,
                      croixTexture, rondTexture,
                      x_winTexture, o_winTexture, tie_stateTexture,
                       contour_xTexture, contour_oTexture);

                  }
                  if(SDL_GetMouseState(&a, &b) & SDL_BUTTON(1) && 256 <= a && 522 >= a && 398 <= b && 433 >= b){
                    plateau.vs = P_VS_IAE;
                    game(&plateau, renderer, grilleTexture, croixTexture, rondTexture, x_winTexture, o_winTexture, tie_stateTexture, contour_xTexture, contour_oTexture);
                  }
                  if(SDL_GetMouseState(&a, &b) & SDL_BUTTON(1) && 255 <= a && 524 >= a && 468 <= b && 498 >= b){
                    plateau.vs = P_VS_IAH;
                    game(&plateau, renderer, grilleTexture, croixTexture, rondTexture, x_winTexture, o_winTexture, tie_stateTexture, contour_xTexture, contour_oTexture);
                  }
                  if(SDL_GetMouseState(&a, &b) & SDL_BUTTON(1) && 246 <= a && 533 >= a && 532 <= b && 560 >= b){
                    plateau.vs = IAE_VS_IAH;
                    game(&plateau, renderer, grilleTexture, croixTexture, rondTexture, x_winTexture, o_winTexture, tie_stateTexture, contour_xTexture, contour_oTexture);
                  }
                  if(SDL_GetMouseState(&a, &b) & SDL_BUTTON(1) && 244 <= a && 531 >= a && 590 <= b && 626 >= b){
                    plateau.vs = IAE_VS_IAE;
                    game(&plateau, renderer, grilleTexture, croixTexture, rondTexture, x_winTexture, o_winTexture, tie_stateTexture, contour_xTexture, contour_oTexture);
                  }
                  if(SDL_GetMouseState(&a, &b) & SDL_BUTTON(1) && 244 <= a && 534 >= a && 654 <= b && 683 >= b){
                    plateau.vs = IAH_VS_IAH;
                    game(&plateau, renderer, grilleTexture, croixTexture, rondTexture, x_winTexture, o_winTexture, tie_stateTexture, contour_xTexture, contour_oTexture);
                  }
                  break;
            default: {}
            }
          }

          //Affichage de menuTexture
          SDL_Rect position;
          position.x = 0;
          position.y = 0;
          SDL_QueryTexture(menuTexture, NULL, NULL, &position.w, &position.h);
          SDL_RenderCopy(renderer,menuTexture,NULL,&position);
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

void game(board *plateau, SDL_Renderer *renderer, SDL_Texture* grilleTexture,
  SDL_Texture* croixTexture, SDL_Texture* rondTexture, SDL_Texture* x_winTexture,
   SDL_Texture* o_winTexture, SDL_Texture* tie_stateTexture,
    SDL_Texture* contour_xTexture, SDL_Texture* contour_oTexture){

  SDL_Event e;
  while (plateau->state != QUIT_STATE) {

    while (SDL_PollEvent(&e)) {
        int a;
        int b;
        int c;
        int d;

        switch (e.type) {

          case SDL_QUIT:
            plateau->state = QUIT_STATE;
            break;

          case SDL_MOUSEBUTTONUP:
            a = e.button.x;
            b = e.button.y;

            c = a - (a % 60);
            d = b - (b % 60);

            if ( plateau->state == 0 && (c!=0) && (c!=240) && (c!=480) && (c!=720) && (d!=0) && (d!=240) && (d!=480) && (d!=720) ) {
              click_on_cell(plateau, c, d);
            }
            else{
              click_on_cell(plateau, c, d);
            }

            break;

        default: {}
       }
    }

    SDL_RenderClear(renderer);
    render_game(renderer, plateau, grilleTexture, croixTexture, rondTexture, x_winTexture, o_winTexture, tie_stateTexture, contour_xTexture, contour_oTexture);
    SDL_RenderPresent(renderer);

  }
}

//Initialisation
board init(board main_board){
    main_board.state = MENU_STATE;
    return main_board;
}