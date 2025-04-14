#ifndef APP_H
#define APP_H

#include "audio.h"
#include "food.h"
#include "renderer.h"
#include "snake.h"
#include "state.h"
#include "text.h"
#include "timer.h"
#include "window.h"
#include <SDL3/SDL.h>
#include <string>

class App {
public:
  SDL_Event event;

  App();

  void init();

  void play();

  void quit();

  State &get_game_state();

private:
  void handle_input();

  void game_loop();

  void pre_game();

  void post_game();

  void init_sdl();

  void init_game();

  Window window;
  Renderer renderer;
  Text text;
  Snake snake;
  Food food;
  State state;
  Timer timer;
  Audio audio;
  std::string size_prefix_str;
};

#endif
