#include "../include/app.h"
#include "../include/renderer.h"
#include "../include/timer.h"
#include "../include/window.h"

int main() {
  // initalize SDL and App objs
  Window window("Snake", window_width, window_height);
  Renderer renderer;
  App app;

  // continue to game loop if SDL loads OK
  if (app.init(window, renderer)) {
    Snake snake;
    Food food;
    Timer timer;
    while (app.running) {
      app.game_loop(snake, food, renderer, timer);
    }
  }

  // close app if SDL fails to init or app stops running
  app.quit();
  return 0;
};
