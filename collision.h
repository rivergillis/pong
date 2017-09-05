// collision.h

// Handles collision detection.
// CheckCollisionWithPoints handles detection and correction (not very well).

#ifndef COLLISION_H_
#define COLLISION_H_

#include <utility>

#include <SDL2/SDL.h>

bool CheckCollision(SDL_Rect a, SDL_Rect b);

int CheckCollisionX(SDL_Rect a, SDL_Rect b);

int CheckCollisionY(SDL_Rect a, SDL_Rect b);

// Returns the pair of points to move @a to in order to no longer be colliding with @b
//  vel_x, vel_y: the velocity of @a
std::pair<int, int> CheckCollisionWithPoints(SDL_Rect a, SDL_Rect b, int vel_x, int vel_y);

#endif