#ifndef TEXTURE_PACK_H_
#define TEXTURE_PACK_H_

#include <vector>

#include "texture.h"

enum TextureName {
  BG = 0,
  BALL,
  PADDLE,
  TOTAL_NUM_TEXTURES
};

class TexturePack {
 public:
  TexturePack();

  ~TexturePack();

  Texture* getTexture(TextureName name);

  std::string texturePath(TextureName name);

  void initTexture(TextureName name, SDL_Renderer* renderer, TTF_Font* font = nullptr);

 private:
  std::vector<Texture> textures_;
};

#endif