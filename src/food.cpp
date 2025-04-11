#include "../include/food.h"
#include "../include/defs.h"
#include <SDL3/SDL.h>

Food::Food() { create_rect(); };

void Food::create_rect() {
  rect = {(float)(SDL_rand(window_width / rect_size) * rect_size),
          (float)(SDL_rand(window_height / rect_size) * rect_size), rect_size,
          rect_size};
};

SDL_FRect *Food::get_rect() { return &rect; }

SDL_Point Food::get_cordinates() {
  return (SDL_Point){.x = (int)rect.x, .y = (int)rect.y};
};

void Food::create(std::deque<SDL_FRect> &body) {
  bool keep_creating{true};
  while (keep_creating) {
    keep_creating = false;
    create_rect();
    for (SDL_FRect snake_segment : body) {
      if (snake_segment.x == rect.x && snake_segment.y == rect.y) {
        keep_creating = true;
        break;
      }
    }
  }
}
