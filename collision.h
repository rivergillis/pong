#ifndef COLLISION_H_
#define COLLISION_H_

#include <utility>

#include <SDL2/SDL.h>

bool CheckCollision(SDL_Rect a, SDL_Rect b);

int CheckCollisionX(SDL_Rect a, SDL_Rect b);

int CheckCollisionY(SDL_Rect a, SDL_Rect b);

std::pair<int, int> CheckCollisionWithPoints(SDL_Rect a, SDL_Rect b, int vel_x, int vel_y);

#endif