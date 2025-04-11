#include "../include/food.h"
#include "../include/defs.h"
#include <SDL3/SDL.h>

Food::Food() { create_rect(); };

void Food::create_rect() {
  m_rect = {(float)(SDL_rand(k_window_width / k_rect_size) * k_rect_size),
            (float)(SDL_rand(k_window_height / k_rect_size) * k_rect_size),
            k_rect_size, k_rect_size};
};

SDL_FRect *Food::get_rect() { return &m_rect; }

SDL_Point Food::get_cordinates() {
  return (SDL_Point){.x = (int)m_rect.x, .y = (int)m_rect.y};
};

void Food::create(std::deque<SDL_FRect> &body) {
  bool keep_creating{true};
  while (keep_creating) {
    keep_creating = false;
    create_rect();
    for (SDL_FRect snake_segment : body) {
      if (snake_segment.x == m_rect.x && snake_segment.y == m_rect.y) {
        keep_creating = true;
        break;
      }
    }
  }
}
