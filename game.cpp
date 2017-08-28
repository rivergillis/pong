#include <vector>

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
SDL_Window* window = NULL;

//The window renderer
SDL_Renderer* renderer = NULL;

bool Init(TexturePack* textures) {
  //Initialization flag
  bool success = true;

  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  } else {
    //Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
      printf("Warning: Linear texture filtering not enabled!");
    }

    //Create window
    window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    } else {
      //Create vsynced renderer for window
      renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
      } else {
        //Initialize renderer color
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

        //Initialize PNG loading
        int img_flags = IMG_INIT_PNG;
        if (!(IMG_Init(img_flags) & img_flags)) {
          printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
          success = false;
        }
      }
    }
  }

  //TODO: Refactor above
  //TODO: use seperate texture pack for fonts
  for (int i = 0; i < TextureName::TOTAL_NUM_TEXTURES; ++i) {
    textures->InitTexture(static_cast<TextureName>(i), renderer);
  }

  return success;
}

bool LoadMedia(TexturePack* textures)
{
  //Loading success flag
  bool success = true;

  for (int i = 0; i < TextureName::TOTAL_NUM_TEXTURES; ++i) {
    Texture* current = textures->GetTexture(static_cast<TextureName>(i));
    std::string path = textures->TexturePath(static_cast<TextureName>(i));
    if (!current->LoadFromFile(path)) {
      printf("Failed to load texture: %s\n", path.c_str());
      success = false;
    }
  }

  return success;
}

void Close(TexturePack* textures)
{
  //Free loaded images
  for (int i = 0; i < TextureName::TOTAL_NUM_TEXTURES; ++i) {
    Texture* current = textures->GetTexture(static_cast<TextureName>(i));
    current->Free();    
  }

  //Destroy window
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  window = NULL;
  renderer = NULL;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}

void GameLoop(TexturePack* textures) {
  bool quit = false;

  SDL_Event e;

  Ball ball;

  //Set the wall
  SDL_Rect wall;
  wall.x = 300;
  wall.y = 40;
  wall.w = 40;
  wall.h = 400;

  std::vector<SDL_Rect> ball_colliders;

  ball_colliders.push_back(wall);

  Uint64 time_now = SDL_GetPerformanceCounter();
  Uint64 time_last = 0;
  double delta_time = 0;

  while (!quit) {
    time_last = time_now;
    time_now = SDL_GetPerformanceCounter();
 
    delta_time = ((time_now - time_last)*1000 / (double)SDL_GetPerformanceFrequency());

    //Handle events on queue
    while(SDL_PollEvent(&e) != 0) {
      //User requests quit
      if(e.type == SDL_QUIT) {
        quit = true;
      }

      //Handle input for the dot
      ball.HandleEvent(e);
    }

    ball.Move(delta_time, ball_colliders);

    //Clear screen
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    //Render bg
    textures->GetTexture(TextureName::BG)->Render(0, 0);

    //Render wall
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);		
    SDL_RenderDrawRect(renderer, &wall);
    
    //Render dot
    ball.Render(textures->GetTexture(TextureName::BALL));

    //Update screen
    SDL_RenderPresent(renderer);
  }
}

int main(int argc, char *args[]) {
  TexturePack textures;

  if (!Init(&textures)) {
    printf("Failed to initialize main game!\n");
    return -1;
  }

  if (!LoadMedia(&textures)) {
    printf("Failed to load media!\n");
    return -1;
  }

  GameLoop(&textures);

  Close(&textures);

  return 0;
}
