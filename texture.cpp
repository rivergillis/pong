#include "texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

Texture::Texture()
{
  //Initialize
  texture_ = NULL;
  width_ = 0;
  height_ = 0;

  has_init_ = false;
}

Texture::Texture(SDL_Renderer* renderer, TTF_Font* font)
{
  //Initialize
  texture_ = NULL;
  width_ = 0;
  height_ = 0;

  init(renderer, font);
}


Texture::~Texture()
{
  //Deallocate
  free();
}

void Texture::init(SDL_Renderer* renderer, TTF_Font* font) {
  renderer_ = renderer;
  font_ = font;

  has_init_ = true;
}

bool Texture::loadFromFile(std::string path)
{
  if (!has_init_) {
    printf("Tried to load texture without first initializing!");
    return false;
  }

  //Get rid of preexisting texture
  free();

  //The final texture
  SDL_Texture* newTexture = NULL;

  //Load image at specified path
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL)
  {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
  }
  else
  {
    //Color key image
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(renderer_, loadedSurface);
    if (newTexture == NULL)
    {
      printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
      //Get image dimensions
      width_ = loadedSurface->w;
      height_ = loadedSurface->h;
    }

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
  }

  //Return success
  texture_ = newTexture;
  return texture_ != NULL;
}

#ifdef _SDL_TTF_H
bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
  if (!has_init_) {
    printf("Tried to load texture from text without first initializing!");
    return false;
  }

  //Get rid of preexisting texture
  free();

  //Render text surface
  SDL_Surface* textSurface = TTF_RenderText_Solid(font_, textureText.c_str(), textColor);
  if (textSurface != NULL)
  {
    //Create texture from surface pixels
    texture_ = SDL_CreateTextureFromSurface(renderer_, textSurface);
    if (texture_ == NULL)
    {
      printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }
    else
    {
      //Get image dimensions
      width_ = textSurface->w;
      height_ = textSurface->h;
    }

    //Get rid of old surface
    SDL_FreeSurface(textSurface);
  }
  else
  {
    printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
  }

  //Return success
  return texture_ != NULL;
}
#endif

void Texture::free()
{
  //Free texture if it exists
  if (texture_ != NULL)
  {
    SDL_DestroyTexture(texture_);
    texture_ = NULL;
    width_ = 0;
    height_ = 0;
  }
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
  //Modulate texture rgb
  SDL_SetTextureColorMod(texture_, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending)
{
  //Set blending function
  SDL_SetTextureBlendMode(texture_, blending);
}

void Texture::setAlpha(Uint8 alpha)
{
  //Modulate texture alpha
  SDL_SetTextureAlphaMod(texture_, alpha);
}

void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
  if (!has_init_) {
    printf("Tried to render texture without first initializing!");
  }

  //Set rendering space and render to screen
  SDL_Rect renderQuad = {x, y, width_, height_};

  //Set clip rendering dimensions
  if (clip != NULL)
  {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  //Render to screen
  SDL_RenderCopyEx(renderer_, texture_, clip, &renderQuad, angle, center, flip);
}

int Texture::getWidth()
{
  return width_;
}

int Texture::getHeight()
{
  return height_;
}
