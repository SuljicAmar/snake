#include "../include/app.h"
#include "../include/renderer.h"
#include "../include/window.h"

int main() {
  Window window("Snake", window_width, window_height);
  Renderer renderer;
  App app;
  if (app.init(window, renderer)) {
    Snake snake;
    Food food;
    while (app.running) {
      app.game_loop(snake, food, renderer);
    }
  }
  app.quit();
  return 0;
};
