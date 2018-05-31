#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include <grid.h>

//void draw_choice(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y);

int main(int argc, char *argv[]){

  SDL_Window* fenetre; //Déclaration de la fenêtre
  SDL_Renderer* renderer; //Déclaration du renderer
  // Déclaration images
  SDL_Surface* menuImg= SDL_LoadBMP("img/menu.bmp");
  SDL_Surface* grilleImg= SDL_LoadBMP("img/grille.bmp");
  SDL_Surface* rondImg= SDL_LoadBMP("img/rond.bmp");
  SDL_Surface* croixImg= SDL_LoadBMP("img/croix.bmp");

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

  if(!menuImg || !grilleImg || !rondImg || !croixImg)//gestion des erreurs images
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

                game_start();

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


                SDL_Delay(500); //Pause de 1/2 seconde

                cont = 0;
              }
          }
      }

      //La texture rondTexture contient maintenant l'image rondImg
      SDL_Texture* rondTexture = SDL_CreateTextureFromSurface(renderer,rondImg);
      SDL_FreeSurface(rondImg);
      SDL_Texture* croixTexture = SDL_CreateTextureFromSurface(renderer,croixImg);
      SDL_FreeSurface(croixImg);
      int tour = 0;

      while ( cont != -1 ) {

        SDL_PumpEvents(); // On demande à la SDL de mettre à jour les états sur la souris
        {
            int a;
            int b;
            int c;
            int d;

            if(SDL_GetMouseState(&a, &b) & SDL_BUTTON(1)) {

              fprintf(stdout, "Position de la souris : %d;%d\n",a,b);
               c = a - (a % 60);
               d = b - (b % 60);
               fprintf(stdout, "Modulo : %d;%d\n",c,d);

              if ( (c!=0) && (c!=240) && (c!=480) && (c!=720) && (d!=0) && (d!=240) && (d!=480) && (d!=720) ) {

                if (tour == 0) {
                  printf("Rond\n");

                  //Affichage de rondTexture

                  SDL_Rect position;
                  position.x = c + 5;
                  position.y = d + 5;
                  SDL_QueryTexture(rondTexture, NULL, NULL, &position.w, &position.h);
                  SDL_RenderCopy(renderer,rondTexture,NULL,&position);
                  SDL_RenderPresent(renderer);

                  //void draw_choice(SDL_Renderer* renderer, SDL_Texture* rondTexture, int c, int d);

                  tour = 1;
                  SDL_Delay(500); //Pause de 1/2 seconde
                }
                else{
                  printf("Croix\n");

                  //Affichage de rondTexture
                  SDL_Rect position;
                  position.x = c + 5;
                  position.y = d + 5;
                  SDL_QueryTexture(croixTexture, NULL, NULL, &position.w, &position.h);
                  SDL_RenderCopy(renderer,croixTexture,NULL,&position);
                  SDL_RenderPresent(renderer);
                  tour = 0;
                  SDL_Delay(500); //Pause de 1/2 seconde
                }
              }
            }
        }
      }

      // Destruction
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(fenetre);

      // Quitter SDL
      SDL_Quit();

  }

  return 0;

}

//void draw_choice(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y){

  //Affichage de rondTexture
//  SDL_Rect position;
//  position.x = x + 5;
//  position.y = y + 5;
//  SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
//  SDL_RenderCopy(renderer,texture,NULL,&position);
//  SDL_RenderPresent(renderer);
//
//}
















