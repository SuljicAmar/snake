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
  text.set_font("../assets/font.ttf", 24.0);
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
  text.update_font_size(72.0);
  text.set_color(255, 190, 106, 255);

  text.set_text("Snake");
  renderer.draw_surface(text.get_text_surface(), window_width,
                        window_height * 0.5);

  text.set_text("press enter");
  text.update_font_size(28.0);
  text.set_color(218, 216, 240, 255);
  renderer.draw_surface(text.get_text_surface(), window_width,
                        window_height * .8);
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
  renderer.draw_rect(food.get_rect(), 253, 83, 100, 255);
  int r_adj = 20;
  for (SDL_FRect snake_segment : snake.body) {
    renderer.draw_rect(&snake_segment, r_adj, 253, 83, 255);
    r_adj += 20;
  };
  renderer.update();

  // delay game loop
  timer.delay();
};

void App::post_game() {
  // game over screen
  renderer.clear();
  text.update_font_size(72.0);
  text.set_color(255, 190, 106, 255);

  text.set_text("Game Over!\0");
  renderer.draw_surface(text.get_text_surface(), window_width,
                        window_height * 0.5);

  size_prefix_str = "Score: ";
  size_prefix_str.append(snake.get_size_as_str());

  text.set_text(size_prefix_str.c_str());
  text.update_font_size(28.0);
  text.set_color(218, 216, 240, 255);

  renderer.draw_surface(text.get_text_surface(), window_width,
                        window_height * 0.8);
  text.set_color(218, 216, 240, 255);

  text.set_text("enter to restart");

  renderer.draw_surface(text.get_text_surface(), window_width, window_height);

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
        }
      }
    }
  }
};

void App::quit() {
  text.close();
  audio.close();
  Mix_Quit();
  renderer.close();
  window.close();
  SDL_Quit();
};

State &App::get_game_state() { return state; };
