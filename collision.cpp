#include "collision.h"

#include <utility>

#include <SDL2/SDL.h>

// Returns the point at which A needs to be moved to to avoid collision.
std::pair<int, int> CheckCollisionWithPoints(SDL_Rect a, SDL_Rect b, int vel_x, int vel_y) {
  SDL_Rect result_rect;
  int result_x = a.x;
  int result_y = a.y;

  if (SDL_IntersectRect(&a, &b, &result_rect) == SDL_FALSE) {
    return {result_x, result_y};
  }

  // printf("Intersection rect - x: %d, y: %d, w: %d, h: %d\n", result_rect.x,
  //   result_rect.y, result_rect.w, result_rect.h);

  // move back horizontally if moving faster and horizontal pen
  if ((abs(vel_x) >= abs(vel_y)) && (result_rect.w > 0)) {
    // moving right
    if (vel_x > 0) {
      result_x = b.x - a.w;
    } else {
      // moving left
      result_x = b.x + b.w;
    }
  } else {
    // otherwise move back vertically
    // moving down
    if (vel_y > 0) {
      result_y = b.y - a.h;
    } else {
      // moving up
      result_y = b.y + b.h;
    }
  }
  
  return {result_x, result_y};
}

// TODO(jgillis): Make this check only x or y
bool CheckCollision(SDL_Rect a, SDL_Rect b) {
  //The sides of the rectangles
  int left_a, left_b;
  int right_a, right_b;
  int top_a, top_b;
  int bottom_a, bottom_b;

  //Calculate the sides of rect A
  left_a = a.x;
  right_a = a.x + a.w;
  top_a = a.y;
  bottom_a = a.y + a.h;

  //Calculate the sides of rect B
  left_b = b.x;
  right_b = b.x + b.w;
  top_b = b.y;
  bottom_b = b.y + b.h;

  //If any of the sides from A are outside of B
  if(bottom_a <= top_b) {
      return false;
  }

  if(top_a >= bottom_b) {
      return false;
  }

  if( right_a <= left_b ) {
      return false;
  }

  if(left_a >= right_b) {
      return false;
  }

  //If none of the sides from A are outside B
  return true;
}

int CheckCollisionX(SDL_Rect a, SDL_Rect b) {
  //The sides of the rectangles
  int left_a, left_b;
  int right_a, right_b;
  int top_a, top_b;
  int bottom_a, bottom_b;

  //Calculate the sides of rect A
  left_a = a.x;
  right_a = a.x + a.w;
  top_a = a.y;
  bottom_a = a.y + a.h;

  //Calculate the sides of rect B
  left_b = b.x;
  right_b = b.x + b.w;
  top_b = b.y;
  bottom_b = b.y + b.h;

  // A touches the left side of B
  if ((right_a >= left_b) && (right_a <= right_b)) {
    return -1;
  }

  // A touches the right side of B
  if ((left_a <= right_b) && (right_a >= right_b)) {
    return 1;
  }

  return 0;
}

int CheckCollisionY(SDL_Rect a, SDL_Rect b) {
  //The sides of the rectangles
  int left_a, left_b;
  int right_a, right_b;
  int top_a, top_b;
  int bottom_a, bottom_b;

  //Calculate the sides of rect A
  left_a = a.x;
  right_a = a.x + a.w;
  top_a = a.y;
  bottom_a = a.y + a.h;

  //Calculate the sides of rect B
  left_b = b.x;
  right_b = b.x + b.w;
  top_b = b.y;
  bottom_b = b.y + b.h;

  // A touches the top side of B
  if ((bottom_a >= top_b) && (bottom_a <= bottom_b)) {
    return -1;
  }

  // A touches the bottom side of B
  if ((top_a <= bottom_b) && (top_a >= bottom_b)) {
    return 1;
  }

  return 0;
}