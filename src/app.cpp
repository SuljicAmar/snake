#include "../include/app.h"

App::App() {};

bool App::init(Window &window, Renderer &renderer) {
  // initalize SDL, window, and renderer
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Failed initializing SDL: %s", SDL_GetError());
    return false;
  }
  if (!window.create_window()) {
    SDL_Log("Failed creating window: %s", SDL_GetError());
    return false;
  }
  if (!renderer.create_renderer(window.get_window())) {
    SDL_Log("Failed creating renderer: %s", SDL_GetError());
    return false;
  }
  return true;
}

void App::game_loop(Snake &snake, Food &food, Renderer &renderer,
                    Timer &timer) {
  timer.start();

  // input, movement and actions
  handle_input(snake);
  snake.move();
  SDL_Point food_cordinates = food.get_cordinates();
  if (snake.ate_food(food_cordinates)) {
    food.create(snake.body);
  }
  if (snake.ate_self()) {
    snake.reset();
  }
  snake.handle_size();

  // drawing
  // TODO: can we draw grid outside game loop and not have to redraw?
  renderer.clear();
  renderer.draw_grid();
  renderer.draw_rect(food.get_rect(), 255, 0, 0, 255);
  for (SDL_FRect snake_segment : snake.body) {
    renderer.draw_rect(&snake_segment, 0, 255, 0, 255);
  }
  renderer.update();

  // delay game loop
  timer.delay();
};

void App::handle_input(Snake &snake) {
  // quit app or move snake
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      running = false;
    }
    if (event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat) {
      snake.set_direction(event);
    }
  }
};

void App::quit() { SDL_Quit(); };
