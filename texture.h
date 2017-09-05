// texture.h
// Author: River Gillis
//
// The main interface for loading, using, and rendering textures.
// This is done through SDL_Textures.
// Requires access to an SDL_Renderer in order to actually render the
// textures.
//
// Usage:
//	Texture texture(renderer);
//	texture.LoadFromFile(file_name);
//	texture.Render(x, y);

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

class Texture
{
 public:
	// Initializes variables
	Texture();

	// Automatically calls Init()
	Texture(SDL_Renderer* renderer, TTF_Font* font = nullptr);

	// Deallocates memory, calls Free()
	~Texture();

	void Init(SDL_Renderer* renderer, TTF_Font* font = nullptr);

	// Loads image at specified path
	bool LoadFromFile(const std::string& path);

	#ifdef _SDL_TTF_H
	// Renders an image from a font string to the texture.
	bool LoadFromRenderedText(const std::string& texture_text, SDL_Color text_color);
	#endif

	// Deallocates @texture_
	void Free();

	// Set color modulation
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);

	// Set blending
	void SetBlendMode(SDL_BlendMode blending);

	// Set alpha modulation
	void SetAlpha(Uint8 alpha);

	// Renders texture at given point
	// 	x, y: The top-left point at which to render the texture
	//	clip: The rectangle of the texture to render
	//	angle: The angle of rotation to rotate the texture
	//	center: The point at which rotation occurs
	//	flip: The style of flipping for the texture
	void Render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int GetWidth();
	int GetHeight();

	// Debug only, return the texture pointer
	SDL_Texture* GetPtr() { return texture_; }

 private:
	// The actual SDL_Texture
	SDL_Texture* texture_;

	// The renderer we're using to render this texture
	SDL_Renderer* renderer_;

	// The font we're using for this texture
	TTF_Font* font_;

	//Image dimensions
	int width_;
	int height_;

	// whether or not the texture has called Init()
	bool has_init_;
};

#endif