#ifndef FOOD_H
#define FOOD_H

#include <SDL3/SDL_rect.h>

class Food {
public:
  Food();

  SDL_FRect *get_rect();

  SDL_Point get_cordinates();

  void create(int window_width, int window_height, int rect_size);

private:
  SDL_FRect rect;
};

#endif
