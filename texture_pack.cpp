#include "texture_pack.h"

#include <vector>

#include "texture.h"

TexturePack::TexturePack() {
  textures_.reserve(static_cast<int>(TextureName::TOTAL_NUM_TEXTURES));
  for (int i = 0; i < static_cast<int>(TextureName::TOTAL_NUM_TEXTURES); ++i) {
    textures_.emplace_back();
  }
}

TexturePack::~TexturePack() {
  for (auto& tex : textures_) {
    tex.Free();
  }
}

Texture* TexturePack::GetTexture(TextureName name) {
  if (name == TextureName::TOTAL_NUM_TEXTURES) { return nullptr; }
  return &textures_[static_cast<int>(name)];
}

void TexturePack::InitTexture(TextureName name, SDL_Renderer* renderer, TTF_Font* font) {
  if (name == TextureName::TOTAL_NUM_TEXTURES) { return; }  
  textures_[static_cast<int>(name)].Init(renderer, font);
}

std::string TexturePack::TexturePath(TextureName name) {
  switch(name) {
    case TextureName::BG:
      return "assets/textures/bg.png";
      break;
    case TextureName::BALL:
      return "assets/textures/ball.png";
      break;
    case TextureName::PADDLE:
      return "assets/textures/paddle.png";
      break;
    case TextureName::TOTAL_NUM_TEXTURES:
      printf("Tried to access texture for TOTAL_NUM_TEXTURES!\n");
      return "";
      break;
  }
}