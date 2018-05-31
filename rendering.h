#ifndef RENDERING_H_
#define RENDERING_H_

void render_game(SDL_Renderer *renderer, const board *plateau, SDL_Texture* grilleTexture,
  SDL_Texture* croixTexture, SDL_Texture* rondTexture,
  SDL_Texture* x_winTexture, SDL_Texture* o_winTexture, SDL_Texture* tie_stateTexture);

#endif  // RENDERING_H_