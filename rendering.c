#include <SDL2/SDL.h>

#include <game.h>
#include <rendering.h>
#include <logic.h>

// Fichié codé par Thomas

int matricex[9][9] = { {60,120,180,60,120,180,60,120,180},{300,360,420,300,360,420,300,360,420},{540,600,660,540,600,660,540,600,660},{60,120,180,60,120,180,60,120,180},{300,360,420,300,360,420,300,360,420},{540,600,660,540,600,660,540,600,660},{60,120,180,60,120,180,60,120,180},{300,360,420,300,360,420,300,360,420},{540,600,660,540,600,660,540,600,660}};
int matricey[9][9] = {{60,60,60,120,120,120,180,180,180},{60,60,60,120,120,120,180,180,180},{60,60,60,120,120,120,180,180,180},{300,300,300,360,360,360,420,420,420},{300,300,300,360,360,360,420,420,420},{300,300,300,360,360,360,420,420,420},{540,540,540,600,600,600,660,660,660},{540,540,540,600,600,600,660,660,660},{540,540,540,600,600,600,660,660,660}};

void render_contour(SDL_Renderer *renderer, board *plateau,
  SDL_Texture* contour_xTexture, SDL_Texture* contour_oTexture){

  SDL_Rect position;
  position.x = matricex[plateau->num_grid][0] - 3;
  position.y = matricey[plateau->num_grid][0] - 3;

  if (plateau->player == PLAYER_X && (plateau->vs == P_VS_P || plateau->vs == P_VS_IAE || plateau->vs == P_VS_IAH)) {
    SDL_QueryTexture(contour_xTexture, NULL, NULL, &position.w, &position.h);
    SDL_RenderCopy(renderer,contour_xTexture,NULL,&position);
  }
  if (plateau->player == PLAYER_O && plateau->vs == P_VS_P){
    SDL_QueryTexture(contour_oTexture, NULL, NULL, &position.w, &position.h);
    SDL_RenderCopy(renderer,contour_oTexture,NULL,&position);
  }

}

void render_grid(SDL_Renderer *renderer, SDL_Texture* grilleTexture) {

  //Affichage de grilleTexture
  SDL_Rect position;
  position.x = 0;
  position.y = 0;
  SDL_QueryTexture(grilleTexture, NULL, NULL, &position.w, &position.h);
  SDL_RenderCopy(renderer,grilleTexture,NULL,&position);

}

void render_note(SDL_Renderer *renderer, SDL_Texture* noteTexture) {

  //Affichage de grilleTexture
  SDL_Rect position;
  position.x = 0;
  position.y = 0;
  SDL_QueryTexture(noteTexture, NULL, NULL, &position.w, &position.h);
  SDL_RenderCopy(renderer,noteTexture,NULL,&position);

}

void render_x(SDL_Renderer *renderer, int x, int y, SDL_Texture* croixTexture) {

  int c = matricex[x][y];
  int d = matricey[x][y];

  SDL_Rect position;
  position.x = c + 5;
  position.y = d + 5;
  SDL_QueryTexture(croixTexture, NULL, NULL, &position.w, &position.h);
  SDL_RenderCopy(renderer,croixTexture,NULL,&position);
}

void render_o(SDL_Renderer *renderer, int x, int y, SDL_Texture* rondTexture) {

    int c = matricex[x][y];
    int d = matricey[x][y];

    SDL_Rect position;
    position.x = c + 5;
    position.y = d + 5;
    SDL_QueryTexture(rondTexture, NULL, NULL, &position.w, &position.h);
    SDL_RenderCopy(renderer,rondTexture,NULL,&position);
}

void render_board(SDL_Renderer *renderer, board *plateau, SDL_Texture* croixTexture, SDL_Texture* rondTexture) {

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (plateau->tab[i].tab[j] == PLAYER_X) {
              render_x(renderer, i, j, croixTexture);
            }

            if (plateau->tab[i].tab[j] == PLAYER_O) {
              render_o(renderer, i, j, rondTexture);
            }
        }
    }
  }


void render_running_state(SDL_Renderer *renderer, board *plateau,
   SDL_Texture* grilleTexture, SDL_Texture* croixTexture,
    SDL_Texture* rondTexture, SDL_Texture* contour_xTexture, SDL_Texture* contour_oTexture) {

    render_grid(renderer, grilleTexture);
    render_board(renderer, plateau, croixTexture, rondTexture);
    if (!new_board(plateau)) {
      render_contour(renderer, plateau, contour_xTexture, contour_oTexture);
    }

}

void render_game_over_state(SDL_Renderer *renderer, SDL_Texture* noteTexture) {

    render_note(renderer, noteTexture);
}



void render_game(SDL_Renderer *renderer, board *plateau, SDL_Texture *grilleTexture,
   SDL_Texture* croixTexture, SDL_Texture* rondTexture, SDL_Texture* x_winTexture,
   SDL_Texture* o_winTexture, SDL_Texture* tie_stateTexture,
   SDL_Texture* contour_xTexture, SDL_Texture* contour_oTexture) {

    if (plateau->state == RUNNING_STATE) {
      render_running_state(renderer, plateau, grilleTexture, croixTexture, rondTexture, contour_xTexture, contour_oTexture);
    }

    if (plateau->state == PLAYER_X_WON_STATE) {
      render_running_state(renderer, plateau, grilleTexture, croixTexture, rondTexture, contour_xTexture, contour_oTexture);
      render_game_over_state(renderer, x_winTexture);
    }

    if (plateau->state == PLAYER_O_WON_STATE) {
      render_running_state(renderer, plateau, grilleTexture, croixTexture, rondTexture, contour_xTexture, contour_oTexture);
      render_game_over_state(renderer, o_winTexture);
    }

    if (plateau->state == TIE_STATE) {
      render_running_state(renderer, plateau, grilleTexture, croixTexture, rondTexture, contour_xTexture, contour_oTexture);
      render_game_over_state(renderer, tie_stateTexture);
    }

}