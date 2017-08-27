#include "ball.h"

#include "constants.h"
#include "collision.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

Ball::Ball(SDL_Renderer* renderer) : ballTexture_(renderer)
{
  //Initialize the offsets
  posX_ = 0;
  posY_ = 0;

  //Set collision box dimension
  collider_.w = DOT_WIDTH;
  collider_.h = DOT_HEIGHT;

  //Initialize the velocity
  velX_ = 0;
  velY_ = 0;
}

void Ball::handleEvent(SDL_Event& e)
{
  //If a key was pressed
  if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
  {
    //Adjust the velocity
    switch (e.key.keysym.sym)
    {
    case SDLK_UP:
      velY_ -= DOT_VEL;
      break;
    case SDLK_DOWN:
      velY_ += DOT_VEL;
      break;
    case SDLK_LEFT:
      velX_ -= DOT_VEL;
      break;
    case SDLK_RIGHT:
      velX_ += DOT_VEL;
      break;
    }
  }
  //If a key was released
  else if (e.type == SDL_KEYUP && e.key.repeat == 0)
  {
    //Adjust the velocity
    switch (e.key.keysym.sym)
    {
    case SDLK_UP:
      velY_ += DOT_VEL;
      break;
    case SDLK_DOWN:
      velY_ -= DOT_VEL;
      break;
    case SDLK_LEFT:
      velX_ += DOT_VEL;
      break;
    case SDLK_RIGHT:
      velX_ -= DOT_VEL;
      break;
    }
  }
}

void Ball::move(SDL_Rect& wall)
{
  //Move the dot left or right
  posX_ += velX_;
  collider_.x = posX_;

  //If the dot collided or went too far to the left or right
  if ((posX_ < 0) || (posX_ + DOT_WIDTH > constants::SCREEN_WIDTH) || checkCollision(collider_, wall))
  {
    //Move back
    posX_ -= velX_;
    collider_.x = posX_;
  }

  //Move the dot up or down
  posY_ += velY_;
  collider_.y = posY_;

  //If the dot collided or went too far up or down
  if ((posY_ < 0) || (posY_ + DOT_HEIGHT > constants::SCREEN_HEIGHT) || checkCollision(collider_, wall))
  {
    //Move back
    posY_ -= velY_;
    collider_.y = posY_;
  }
}

void Ball::render()
{
  //Show the dot
  ballTexture_.render(posX_, posY_);
}