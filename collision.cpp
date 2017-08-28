#include "collision.h"

#include <utility>

#include <SDL2/SDL.h>

// Returns the point at which A needs to be moved to to avoid collision.
std::pair<int, int> checkCollisionWithPoints(SDL_Rect a, SDL_Rect b, int vel_x, int vel_y) {
  SDL_Rect result_rect;
  int result_x = a.x;
  int result_y = a.y;

  if (SDL_IntersectRect(&a, &b, &result_rect) == SDL_FALSE) {
    return {result_x, result_y};
  }

  printf("Intersection rect - x: %d, y: %d, w: %d, h: %d\n", result_rect.x,
    result_rect.y, result_rect.w, result_rect.h);

  // use the smallest intersection delta
  // horizontal collision
  if (result_rect.w < result_rect.h) {
    // if positive velocity, a hit the left side of b
    if (vel_x >= 0) {
      result_x = b.x - a.w;
    } else {
      // if negative velocity, a hit the right side of b
      result_x = b.x + b.w;
    }
  // vertical collision
  } else {
    // if positive velocity, a hit the top side of b
    if (vel_y >= 0) {
      result_y = b.y - a.h;
    } else {
      // if negative velocity, a hit the bottom side of b
      result_y = b.y + b.h;
    }
  }

  return {result_x, result_y};
}

// TODO(jgillis): Make this check only x or y
bool checkCollision(SDL_Rect a, SDL_Rect b)
{
  //The sides of the rectangles
  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA, bottomB;

  //Calculate the sides of rect A
  leftA = a.x;
  rightA = a.x + a.w;
  topA = a.y;
  bottomA = a.y + a.h;

  //Calculate the sides of rect B
  leftB = b.x;
  rightB = b.x + b.w;
  topB = b.y;
  bottomB = b.y + b.h;

  //If any of the sides from A are outside of B
  if( bottomA <= topB )
  {
      return false;
  }

  if( topA >= bottomB )
  {
      return false;
  }

  if( rightA <= leftB )
  {
      return false;
  }

  if( leftA >= rightB )
  {
      return false;
  }

  //If none of the sides from A are outside B
  return true;
}

int checkCollisionX(SDL_Rect a, SDL_Rect b) {
  //The sides of the rectangles
  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA, bottomB;

  //Calculate the sides of rect A
  leftA = a.x;
  rightA = a.x + a.w;
  topA = a.y;
  bottomA = a.y + a.h;

  //Calculate the sides of rect B
  leftB = b.x;
  rightB = b.x + b.w;
  topB = b.y;
  bottomB = b.y + b.h;

  // A touches the left side of B
  if ((rightA >= leftB) && (rightA <= rightB)) {
    return -1;
  }

  // A touches the right side of B
  if ((leftA <= rightB) && (rightA >= rightB)) {
    return 1;
  }

  return 0;
}

int checkCollisionY(SDL_Rect a, SDL_Rect b) {
  //The sides of the rectangles
  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA, bottomB;

  //Calculate the sides of rect A
  leftA = a.x;
  rightA = a.x + a.w;
  topA = a.y;
  bottomA = a.y + a.h;

  //Calculate the sides of rect B
  leftB = b.x;
  rightB = b.x + b.w;
  topB = b.y;
  bottomB = b.y + b.h;

  // A touches the top side of B
  if ((bottomA >= topB) && (bottomA <= bottomB)) {
    return -1;
  }

  // A touches the bottom side of B
  if ((topA <= bottomB) && (topA >= bottomB)) {
    return 1;
  }

  return 0;
}