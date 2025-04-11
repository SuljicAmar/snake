#include "../include/renderer.h"
#include "../include/defs.h"

Renderer::Renderer() {};

Renderer::~Renderer() { SDL_DestroyRenderer(renderer); };

SDL_Renderer *Renderer::get_renderer() { return renderer; }

bool Renderer ::create_renderer(SDL_Window *window) {
  renderer = SDL_CreateRenderer(window, 0);
  if (!renderer) {
    return false;
  }
  return true;
}

void Renderer::draw_rect(SDL_FRect *rect, int r, int g, int b, int a) {
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
  SDL_RenderFillRect(renderer, rect);
}

void Renderer::update() { SDL_RenderPresent(renderer); }

void Renderer::clear() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
};

void Renderer::draw_grid() {
  // since window width and window height are same
  // could just do 1 loop but splitting it up
  // in case of future updates to sizing
  SDL_SetRenderDrawColor(renderer, 66, 66, 66, 255);
  for (int i = 0; i <= window_width; i += rect_size) {
    SDL_RenderLine(renderer, i, 0.0, i, window_height);
  };
  for (int i = 0; i <= window_height; i += rect_size) {
    SDL_RenderLine(renderer, 0.0, i, window_width, i);
  };
};
