#ifndef SNAKE_H
#define SNAKE_H

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_rect.h>
#include <deque>

class Snake {
public:
  int size;
  enum Direction { down, left, right, up };
  SDL_FRect head;
  std::deque<SDL_FRect> body;

  Snake();

  void set_direction(SDL_Event event);

  void move(int rect_size);

  bool ate_food(SDL_Point food_cordinates);

  bool ate_self();

  bool out_of_bounds(int window_width, int window_height);

  void reset(int window_width, int window_height, int rect_size);

  void handle_size();

  std::string get_size_as_str();

private:
  Direction direction{right};

  void create_head(int window_width, int window_height, int rect_size);
};

#endif
