#include "../include/window.h"

Window::Window() {};

bool Window::create_window(int window_width, int window_height) {
  window = SDL_CreateWindow("Snake", window_width, window_height, 0);

  if (!window) {
    return false;
  };
  return true;
}

void Window::close() {
  SDL_DestroyWindow(window);
  window = nullptr;
};

SDL_Window *Window::get_window() { return window; };
