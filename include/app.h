#ifndef APP_H
#define APP_H

#include "food.h"
#include "renderer.h"
#include "snake.h"
#include "window.h"
#include <SDL3/SDL.h>

class App {
public:
  int frame_time;
  Uint64 ns_per_frame = 1000000000 / 30;
  Uint64 frame_start;
  SDL_Event event;
  bool running{true};

  bool init(Window &window, Renderer &renderer);

  void game_loop(Snake &snake, Food &food, Renderer &renderer);

  void quit();
};

#endif
