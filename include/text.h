#ifndef TEXT_H
#define TEXT_H

#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>

class Text {
public:
  Text();

  void close();

  bool init();

  void set_font(const char *font_path, float font_size);

  void update_font_size(float font_size);

  void set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

  void set_text(const char *message);

  SDL_Surface *get_text_surface();

private:
  TTF_Font *font{nullptr};
  SDL_Surface *surface{nullptr};
  SDL_Color color;
  const char *text{nullptr};
};

#endif
