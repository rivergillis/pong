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
	//Initializes variables
	Texture();

	// automatically inits
	Texture(SDL_Renderer* renderer, TTF_Font* font = nullptr);

	//Deallocates memory
	~Texture();

	void Init(SDL_Renderer* renderer, TTF_Font* font = nullptr);

	//Loads image at specified path
	bool LoadFromFile(std::string path);

	#ifdef _SDL_TTF_H
	//Creates image from font string
	bool LoadFromRenderedText(std::string texture_text, SDL_Color text_color);
	#endif

	//Deallocates texture
	void Free();

	//Set color modulation
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void SetBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void SetAlpha(Uint8 alpha);

	//Renders texture at given point
	void Render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int GetWidth();
	int GetHeight();

 private:
	//The actual hardware texture
	SDL_Texture* texture_;

	// The renderer we're using to render this texture
	SDL_Renderer* renderer_;

	// The font we're using for this texture
	TTF_Font* font_;

	//Image dimensions
	int width_;
	int height_;

	bool has_init_;
};

#endif