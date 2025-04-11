#ifndef FOOD_H
#define FOOD_H
#include <SDL3/SDL.h>
#include <deque>

class Food {
public:
  Food();

  void draw(SDL_Renderer *renderer);

  SDL_FRect *get_rect();

  SDL_Point get_cordinates();

  void create(std::deque<SDL_FRect> &body);

private:
  SDL_FRect rect;
  void create_rect();
};

#endif
