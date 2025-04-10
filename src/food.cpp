#include "../include/food.h"
#include "../include/defs.h"
#include <SDL3/SDL.h>

Food::Food() { create(); };

void Food::create() {
  m_rect = {(float)(SDL_rand(window_width / rect_size) * rect_size),
            (float)(SDL_rand(window_height / rect_size) * rect_size), rect_size,
            rect_size};
};

SDL_FRect *Food::get_rect() { return &m_rect; }

SDL_Point Food::get_cordinates() {
  return (SDL_Point){.x = (int)m_rect.x, .y = (int)m_rect.y};
};
