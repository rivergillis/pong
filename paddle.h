#ifndef PADDLE_H_
#define PADDLE_H_

#include <SDL2/SDL.h>
#include "texture.h"

class Paddle {
 public:
  // The dimensions of the paddle
  static const int PADDLE_WIDTH = 30;
  static const int PADDLE_HEIGHT = 100;

  // The maximum vertical velocity of the paddle
  static const int PADDLE_VEL = 10;

  Paddle();

  void HandleEvent(SDL_Event& e);

  //Moves the paddle
  // NOTE: Paddle doesn't check collision, so we need to move all
  // of the paddles BEFORE we move the ball!
  void Move(double delta_time);
  
  //Shows the ball on the screen
  void Render(Texture* texture);

  SDL_Rect* GetCollider() { return &collider_; }
  
 private:
  //The X and Y offsets of the paddle
  int x_pos_, y_pos_;
  
  //The velocity of the paddle, vert only
  int y_vel_;

  //Paddle's collision box
  SDL_Rect collider_;
};

#endif