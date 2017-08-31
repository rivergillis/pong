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

class TexturePack {
 public:
  TexturePack();

  ~TexturePack();

  Texture* GetTexture(TextureName name);

  std::string TexturePath(TextureName name);

  void InitTexture(TextureName name, SDL_Renderer* renderer, TTF_Font* font = nullptr);

 private:
  std::vector<Texture> textures_;
};

#endif