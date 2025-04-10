#include "../include/window.h"

Window::Window(char *name, int window_width, int window_height)
    : m_name{name}, m_width{window_width}, m_height{window_height} {};

bool Window::create_window() {
  m_window = SDL_CreateWindow(m_name, m_width, m_height, 0);
  if (!m_window) {
    return false;
  }
  return true;
}

Window::~Window() { SDL_DestroyWindow(m_window); };

SDL_Window *Window::get_window() { return m_window; };
