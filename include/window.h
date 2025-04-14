#ifndef WINDOW_H
#define WINDOW_H

#include <SDL3/SDL_video.h>

class Window {
public:
  Window();

  void close();

  bool create_window(int window_width, int window_height);

  SDL_Window *get_window();

private:
  SDL_Window *window{nullptr};
};

#endif
