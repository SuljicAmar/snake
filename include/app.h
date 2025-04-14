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
  int text_surface_w;
  int text_surface_h;

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

  void cfg_header_text();

  void cfg_score_text();

  void cfg_keymap_text();

  Window window;
  Renderer renderer;
  Text text;
  Snake snake;
  Food food;
  State state;
  Timer timer;
  Audio audio;
  std::string size_prefix_str;
  SDL_Surface *text_surface{nullptr};
  SDL_Color food_color{201, 104, 104, 255};
  SDL_Color snake_starting_color{89, 116, 69, 255};
  SDL_Color text_color{33, 33, 33, 255};
};

#endif
