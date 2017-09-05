// texture_pack.h
// Author: River Gillis
//
// TexturePack holds all of the Textures for the game
// It provides an easy way to refer to textures using the TextureName enumclass
//
// Usage:
//  TexturePack pack;
//  for (int i = 0; i < static_cast<int>(TextureName::TOTAL_NUM_TEXTURES); ++i) {
//    pack.InitTexture(static_cast<TextureName>(i), renderer);
//  }
// pack.GetTexture(TextureName::BALL)->Render(x,y);

#ifndef TEXTURE_PACK_H_
#define TEXTURE_PACK_H_

#include <vector>

#include "texture.h"

enum class TextureName {
  BG = 0,
  BALL,
  PADDLE,
  TOTAL_NUM_TEXTURES
};

// TODO: implement LoadTexture(TextureName name);
class TexturePack {
 public:
  TexturePack();

  ~TexturePack();

  Texture* GetTexture(TextureName name);

  // Returns a file path to the texture @name
  std::string TexturePath(TextureName name);

  // Initializes the texture @name with @renderer and @font
  // TODO: remove @font, since font textures are handled by FontRenderer
  // TODO: implement InitAllTextures()
  void InitTexture(TextureName name, SDL_Renderer* renderer, TTF_Font* font = nullptr);

 private:
  // All of the textures used in the game
  std::vector<Texture> textures_;
};

#endif