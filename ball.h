// ball.h
// Author: River Gillis
// 
// An abstraction of the Ball object in Pong.
// Contains the entire state of the Ball, contains the logic to move the ball.
// Also has the ability to render the ball to the screen.
//
// Usage:
//  Ball ball;
//  while (game_loop) {
//    ball.Move(delta, colliders, &player_score, &ai_score);
//    ball.Render(&ball_texture);
//  }

#ifndef BALL_H_
#define BALL_H_

#include <vector>

#include "texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <random>

// Declares the type of collision that occurred.
// Type determined by what the ball collides with.
// SCORE means it touched the horizontal screen edge.
enum class CollisionType {
  NONE = 0,
  WALL,
  PADDLE,
  SCORE
};

class Ball {
 public:
  // The dimensions of the ball
  static const int BALL_WIDTH = 30;
  static const int BALL_HEIGHT = 30;

  // Maximum total velocity of the ball
  static const int BALL_VEL = 10;

  Ball();

  SDL_Rect* GetCollider() { return &collider_; }

  // Moves the ball and checks collision against @colliders.
  // If scoring occurs, calls Score().
  // returns what type of collision occurred.
  CollisionType Move(double delta_time, std::vector<SDL_Rect*>& colliders, int* player_score, int* ai_score);

  // Renders the ball to the screen
  void Render(Texture* texture);

  void SetVelocityMultiplier(double mult) {
    vel_multiplier = mult;
  }

private:
  // Scores against @player_scored.
  // If player_scored is true, ++(*player_score)
  //  else: ++(*ai_score)
  void Score(bool player_scored, int* player_score, int* ai_score);

  // To be implemented: resets the position of the ball.
  void ResetBall();

  double vel_multiplier = 1;

  // The X and Y offsets of the ball
  int x_pos_, y_pos_;

  // The velocity of the ball
  int x_vel_, y_vel_;

  // Ball's collision box
  SDL_Rect collider_;

  // random generator
  std::mt19937 rng_;
};

#endif