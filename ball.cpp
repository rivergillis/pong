#include "ball.h"

#include "constants.h"
#include "collision.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

Ball::Ball()
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

void Ball::move(double deltaTime, std::vector<SDL_Rect>& colliders)
{
  //Move the dot left or right
  // Perfect delta is 16.6666...
  int delta_vel_x = double(velX_ / 16.667) * deltaTime;
  posX_ += delta_vel_x;
  collider_.x = posX_;

  // TODO: score on going to the ends of the X screen

  //If the dot collided or went too far to the left or right
  if ((posX_ < 0) || (posX_ + DOT_WIDTH > constants::SCREEN_WIDTH))
  {
    //Move back
    posX_ -= delta_vel_x;
    collider_.x = posX_;
  } else {
    // check new x collisions
    for (const auto& outside_collider : colliders) {
      // make sure to only check if there's an actual collision
      if (!checkCollision(collider_, outside_collider)) {
        break;
      }

      int collision = checkCollisionX(collider_, outside_collider);
      if (collision == 1) {
        // ball touches the right side coming from the right
        printf("Ball has touched the right side of the wall!\n");
        posX_ = outside_collider.x + outside_collider.w;
        collider_.x = posX_;
      } else if (collision == -1) {
        // ball touches the left side coming from the left
        printf("Ball has touched the left side of the wall!\n");
        posX_ = outside_collider.x - collider_.w;
        collider_.x = posX_;
      }
    }
  }

  //Move the dot up or down
  int delta_vel_y = double(velY_ / 16.667) * deltaTime;
  posY_ += delta_vel_y;
  collider_.y = posY_;

  //If the dot collided or went too far up or down
  if ((posY_ < 0) || (posY_ + DOT_HEIGHT > constants::SCREEN_HEIGHT))
  {
    //Move back
    posY_ -= delta_vel_y;
    collider_.y = posY_;
  } else {
    // check new y collisions
    for (const auto& outside_collider : colliders) {
      // make sure to only check if there's an actual collision
      if (!checkCollision(collider_, outside_collider)) {
        break;
      }

      int collision = checkCollisionY(collider_, outside_collider);
      if (collision == 1) {
        // ball touches the bottom side 
        printf("Ball has touched the bottom side of the wall!\n");
        posY_ = outside_collider.y + outside_collider.h + 1;
        collider_.y = posY_;
      } else if (collision == -1) {
        // ball touches the top side
        printf("Ball has touched the top side of the wall!\n");
        posY_ = outside_collider.y - collider_.h;
        collider_.y = posY_;
      }
    }
  }
  printf("x: %d, y: %d, \ncollider x: %d, collider y: %d", posX_, posY_, collider_.x, collider_.y);
}

void Ball::render(Texture* texture)
{
  //Show the dot
  texture->render(posX_, posY_);
}