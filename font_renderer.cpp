#include "font_renderer.h"

#include "utilities.h"
#include <cinttypes>
#include <cstdint>

// Construct empty unordered_maps at each FontName of @fonts_
// Not sure if this is necessary, but hey it's explicit and what we want
FontRenderer::FontRenderer() {
  fonts_.reserve(static_cast<int>(FontName::TOTAL_NUM_FONTS));
  for (int i = 0; i < static_cast<int>(FontName::TOTAL_NUM_FONTS); ++i) {
    fonts_.emplace_back();
  }
}

// Deallocate every TTF in @fonts_
// TODO: test if we can move this to ~Font()
FontRenderer::~FontRenderer() {
  // Deallocate each TTF_Font*
  for (auto& font_map : fonts_) {
    for (auto& font_map_pair : font_map) {
      TTF_CloseFont(font_map_pair.second.GetTTF());
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
  // @font_map: A map of font point size to Font objects for font @name
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
    return_val = TTF_SizeText((*font_map)[size].GetTTF(), text.c_str(), w, h);
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
    printf("Making and rendering this font for the first time!\n");
    TTF_Font* new_ttf = TTF_OpenFont(FontPath(name).c_str(), size);
    if (new_ttf == nullptr) {
      printf("Error: Failed to open font! Message: %s\n", TTF_GetError());
      return;
    }

    // Create a new Font with the ttf and renderer
    Font new_font(new_ttf, renderer);

    // Render the text, then the texture
    new_font.GetTexture()->LoadFromRenderedText(text, text_color);
    new_font.GetTexture()->Render(x, y);

    // Move the new font into our map
    (*font_map)[size] = std::move(new_font);

    return;
  }

  // If we do have the font in this size, check if it is the same rendering
  Font* font = &(*font_map)[size];
  // TODO: Define equality for Font objects
  if (font->GetText() == text && ColorsEqual(font->GetColor(), text_color)) {
    // This is the same as the previous rendering, so just use it.
    font->GetTexture()->Render(x, y);
  } else {
    // This is a new rendering text or color, remake the texture
    printf("Rendering this font for the first time!\n");
    font->GetTexture()->LoadFromRenderedText(text, text_color);
    font->GetTexture()->Render(x, y);

    // Update the Font
    font->SetText(text);
    font->SetColor(text_color);
  }
}

/*
void FontRenderer::DbgFonts() {
  // Deallocate each TTF_Font*
  int size = 0;
  int inner_size = 0;
  for (auto& font_map : fonts_) {
    printf("Map %d", size);
    for (auto& font_map_pair : font_map) {
      printf("\tSize: %d", inner_size);
      printf("\tTTF: %016" PRIxPTR, (uintptr_t)font_map_pair.second.ttf);
      printf("\tTexture: %016" PRIxPTR, (uintptr_t)font_map_pair.second.texture.GetPtr());
      printf("\tText: %s", font_map_pair.second.text.c_str());
      SDL_Color c = font_map_pair.second.text_color;
      printf("\tColor: %d, %d, %d, %d\n", c.r, c.g, c.b, c.a);
      inner_size += 1;
    }
    size += 1;
  }
}
*/