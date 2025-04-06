#include "../include/food.h"
#include "../include/defs.h"
#include <SDL3/SDL.h>

Food::Food() { create(); };

void Food::create() {
  rect = {(float)(SDL_rand(screen_width / rect_size) * rect_size),
          (float)(SDL_rand(screen_height / rect_size) * rect_size), rect_size,
          rect_size};
  x = rect.x;
  y = rect.y;
};

void Food::draw(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderFillRect(renderer, &rect);
};
