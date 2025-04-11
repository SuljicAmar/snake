#ifndef APP_H
#define APP_H

#include "food.h"
#include "renderer.h"
#include "snake.h"
#include "timer.h"
#include "window.h"
#include <SDL3/SDL.h>

class App {
public:
  SDL_Event event;
  bool running{true};

  App();

  bool init(Window &window, Renderer &renderer);

  void game_loop(Snake &snake, Food &food, Renderer &renderer, Timer &timer);

  void quit();

  void handle_input(Snake &snake);
};

#endif
