#include "../include/renderer.h"

Renderer::Renderer() {};

void Renderer::close() {
  SDL_DestroyRenderer(renderer);
  renderer = nullptr;

  SDL_DestroyTexture(texture);
  texture = nullptr;
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
  SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g,
                         background_color.b, background_color.a);
  SDL_RenderClear(renderer);
};

void Renderer::draw_grid(int max_x, int max_y, int cell_size) {
  SDL_SetRenderDrawColor(renderer, grid_lines_color.r, grid_lines_color.g,
                         grid_lines_color.b, grid_lines_color.a);
  for (int i = 0; i <= max_x; i += cell_size) {
    SDL_RenderLine(renderer, i, 0.0, i, max_y);
    SDL_RenderLine(renderer, 0.0, i, max_x, i);
  };
};

void Renderer::draw_surface(SDL_Surface *surface, float x, float y, float w,
                            float h) {
  // used for rendering Text
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FRect texture_space = {x, y, w, h};
  SDL_RenderTexture(renderer, texture, nullptr, &texture_space);
};
