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

		void init(SDL_Renderer* renderer, TTF_Font* font = nullptr);

		//Loads image at specified path
		bool loadFromFile(std::string path);
		
		#ifdef _SDL_TTF_H
		//Creates image from font string
		bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
		#endif

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor(Uint8 red, Uint8 green, Uint8 blue);

		//Set blending
		void setBlendMode(SDL_BlendMode blending);

		//Set alpha modulation
		void setAlpha(Uint8 alpha);
		
		//Renders texture at given point
		void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		//Gets image dimensions
		int getWidth();
		int getHeight();

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