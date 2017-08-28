#include "texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

Texture::Texture() {
  //Initialize
  texture_ = NULL;
  width_ = 0;
  height_ = 0;

  has_init_ = false;
}

Texture::Texture(SDL_Renderer* renderer, TTF_Font* font) {
  //Initialize
  texture_ = NULL;
  width_ = 0;
  height_ = 0;

  Init(renderer, font);
}


Texture::~Texture() {
  //Deallocate
  Free();
}

void Texture::Init(SDL_Renderer* renderer, TTF_Font* font) {
  renderer_ = renderer;
  font_ = font;

  has_init_ = true;
}

bool Texture::LoadFromFile(std::string path) {
  if (!has_init_) {
    printf("Tried to load texture without first initializing!");
    return false;
  }

  //Get rid of preexisting texture
  Free();

  //The final texture
  SDL_Texture* new_texture = NULL;

  //Load image at specified path
  SDL_Surface* loaded_surface = IMG_Load(path.c_str());
  if (loaded_surface == NULL) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
  } else {
    //Color key image
    SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF));

    //Create texture from surface pixels
    new_texture = SDL_CreateTextureFromSurface(renderer_, loaded_surface);
    if (new_texture == NULL) {
      printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    } else {
      //Get image dimensions
      width_ = loaded_surface->w;
      height_ = loaded_surface->h;
    }

    //Get rid of old loaded surface
    SDL_FreeSurface(loaded_surface);
  }

  //Return success
  texture_ = new_texture;
  return texture_ != NULL;
}

#ifdef _SDL_TTF_H
bool Texture::LoadFromRenderedText(std::string texture_text, SDL_Color text_color) {
  if (!has_init_) {
    printf("Tried to load texture from text without first initializing!");
    return false;
  }

  //Get rid of preexisting texture
  Free();

  //Render text surface
  SDL_Surface* text_surface = TTF_RenderText_Solid(font_, texture_text.c_str(), text_color);
  if (text_surface != NULL) {
    //Create texture from surface pixels
    texture_ = SDL_CreateTextureFromSurface(renderer_, text_surface);
    if (texture_ == NULL) {
      printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    } else {
      //Get image dimensions
      width_ = text_surface->w;
      height_ = text_surface->h;
    }

    //Get rid of old surface
    SDL_FreeSurface(text_surface);
  } else {
    printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
  }

  //Return success
  return texture_ != NULL;
}
#endif

void Texture::Free() {
  //Free texture if it exists
  if (texture_ != NULL) {
    SDL_DestroyTexture(texture_);
    texture_ = NULL;
    width_ = 0;
    height_ = 0;
  }
}

void Texture::SetColor(Uint8 red, Uint8 green, Uint8 blue) {
  //Modulate texture rgb
  SDL_SetTextureColorMod(texture_, red, green, blue);
}

void Texture::SetBlendMode(SDL_BlendMode blending) {
  //Set blending function
  SDL_SetTextureBlendMode(texture_, blending);
}

void Texture::SetAlpha(Uint8 alpha) {
  //Modulate texture alpha
  SDL_SetTextureAlphaMod(texture_, alpha);
}

void Texture::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
  if (!has_init_) {
    printf("Tried to render texture without first initializing!");
  }

  //Set rendering space and render to screen
  SDL_Rect render_quad = {x, y, width_, height_};

  //Set clip rendering dimensions
  if (clip != NULL) {
    render_quad.w = clip->w;
    render_quad.h = clip->h;
  }

  //Render to screen
  SDL_RenderCopyEx(renderer_, texture_, clip, &render_quad, angle, center, flip);
}

int Texture::GetWidth() {
  return width_;
}

int Texture::GetHeight() {
  return height_;
}
