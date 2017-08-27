#include "texture.h"
#include "texture_pack.h"
#include "ball.h"
#include "constants.h"
#include "collision.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init(TexturePack* textures)
{
  //Initialization flag
  bool success = true;

  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  }
  else
  {
    //Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
      printf("Warning: Linear texture filtering not enabled!");
    }

    //Create window
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    }
    else
    {
      //Create vsynced renderer for window
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (gRenderer == NULL)
      {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
      }
      else
      {
        //Initialize renderer color
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
          printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
          success = false;
        }
      }
    }
  }

  //TODO: Refactor above
  //TODO: use seperate texture pack for fonts
  for (int i = 0; i < TextureName::TOTAL_NUM_TEXTURES; ++i) {
    textures->initTexture(static_cast<TextureName>(i), gRenderer);
  }

  return success;
}

bool loadMedia(TexturePack* textures)
{
  //Loading success flag
  bool success = true;

  for (int i = 0; i < TextureName::TOTAL_NUM_TEXTURES; ++i) {
    Texture* current = textures->getTexture(static_cast<TextureName>(i));
    std::string path = textures->texturePath(static_cast<TextureName>(i));
    if (!current->loadFromFile(path)) {
      printf("Failed to load texture: %s\n", path.c_str());
      success = false;
    }
  }

  return success;
}

void close(TexturePack* textures)
{
  //Free loaded images
  for (int i = 0; i < TextureName::TOTAL_NUM_TEXTURES; ++i) {
    Texture* current = textures->getTexture(static_cast<TextureName>(i));
    current->free();    
  }

  //Destroy window
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}

void gameLoop(TexturePack* textures) {
  bool quit = false;

  SDL_Event e;

  Ball ball;

  //Set the wall
  SDL_Rect wall;
  wall.x = 300;
  wall.y = 40;
  wall.w = 40;
  wall.h = 400;  

  Uint64 time_now = SDL_GetPerformanceCounter();
  Uint64 time_last = 0;
  double deltaTime = 0;

  while (!quit) {
    time_last = time_now;
    time_now = SDL_GetPerformanceCounter();
 
    deltaTime = ((time_now - time_last)*1000 / (double)SDL_GetPerformanceFrequency());

    printf("Time passed: %f\n", deltaTime);

    //Handle events on queue
    while(SDL_PollEvent(&e) != 0) {
      //User requests quit
      if(e.type == SDL_QUIT) {
        quit = true;
      }

      //Handle input for the dot
      ball.handleEvent(e);
    }

    ball.move(wall);

    //Clear screen
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    //Render bg
    textures->getTexture(TextureName::BG)->render(0, 0);

    //Render wall
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);		
    SDL_RenderDrawRect(gRenderer, &wall);
    
    //Render dot
    ball.render(textures->getTexture(TextureName::BALL));

    //Update screen
    SDL_RenderPresent(gRenderer);
  }
}

int main(int argc, char *args[])
{
  TexturePack textures;

  if (!init(&textures)) {
    printf("Failed to initialize main game!\n");
    return -1;
  }

  if (!loadMedia(&textures)) {
    printf("Failed to load media!\n");
    return -1;
  }

  gameLoop(&textures);

  close(&textures);

  return 0;
}
