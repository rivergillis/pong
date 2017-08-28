#include "texture_pack.h"

#include <vector>

#include "texture.h"

TexturePack::TexturePack() {
  for (int i = 0; i < TextureName::TOTAL_NUM_TEXTURES; ++i) {
    textures_.emplace_back();
  }
}

TexturePack::~TexturePack() {
  for (auto& tex : textures_) {
    tex.Free();
  }
}

Texture* TexturePack::GetTexture(TextureName name) {
  return &textures_[name];
}

void TexturePack::InitTexture(TextureName name, SDL_Renderer* renderer, TTF_Font* font) {
  textures_[name].Init(renderer, font);
}


std::string TexturePack::TexturePath(TextureName name) {
  switch(name) {
    case TextureName::BG:
      return "textures/bg.png";
      break;
    case TextureName::BALL:
      return "textures/ball.png";
      break;
    case TextureName::PADDLE:
      return "textures/paddle.png";
      break;
    case TextureName::TOTAL_NUM_TEXTURES:
      printf("Tried to access texture for TOTAL_NUM_TEXTURES!\n");
      return "";
      break;
  }
}