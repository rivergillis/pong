// paddle.h
// Author: River Gillis
//
// Paddle contains the entire state of the paddle used in Pong. It works for
// either a human-controlled paddle or an AI-controlled paddle.
//
// Usage:
//  Ball ball;
//  Paddle player(true);
//  Paddle ai(false);
//  while (game_loop) {
//    // move the paddles before the ball
//    player.HandleEvent(event);
//    player.Move(delta);
//    ai.Autopilot(ball.GetCollider());
//    ai.Move(delta);
//    // colliders = player.GetCollider() and ai.GetCollider()
//    ball.Move(delta, colliders, &player_score, &ai_score);
//    // rendering...
//  }

#ifndef PADDLE_H_
#define PADDLE_H_

#include <SDL2/SDL.h>
#include "texture.h"

class Paddle {
 public:
  // The dimensions of the paddle
  static const int PADDLE_WIDTH = 50;
  static const int PADDLE_HEIGHT = 120;

  // The maximum vertical velocity of the paddle
  static const int PADDLE_VEL = 10;

  // If player=true, set to left side
  Paddle(bool player);

  // To be used for the player paddle, modifies the velocity based on
  // the up/down key press/release
  void HandleEvent(SDL_Event& e);

  // Moves the paddle
  // NOTE: Paddle doesn't check collision, so we need to move all
  // of the paddles BEFORE we move the ball!
  void Move(double delta_time);
  
  // Render the paddle to the screen using @texture
  void Render(Texture* texture);

  // To be used for the ai paddle, sets the velocities to move
  // towards the ball
  void Autopilot(SDL_Rect* ball);

  SDL_Rect* GetCollider() { return &collider_; }
  
 private:
  // The X and Y offsets of the paddle
  int x_pos_, y_pos_;
  
  // The velocity of the paddle, vert only
  int y_vel_;

  // Paddle's collision box
  SDL_Rect collider_;
};

#endif