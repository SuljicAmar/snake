#include "../include/food.h"

Food::Food() {};

void Food::create(int window_width, int window_height, int rect_size) {
  // create rect with random cordinates, accounting for int size of rect
  // so snake collision works properly
  rect = {(float)(SDL_rand(window_width / rect_size) * rect_size),
          (float)(SDL_rand(window_height / rect_size) * rect_size),
          (float)rect_size, (float)rect_size};
};

SDL_FRect *Food::get_rect() { return &rect; };

SDL_Point Food::get_cordinates() {
  return (SDL_Point){.x = (int)rect.x, .y = (int)rect.y};
};
