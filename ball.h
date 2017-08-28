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


//The ball that will move around on the screen
class Ball {
 public:
  //The dimensions of the ball
  static const int BALL_WIDTH = 30;
  static const int BALL_HEIGHT = 30;

  //Maximum axis velocity of the ball
  static const int BALL_VEL = 10;

  //Initializes the variables
  Ball();

  //Moves the ball and checks collision
  void Move(double delta_time, std::vector<SDL_Rect>& colliders);

  //Shows the ball on the screen
  void Render(Texture* texture);

private:
  //The X and Y offsets of the ball
  int x_pos_, y_pos_;

  //The velocity of the ball
  int x_vel_, y_vel_;

  //Ball's collision box
  SDL_Rect collider_;

  // random generator
  std::mt19937 rng_;
};

#endif