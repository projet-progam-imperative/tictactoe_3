#include <SDL2/SDL.h>

#include <game.h>
#include <rendering.h>

int matricex[9][9] = { {60,120,180,60,120,180,60,120,180},{300,360,420,300,360,420,300,360,420},{540,600,660,540,600,660,540,600,660},{60,120,180,60,120,180,60,120,180},{300,360,420,300,360,420,300,360,420},{540,600,660,540,600,660,540,600,660},{60,120,180,60,120,180,60,120,180},{300,360,420,300,360,420,300,360,420},{540,600,660,540,600,660,540,600,660}};
int matricey[9][9] = {{60,60,60,120,120,120,180,180,180},{60,60,60,120,120,120,180,180,180},{60,60,60,120,120,120,180,180,180},{300,300,300,360,360,360,420,420,420},{300,300,300,360,360,360,420,420,420},{300,300,300,360,360,360,420,420,420},{540,540,540,600,600,600,660,660,660},{540,540,540,600,600,600,660,660,660},{540,540,540,600,600,600,660,660,660}};

void render_grid(SDL_Renderer *renderer, SDL_Texture* grilleTexture) {

  //Affichage de grilleTexture
  SDL_Rect position;
  position.x = 0;
  position.y = 0;
  SDL_QueryTexture(grilleTexture, NULL, NULL, &position.w, &position.h);
  SDL_RenderCopy(renderer,grilleTexture,NULL,&position);

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

void render_board(SDL_Renderer *renderer, const board *plateau, SDL_Texture* croixTexture, SDL_Texture* rondTexture) {

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


void render_running_state(SDL_Renderer *renderer, const board *plateau, SDL_Texture* grilleTexture, SDL_Texture* croixTexture, SDL_Texture* rondTexture) {

    render_grid(renderer, grilleTexture);
    render_board(renderer, plateau, croixTexture, rondTexture);
}

//render_game_over_state(renderer, plateau);


void render_game(SDL_Renderer *renderer, const board *plateau, SDL_Texture *grilleTexture, SDL_Texture* croixTexture, SDL_Texture* rondTexture) {

    if (plateau->state == RUNNING_STATE) {
      render_running_state(renderer, plateau, grilleTexture, croixTexture, rondTexture);
    }

    //switch (plateau->state) {
    //case RUNNING_STATE:
        //render_running_state(renderer, plateau);
        //break;

    //case PLAYER_X_WON_STATE:
        //render_game_over_state(renderer, plateau);
        //break;

    //case PLAYER_O_WON_STATE:
        //render_game_over_state(renderer, plateau, &PLAYER_O_COLOR);
      //  break;

  //  case TIE_STATE:
        //ender_game_over_state(renderer, plateau, &TIE_COLOR);
      //  break;

  //  default: {}
    //}
}