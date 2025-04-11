#include "../include/app.h"
#include "../include/renderer.h"
#include "../include/window.h"

int main() {
  Window window("Snake", k_window_width, k_window_height);
  Renderer renderer;
  App app;
  if (app.init(window, renderer)) {
    Snake snake;
    Food food;
    while (app.m_running) {
      app.game_loop(snake, food, renderer);
    }
  }
  app.quit();
  return 0;
};
