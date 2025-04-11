#ifndef SNAKE_H
#define SNAKE_H

#include "defs.h"
#include <SDL3/SDL.h>
#include <deque>

class Snake {
public:
  int m_size{1};
  enum Direction { down, left, right, up };

  SDL_FRect m_head{.x = k_window_width / 2,
                   .y = k_window_height / 2,
                   .w = k_rect_size,
                   .h = k_rect_size};
  std::deque<SDL_FRect> m_body;

  Snake();

  void set_direction(SDL_Event event);

  void move();

  void draw(SDL_Renderer *renderer);

  bool ate_food(SDL_Point food_cordinates);

  bool ate_self();

  void out_of_bounds();

  void reset();

  void handle_size();

private:
  Direction m_direction{right};
};

#endif
