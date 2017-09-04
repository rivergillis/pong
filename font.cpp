#include "font.h"

Font::Font(TTF_Font* ttf, SDL_Renderer* renderer) {
  ttf_ = ttf;
  texture_.reset(new Texture(renderer, ttf));
}

Font::Font() {
  ttf_ = nullptr;
  text_ = "";
  text_color_ = { 0xFF, 0xFF, 0xFF, 0x00 };
}