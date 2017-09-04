#ifndef FONT_H_
#define FONT_H_

#include "texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Font {
 public:
  Font();

  Font(TTF_Font* ttf, SDL_Renderer* renderer);

  TTF_Font* GetTTF() { return ttf_; }

  Texture* GetTexture() { return texture_.get(); }

  void SetText(const std::string& new_text) {
    text_ = new_text;
  }

  std::string GetText() { return text_; }

  void SetColor(SDL_Color color) {
    text_color_ = color;
  }

  SDL_Color GetColor() { return text_color_; }

 private:
  // Font does not own this and will not destruct it
  TTF_Font* ttf_;

  std::unique_ptr<Texture> texture_;
  std::string text_;
  SDL_Color text_color_;
};

#endif