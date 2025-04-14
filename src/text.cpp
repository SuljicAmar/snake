#include "../include/text.h"

Text::Text() {};

void Text::close() {
  TTF_CloseFont(font);
  font = nullptr;

  SDL_DestroySurface(surface);
  surface = nullptr;

  TTF_Quit();
};

bool Text::init() {
  if (!TTF_Init()) {
    return false;
  }
  return true;
};

void Text::set_font(const char *font_path, float font_size) {
  font = TTF_OpenFont(font_path, font_size);
};

void Text::update_font_size(float font_size) {
  TTF_SetFontSize(font, font_size);
}

void Text::set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  color = SDL_Color{.r = r, .g = g, .b = b, .a = a};
};

void Text::set_text(const char *message) { text = message; };

SDL_Surface *Text::get_text_surface() {
  return TTF_RenderText_Blended(font, text, 0, color);
};
