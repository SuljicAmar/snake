#include "../include/text.h"

Text::Text() {};

void Text::close() {
  TTF_CloseFont(font);
  font = nullptr;
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

void Text::set_color(SDL_Color new_color) { color = new_color; };

void Text::set_text(const char *message) { text = message; };

SDL_Surface *Text::get_text_surface() {
  return TTF_RenderText_Blended(font, text, 0, color);
};
