#include "collision.h"

#include <SDL2/SDL.h>

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