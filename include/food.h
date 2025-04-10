#ifndef FOOD_H
#define FOOD_H
#include <SDL3/SDL.h>

class Food {
public:
  Food();

  void create();

  void draw(SDL_Renderer *renderer);

  SDL_FRect *get_rect();

  SDL_Point get_cordinates();

private:
  SDL_FRect m_rect;
};

#endif
