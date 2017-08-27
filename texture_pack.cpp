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
    tex.free();
  }
}

Texture* TexturePack::getTexture(TextureName name) {
  return &textures_[name];
}

void TexturePack::initTexture(TextureName name, SDL_Renderer* renderer, TTF_Font* font) {
  textures_[name].init(renderer, font);
}


std::string TexturePack::texturePath(TextureName name) {
  switch(name) {
    case TextureName::BALL:
      return "textures/ball.png";
      break;
    case TextureName::PADDLE:
      return "textures/paddle.png";
      break;
    case TextureName::TOTAL_NUM_TEXTURES:
      return "";
      break;
  }
}