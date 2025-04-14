#include "../include/renderer.h"

Renderer::Renderer() {};

void Renderer::close() {
  SDL_DestroyRenderer(renderer);
  renderer = nullptr;
};

SDL_Renderer *Renderer::get_renderer() { return renderer; }

bool Renderer ::create_renderer(SDL_Window *window) {
  renderer = SDL_CreateRenderer(window, 0);
  if (!renderer) {
    return false;
  }
  return true;
}

void Renderer::draw_rect(SDL_FRect *rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
  SDL_RenderFillRect(renderer, rect);
}

void Renderer::update() { SDL_RenderPresent(renderer); }

void Renderer::clear() {
  SDL_SetRenderDrawColor(renderer, 31, 25, 40, 255);
  SDL_RenderClear(renderer);
};

void Renderer::draw_grid(int max_x, int max_y, int cell_size) {
  // since window width and window height are same
  // could just do 1 loop but splitting it up
  // in case of future updates to sizing
  SDL_SetRenderDrawColor(renderer, 40, 35, 57, 255);
  for (int i = 0; i <= max_x; i += cell_size) {
    SDL_RenderLine(renderer, i, 0.0, i, max_y);
  };
  for (int i = 0; i <= max_y; i += cell_size) {
    SDL_RenderLine(renderer, 0.0, i, max_x, i);
  };
};

void Renderer::draw_surface(SDL_Surface *surface, int x, int y) {
  // used for rendering Text
  SDL_Texture *texture{SDL_CreateTextureFromSurface(renderer, surface)};
  int surface_width{surface->w};
  int surface_height{surface->h};
  SDL_DestroySurface(surface);
  SDL_FRect texture_space = {(x - surface_width) / 2.f,
                             (y - surface_height) / 2.f, (float)surface_width,
                             (float)surface_height};
  SDL_RenderTexture(renderer, texture, nullptr, &texture_space);
  SDL_DestroyTexture(texture);
};
