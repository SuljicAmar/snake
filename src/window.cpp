#include "../include/window.h"

Window::Window(char *name, int window_width, int window_height)
    : name{name}, width{window_width}, height{window_height} {};

bool Window::create_window() {
  window = SDL_CreateWindow(name, width, height, 0);
  if (!window) {
    return false;
  }
  return true;
}

Window::~Window() { SDL_DestroyWindow(window); };

SDL_Window *Window::get_window() { return window; };
