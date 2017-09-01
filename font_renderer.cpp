#include "font_renderer.h"

#include "utilities.h"

FontRenderer::FontRenderer() {
  fonts_.reserve(static_cast<int>(FontName::TOTAL_NUM_FONTS));
  for (int i = 0; i < static_cast<int>(FontName::TOTAL_NUM_FONTS); ++i) {
    fonts_.emplace_back();
  }
}

FontRenderer::~FontRenderer() {
  // Deallocate each TTF_Font*
  for (auto& font_map : fonts_) {
    for (auto& font_map_pair : font_map) {
      TTF_CloseFont(font_map_pair.second.ttf);
    }
  }
}

std::string FontRenderer::FontPath(FontName name) {
  switch(name) {
    case FontName::FORWARD:
      return "assets/fonts/fff-forward.ttf";
      break;
    case FontName::TOTAL_NUM_FONTS:
      printf("Tried to access texture for TOTAL_NUM_FONTS!\n");
      return "";
      break;
  }
}

int FontRenderer::SizeFont(FontName name, int size, const std::string& text, int* w, int* h) {
  if (name == FontName::TOTAL_NUM_FONTS) { return -1; }
  std::unordered_map<int, Font>* font_map = &fonts_[static_cast<int>(name)];

  int return_val = 0;

  // we don't have this font saved, make one and test
  if (font_map->count(size) == 0) {
    TTF_Font* new_font = TTF_OpenFont(FontPath(name).c_str(), size);
    if (new_font == nullptr) {
      printf("Error: Failed to open font! Message: %s\n", TTF_GetError());
      return -1;
    }
    return_val = TTF_SizeText(new_font, text.c_str(), w, h);
    TTF_CloseFont(new_font);
  } else {
    // We already have made this font, test that
    return_val = TTF_SizeText((*font_map)[size].ttf, text.c_str(), w, h);
  }

  return return_val;
}


void FontRenderer::RenderFont(SDL_Renderer* renderer, FontName name, int size,
  int x, int y, const std::string& text, SDL_Color text_color) {
  // Create the font size if it doesn't exist
  // if the given text is different from the previous text for that font, load a new one
  // render the given texture

  // breakdown: We first create a TTF_Font* with a .ttf and a size
  // then we initialize a texture with a renderer and a TTF_FONT
  // then we render text to a texture using a text string and color
  // then we render the texture
  if (name == FontName::TOTAL_NUM_FONTS) { return; }
  std::unordered_map<int, Font>* font_map = &fonts_[static_cast<int>(name)];

  // If we don't have the font in this size yet, make one
  if (font_map->count(size) == 0) {
    TTF_Font* new_font = TTF_OpenFont(FontPath(name).c_str(), size);
    if (new_font == nullptr) {
      printf("Error: Failed to open font! Message: %s\n", TTF_GetError());
      return;
    }

    Texture new_texture(renderer, new_font);
    new_texture.LoadFromRenderedText(text, text_color);

    // Go ahead and render it while we're here
    new_texture.Render(x, y);

    // Add it to the map and leave
    (*font_map)[size] = {new_font, new_texture, text, text_color};
    return;
  }

  // If we do have the font in this size, check if it is the same rendering
  Font* font = &(*font_map)[size];
  if (font->text == text && ColorsEqual(font->text_color, text_color)) {
    // This is the same as the previous rendering, so just use it.
    font->texture.Render(x, y);
  } else {
    // This is a new rendering text or color, remake the texture
    font->texture.LoadFromRenderedText(text, text_color);
    font->texture.Render(x, y);

    // Update the Font
    font->text = text;
    font->text_color = text_color;
  }
}