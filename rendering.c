#include <SDL2/SDL.h>

#include <game.h>
#include <rendering.h>

int matricex[9][9] = { {60,120,180,60,120,180,60,120,180},{300,360,420,300,360,420,300,360,420},{540,600,660,540,600,660,540,600,660},{60,120,180,60,120,180,60,120,180},{300,360,420,300,360,420,300,360,420},{540,600,660,540,600,660,540,600,660},{60,120,180,60,120,180,60,120,180},{300,360,420,300,360,420,300,360,420},{540,600,660,540,600,660,540,600,660}};
int matricey[9][9] = {{60,60,60,120,120,120,180,180,180},{60,60,60,120,120,120,180,180,180},{60,60,60,120,120,120,180,180,180},{300,300,300,360,360,360,420,420,420},{300,300,300,360,360,360,420,420,420},{300,300,300,360,360,360,420,420,420},{540,540,540,600,600,600,660,660,660},{540,540,540,600,600,600,660,660,660},{540,540,540,600,600,600,660,660,660}};

void render_x(SDL_Renderer *renderer, int x, int y) {

  int c = matricex[x][y];
  int d = matricey[x][y];

  SDL_Surface* croixImg= SDL_LoadBMP("img/croix.bmp");
  SDL_Texture* croixTexture = SDL_CreateTextureFromSurface(renderer,croixImg);
  SDL_FreeSurface(croixImg);

  SDL_Rect position;
  position.x = c + 5;
  position.y = d + 5;
  SDL_QueryTexture(croixTexture, NULL, NULL, &position.w, &position.h);
  SDL_RenderCopy(renderer,croixTexture,NULL,&position);
  SDL_RenderPresent(renderer);
}

void render_o(SDL_Renderer *renderer, int x, int y) {

    int c = matricex[x][y];
    int d = matricey[x][y];

    SDL_Surface* rondImg= SDL_LoadBMP("img/rond.bmp");
    SDL_Texture* rondTexture = SDL_CreateTextureFromSurface(renderer,rondImg);
    SDL_FreeSurface(rondImg);

    SDL_Rect position;
    position.x = c + 5;
    position.y = d + 5;
    SDL_QueryTexture(rondTexture, NULL, NULL, &position.w, &position.h);
    SDL_RenderCopy(renderer,rondTexture,NULL,&position);
    SDL_RenderPresent(renderer);
}

void render_board(SDL_Renderer *renderer, const board *plateau) {

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (plateau->tab[i].tab[j] == PLAYER_X) {
              render_x(renderer, i, j);
            }

            if (plateau->tab[i].tab[j] == PLAYER_O) {
              render_o(renderer, i, j);
            }
        }
    }
  }


void render_running_state(SDL_Renderer *renderer, const board *plateau) {

    render_board(renderer, plateau);
}

//render_game_over_state(renderer, plateau);


void render_game(SDL_Renderer *renderer, const board *plateau) {

    if (plateau->state == RUNNING_STATE) {
      render_running_state(renderer, plateau);
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