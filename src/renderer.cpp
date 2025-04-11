#include "../include/renderer.h"
#include "SDL3/SDL_render.h"

Renderer::Renderer() {};

Renderer::~Renderer() { SDL_DestroyRenderer(renderer); };

SDL_Renderer *Renderer::get_renderer() { return renderer; }
bool Renderer ::create_renderer(SDL_Window *window) {
  renderer = SDL_CreateRenderer(window, 0);
  if (!renderer) {
    SDL_Log("Failed creating renderer: %s", SDL_GetError());
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
}
