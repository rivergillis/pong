#ifndef FONT_RENDERER_H_
#define FONT_RENDERER_H_

#include "texture.h"

#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

enum class FontName {
  FORWARD = 0,
  TOTAL_NUM_FONTS
};

struct Font {
  TTF_Font* ttf = nullptr;
  Texture texture;
  std::string text = "";
  SDL_Color text_color;
};

class FontRenderer {
 public:
  // Init
  FontRenderer();

  // Dealloc
  ~FontRenderer();

  std::string FontPath(FontName name);  

  void RenderFont(SDL_Renderer* renderer, FontName name, int size,
    int x, int y, const std::string& text, SDL_Color text_color);
    
 private:
  // vector of font sizes to font maps
  //  each font map maps integer point size to Fonts
  std::vector<std::unordered_map<int, Font>> fonts_;
};

#endif