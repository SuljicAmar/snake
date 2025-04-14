#include "../include/app.h"

int main() {
  // initalize SDL and App objs
  App app;
  app.init();

  // app.init populates state variable
  while (app.get_game_state().running) {
    app.play();
  }

  // close app
  app.quit();
  return 0;
};
