#ifndef WINDOW_H
#define WINDOW_H

#include <SDL3/SDL_video.h>

class Window {
public:
  Window(char *name, int window_width, int window_height);

  ~Window();

  bool create_window();

  SDL_Window *get_window();

private:
  SDL_Window *window{nullptr};
  char *name;
  int width;
  int height;
};

#endif
