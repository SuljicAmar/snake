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
  m_frame_start = SDL_GetTicksNS();

  while (SDL_PollEvent(&m_event)) {
    if (m_event.type == SDL_EVENT_QUIT) {
      m_running = false;
    }
    if (m_event.type == SDL_EVENT_KEY_DOWN && !m_event.key.repeat) {
      snake.set_direction(m_event);
    }
  }
  snake.move();
  SDL_Point food_cordinates = food.get_cordinates();
  if (snake.ate_food(food_cordinates)) {
    food.create(snake.m_body);
  }
  if (snake.ate_self()) {
    snake.reset();
  }
  snake.handle_size();
  renderer.clear();
  renderer.draw_rect(food.get_rect(), 255, 0, 0, 255);
  for (SDL_FRect snake_segment : snake.m_body) {
    renderer.draw_rect(&snake_segment, 143, 188, 143, 255);
  }
  renderer.update();
  m_frame_time = SDL_GetTicksNS() - m_frame_start;

  if (m_frame_time < m_ns_per_frame) {
    SDL_DelayNS(m_ns_per_frame - m_frame_time);
  }
};

void App::quit() { SDL_Quit(); };
