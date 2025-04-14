#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL_render.h>

class Renderer {
public:
  Renderer();

  void close();

  SDL_Renderer *get_renderer();

  bool create_renderer(SDL_Window *window);

  void draw_rect(SDL_FRect *rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

  void update();

  void clear();

  void draw_grid(int max_x, int max_y, int cell_size);

  void draw_surface(SDL_Surface *surface, float x, float y, float w, float h);

private:
  SDL_Renderer *renderer{nullptr};
  SDL_Texture *texture{nullptr};
  SDL_Color background_color{239, 234, 216, 255};
  SDL_Color grid_lines_color{216, 210, 194, 255};
};

#endif
