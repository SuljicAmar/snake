#ifndef WINDOW_H
#define WINDOW_H

#include <SDL3/SDL.h>

class Window {
public:
  Window(char *name, int window_width, int window_height);

  ~Window();

  bool create_window();

  SDL_Window *get_window();

private:
  SDL_Window *m_window{nullptr};
  char *m_name;
  int m_width;
  int m_height;
};

#endif
