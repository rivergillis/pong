#ifndef COLLISION_H_
#define COLLISION_H_

#include <SDL2/SDL.h>

bool checkCollision(SDL_Rect a, SDL_Rect b);

int checkCollisionX(SDL_Rect a, SDL_Rect b);

int checkCollisionY(SDL_Rect a, SDL_Rect b);

#endif