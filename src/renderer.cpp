#include "../include/renderer.h"
#include "SDL3/SDL_render.h"

Renderer::Renderer() {};

Renderer::~Renderer() { SDL_DestroyRenderer(m_renderer); };

SDL_Renderer *Renderer::get_renderer() { return m_renderer; }
bool Renderer ::create_renderer(SDL_Window *window) {
  m_renderer = SDL_CreateRenderer(window, 0);
  if (!m_renderer) {
    SDL_Log("Failed creating renderer: %s", SDL_GetError());
    return false;
  }
  return true;
}

void Renderer::draw_rect(SDL_FRect *rect, int r, int g, int b, int a) {
  SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
  SDL_RenderFillRect(m_renderer, rect);
}

void Renderer::update() { SDL_RenderPresent(m_renderer); }

void Renderer::clear() {
  SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
  SDL_RenderClear(m_renderer);
}
