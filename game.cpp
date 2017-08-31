#include <vector>

#include "texture.h"
#include "texture_pack.h"
#include "ball.h"
#include "paddle.h"
#include "constants.h"
#include "collision.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>

//The window we'll be rendering to
SDL_Window* window = NULL;

//The window renderer
SDL_Renderer* renderer = NULL;

TTF_Font* score_font = NULL;

Texture score_font_texture;

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

         //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
      }
    }
  }

  score_font = TTF_OpenFont("assets/fonts/fff-forward.ttf", 42);
  if (score_font == NULL) {
    printf("Error: Failed to open font fff-forward.ttf! Error: %s\n", TTF_GetError());
  } else {
    score_font_texture.Init(renderer, score_font);
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

  SDL_Color textColor = { 255, 255, 255, 255 };
  score_font_texture.LoadFromRenderedText("0  0", textColor);  

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

    int old_player_score = player_score;
    int old_ai_score = ai_score;

    // Paddles must move before ball!
    ai.Move(delta_time);
    player.Move(delta_time);
    ball.Move(delta_time, ball_colliders, &player_score, &ai_score);

    if (player_score != old_player_score || ai_score != old_ai_score) {
      std::ostringstream ss;
      ss << player_score << "  " << ai_score;
      score_font_texture.LoadFromRenderedText(ss.str(), textColor);
    }

    if (player_score != old_player_score) {
      printf("Player has scored! Player Score: %d\n", player_score);
    } else if (ai_score != old_ai_score) {
      printf("AI has scored! AI Score: %d\n", ai_score);
    }

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
    score_font_texture.Render((constants::SCREEN_WIDTH - score_font_texture.GetWidth()) / 2, 10);

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
