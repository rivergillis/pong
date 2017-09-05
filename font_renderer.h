// font_renderer.h
// Author: River Gillis
//
// Handles the collection and rendering of text to the screen.
//  (really should be renamed to text_renderer).
// Automatically detects and makes sure not to render the same text
// again, instead simply uses the last rendering.
//
// For the sake of a simple API that has an efficient implmentation, the
// implmentation is kind of ugly. Dealing with @fonts_ is hard to look at.

#ifndef FONT_RENDERER_H_
#define FONT_RENDERER_H_

#include "texture.h"
#include "font.h"

#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// The names of all of the fonts
enum class FontName {
  FORWARD = 0,
  TOTAL_NUM_FONTS
};

class FontRenderer {
 public:
  FontRenderer();

  // Deallocates every Font in @fonts_
  ~FontRenderer();

  // Places the size of the texture into @w, @h
  //  name: The name of the font
  //  size: The point size of the font
  //  text: The text to be rendered
  int SizeFont(FontName name, int size, const std::string& text, int* w, int* h);

  // void DbgFonts();

  // Render the @text to the screen at @x, @y with the font @name at size @size
  // using renderer @renderer with text color @text_color
  // If that same font was rendered last frame, reuse it.
  void RenderFont(SDL_Renderer* renderer, FontName name, int size,
    int x, int y, const std::string& text, SDL_Color text_color);

 private:
  // Get the file path to font @name
  std::string FontPath(FontName name);  
  
  // vector of font sizes to font maps
  //  each font map maps integer point size to Fonts
  // Examples:
  //  // A map of font sizes to Font objects for the FORWARD font
  //  fonts_[static_cast<int>(FontName::FORWARD)]
  //  // A Font object for the FORWARD font at size 48
  //  fonts_[static_cast<int>(FontName::FORWARD)][48]
  std::vector<std::unordered_map<int, Font>> fonts_;
};

#endif