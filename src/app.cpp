#include "../include/app.h"

bool App::init(Window &window, Renderer &renderer) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Failed initializing SDL: %s", SDL_GetError());
    return false;
  }
  if (!window.create_window()) {
    return false;
  }
  if (!renderer.create_renderer(window.get_window())) {
    return false;
  }
  return true;
}

void App::game_loop(Snake &snake, Food &food, Renderer &renderer) {
  frame_start = SDL_GetTicksNS();

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      running = false;
    }
    if (event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat) {
      snake.set_direction(event);
    }
  }
  snake.move();
  SDL_Point food_cordinates = food.get_cordinates();
  if (snake.ate_food(food_cordinates)) {
    food.create(snake.body);
  }
  if (snake.ate_self()) {
    snake.reset();
  }
  snake.handle_size();
  renderer.clear();
  renderer.draw_rect(food.get_rect(), 255, 0, 0, 255);
  for (SDL_FRect snake_segment : snake.body) {
    renderer.draw_rect(&snake_segment, 143, 188, 143, 255);
  }
  renderer.update();
  frame_time = SDL_GetTicksNS() - frame_start;

  if (frame_time < ns_per_frame) {
    SDL_DelayNS(ns_per_frame - frame_time);
  }
};

void App::quit() { SDL_Quit(); };
