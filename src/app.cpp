#include "../include/app.h"
#include "../include/defs.h"

App::App() {};

void App::init() {
  // initalize SDL, window, renderer, text
  state.init = true;
  init_sdl();
  if (state.init) {
    init_game();
  }
};

void App::init_sdl() {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    SDL_Log("Failed initializing SDL: %s", SDL_GetError());
    state.init = false;
  }
  if (!window.create_window(window_width, window_height)) {
    SDL_Log("Failed creating window: %s", SDL_GetError());
    state.init = false;
  }
  if (!renderer.create_renderer(window.get_window())) {
    SDL_Log("Failed creating renderer: %s", SDL_GetError());
    state.init = false;
  }
  if (!text.init()) {
    SDL_Log("Failed init TTF_Text: %s", SDL_GetError());
    state.init = false;
  }
  if (!state.init) {
    state.running = false;
    state.activity = null;
  };
};

void App::init_game() {
  state.running = true;
  text.set_font("../assets/font.ttf", 100);
  audio.create_audio_objects();
  audio.set_music("../assets/music.wav");
  audio.set_eat_sound("../assets/eat.wav");
  audio.set_game_over_sound("../assets/game_over.wav");
  audio.play_music();
  food.create(window_width, window_height, rect_size);
  snake.reset(window_width, window_height, rect_size);
  state.activity = menu;
};

void App::play() {
  switch (state.activity) {
  case menu:
    pre_game();
    break;
  case playing:
    game_loop();
    break;
  case game_over:
    post_game();
    break;
  case null:
    break;
  };
  handle_input();
};

void App::pre_game() {
  // start game screen
  renderer.clear();
  cfg_header_text();
  cfg_keymap_text();
  renderer.update();
};

void App::game_loop() {
  audio.unpause_music();
  timer.start();

  // input, movement and actions
  snake.move(rect_size);
  if (snake.out_of_bounds(window_width, window_height) || snake.ate_self()) {
    audio.pause_music();
    audio.play_game_over_sound();
    state.activity = game_over;
  }
  SDL_Point food_cordinates = food.get_cordinates();
  if (snake.ate_food(food_cordinates)) {
    audio.play_eat_sound_effect();
    snake.size++;
    food.create(window_width, window_height, rect_size);
  }

  snake.handle_size();

  // drawing
  renderer.clear();
  renderer.draw_grid(window_width, window_height, rect_size);
  renderer.draw_rect(food.get_rect(), food_color.r, food_color.g, food_color.b,
                     food_color.a);
  int g_adj = snake_starting_color.g;
  for (SDL_FRect snake_segment : snake.body) {
    renderer.draw_rect(&snake_segment, snake_starting_color.r, g_adj,
                       snake_starting_color.b, snake_starting_color.a);
    g_adj += 3;
  };
  renderer.update();

  // delay game loop
  timer.delay();
};

void App::post_game() {
  // game over screen
  renderer.clear();
  cfg_header_text();
  cfg_score_text();
  cfg_keymap_text();
  renderer.update();
};

void App::handle_input() {
  // quit app, restart or move snake
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      state.running = false;
    }
    if (event.type == SDL_EVENT_KEY_DOWN) {
      if (state.activity == playing) {
        snake.set_direction(event);
      } else {
        if (event.key.scancode == SDL_SCANCODE_RETURN) {
          snake.reset(window_width, window_height, rect_size);
          state.activity = playing;
        } else if (event.key.scancode == SDL_SCANCODE_Q) {
          state.running = false;
        }
      }
    }
  }
};

void App::quit() {
  text.close();
  audio.close();
  Mix_Quit();
  SDL_DestroySurface(text_surface);
  text_surface = nullptr;
  renderer.close();
  window.close();
  SDL_Quit();
};

State &App::get_game_state() { return state; };

// this cfg code is very ugly and bad
// but as its last bit of code i'm writing for
// this proj i will leave it
void App::cfg_header_text() {
  if (state.activity == menu) {
    text.set_color(snake_starting_color);
    text.set_text("Snake");
    text_surface = text.get_text_surface();
    text_surface_w = text_surface->w;
    text_surface_h = text_surface->h;
    renderer.draw_surface(text_surface, (window_width - text_surface_w) / 2.f,

                          (window_height * 0.6 - text_surface_h) / 2.f,

                          text_surface_w, text_surface_h);
  } else {
    text.set_color(food_color);
    text.set_text("Game Over!\0");
    text_surface = text.get_text_surface();
    text_surface_w = text_surface->w / 1.5;
    text_surface_h = text_surface->h / 1.5;
    renderer.draw_surface(text_surface, (window_width - text_surface_w) / 2.f,
                          (window_height * 0.6 - text_surface_h) / 2.f,
                          text_surface_w, text_surface_h);
  }
  SDL_DestroySurface(text_surface);
};

void App::cfg_score_text() {
  text.set_color(text_color);
  size_prefix_str = "Score: ";
  size_prefix_str.append(snake.get_size_as_str());
  text.set_text(size_prefix_str.c_str());
  text.set_color(text_color);
  text_surface = text.get_text_surface();
  text_surface_w = text_surface->w / 4.f;
  text_surface_h = text_surface->h / 4.f;
  renderer.draw_surface(text_surface, (window_width - text_surface_w) / 2.f,
                        (window_height * 0.9 - text_surface_h) / 2.f,
                        text_surface_w, text_surface_h);
  SDL_DestroySurface(text_surface);
};

void App::cfg_keymap_text() {
  text.set_color(text_color);
  text.set_text("quit <q>");
  text_surface = text.get_text_surface();
  text_surface_w = text_surface->w / 3.f;
  text_surface_h = text_surface->h / 3.f;
  renderer.draw_surface(text_surface, (window_width - text_surface_w) * 0.1,
                        (window_height - text_surface_h) / 1.5, text_surface_w,
                        text_surface_h);
  SDL_DestroySurface(text_surface);
  text.set_text("play <enter>");
  text_surface = text.get_text_surface();
  text_surface_w = text_surface->w / 3.f;
  text_surface_h = text_surface->h / 3.f;
  renderer.draw_surface(text_surface, (window_width - text_surface_w) * 0.9,
                        (window_height - text_surface_h) / 1.5, text_surface_w,
                        text_surface_h);
  SDL_DestroySurface(text_surface);
};
