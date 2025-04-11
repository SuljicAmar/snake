#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL_render.h>

class Renderer {
public:
  Renderer();
  ~Renderer();

  SDL_Renderer *get_renderer();
  bool create_renderer(SDL_Window *window);
  void draw_rect(SDL_FRect *rect, int r, int g, int b, int a);

  void update();

  void clear();

  void draw_grid();

private:
  SDL_Renderer *renderer{nullptr};
};

#endif
