#include <vector>

#include "texture.h"
#include "texture_pack.h"
#include "font_renderer.h"
#include "ball.h"
#include "paddle.h"
#include "constants.h"
#include "collision.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <sstream>

//The window we'll be rendering to
SDL_Window* window = nullptr;

//The window renderer
SDL_Renderer* renderer = nullptr;

Mix_Chunk* bop = nullptr;
Mix_Chunk* boop = nullptr;

bool Init(TexturePack* textures) {
  //Initialization flag
  bool success = true;

  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    return false;
  }

  //Set texture filtering to linear
  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    printf("Warning: Linear texture filtering not enabled!");
  }

  //Create window
  window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
    return false;
  }

  //Create vsynced renderer for window
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == nullptr) {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    return false;
  }

  //Initialize renderer color
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  //Initialize PNG loading
  int img_flags = IMG_INIT_PNG;
  if (!(IMG_Init(img_flags) & img_flags)) {
    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    return false;
  }

  //Initialize SDL_ttf
  if(TTF_Init() == -1) {
    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    return false;
  }
  
  //Initialize SDL_mixer
  if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0) {
    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    return false;
  }

  //TODO: use seperate texture pack for fonts
  for (int i = 0; i < static_cast<int>(TextureName::TOTAL_NUM_TEXTURES); ++i) {
    textures->InitTexture(static_cast<TextureName>(i), renderer);
  }

  return success;
}

bool LoadMedia(TexturePack* textures) {
  //Loading success flag
  bool success = true;

  for (int i = 0; i < static_cast<int>(TextureName::TOTAL_NUM_TEXTURES); ++i) {
    Texture* current = textures->GetTexture(static_cast<TextureName>(i));
    std::string path = textures->TexturePath(static_cast<TextureName>(i));
    if (!current->LoadFromFile(path)) {
      printf("Failed to load texture: %s\n", path.c_str());
      success = false;
    }
  }

  bop = Mix_LoadWAV("assets/sfx/blip-fs5.wav");
  if(bop == nullptr) {
		printf( "Failed to load bop sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
  }
  
  boop = Mix_LoadWAV("assets/sfx/blip-fs4.wav");
  if(boop == nullptr) {
		printf( "Failed to load boop sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
  }

  return success;
}

void Close(TexturePack* textures) {
  //Free loaded images
  for (int i = 0; i < static_cast<int>(TextureName::TOTAL_NUM_TEXTURES); ++i) {
    Texture* current = textures->GetTexture(static_cast<TextureName>(i));
    current->Free();    
  }

  //Destroy window
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  window = nullptr;
  renderer = nullptr;

  Mix_FreeChunk(bop);
  bop = nullptr;

  Mix_FreeChunk(boop);
  boop = nullptr;

  //Quit SDL subsystems
  Mix_Quit();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

void PrintRect(SDL_Rect* rect) {
  printf("Rect - x: %d, y: %d, w: %d, h: %d\n", rect->x, rect->y, rect->w, rect->h);
}

void GameLoop(TexturePack* textures) {
  bool quit = false;

  SDL_Event e;

  Ball ball;

  Paddle player(true);
  Paddle ai(false);

  int player_score = 0;
  int ai_score = 0;

  std::vector<SDL_Rect*> ball_colliders;

  ball_colliders.push_back(player.GetCollider());
  ball_colliders.push_back(ai.GetCollider());

  Uint64 time_now = SDL_GetPerformanceCounter();
  Uint64 time_last = 0;
  double delta_time = 0;

  SDL_Color text_color = { 255, 255, 255, 255 };

  FontRenderer font_renderer;

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

      player.HandleEvent(e);
    }

    ai.Autopilot(ball.GetCollider());

    // Paddles must move before ball!
    ai.Move(delta_time);
    player.Move(delta_time);
    CollisionType collision = ball.Move(delta_time, ball_colliders, &player_score, &ai_score);

    //Clear screen
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    //Render bg
    textures->GetTexture(TextureName::BG)->Render(0, 0);
    
    // Render paddles
    ai.Render(textures->GetTexture(TextureName::PADDLE));
    player.Render(textures->GetTexture(TextureName::PADDLE));

    //Render dot
    ball.Render(textures->GetTexture(TextureName::BALL));

    // Render text
    int text_width = 0;
    int text_height = 0;
    std::ostringstream score_stream;
    score_stream << player_score << "  " << ai_score;

    std::string score_text = score_stream.str();
    
    if (font_renderer.SizeFont(FontName::FORWARD, 42, score_text, &text_width, &text_height) != 0) {
      printf("Failure to size font!\n");
    }

    font_renderer.RenderFont(renderer, FontName::FORWARD, 42, 
    /*x=*/(constants::SCREEN_WIDTH - text_width) / 2, /*y=*/10, score_text, text_color);

    // This is a terrible hack due to the font rendering being broken
    if (player_score == -1) {
      player_score = 0;
    }

    switch (collision) {
      case CollisionType::WALL:
      case CollisionType::PADDLE:
        Mix_PlayChannel( -1, bop, 0 );
        break; 
      case CollisionType::SCORE:
        Mix_PlayChannel(-1, boop, 0);
        break;
      default: break;
    }

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
