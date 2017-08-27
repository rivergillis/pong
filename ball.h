#ifndef BALL_H_
#define BALL_H_

#include <vector>

#include "texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

//The ball that will move around on the screen
class Ball
{
public:
  //The dimensions of the ball
  static const int DOT_WIDTH = 30;
  static const int DOT_HEIGHT = 30;

  //Maximum axis velocity of the ball
  static const int DOT_VEL = 10;

  //Initializes the variables
  Ball();

  //Takes key presses and adjusts the ball's velocity
  void handleEvent(SDL_Event& e);

  //Moves the ball and checks collision
  void move(double deltaTime, std::vector<SDL_Rect>& colliders);

  //Shows the ball on the screen
  void render(Texture* texture);

private:
  //The X and Y offsets of the ball
  int posX_, posY_;

  //The velocity of the ball
  int velX_, velY_;

  //Ball's collision box
  SDL_Rect collider_;
};

#endif