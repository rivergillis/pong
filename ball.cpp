#include "ball.h"

#include "constants.h"
#include "collision.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

Ball::Ball() {
  //Initialize the offsets
  x_pos_ = 0;
  y_pos_ = 0;

  //Set collision box dimension
  collider_.w = BALL_WIDTH;
  collider_.h = BALL_HEIGHT;

  //Initialize the velocity
  x_vel_ = 0;
  y_vel_ = 0;
}

void Ball::HandleEvent(SDL_Event& e) {
  //If a key was pressed
  if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    //Adjust the velocity
    switch (e.key.keysym.sym) {
    case SDLK_UP:
      y_vel_ -= BALL_VEL;
      break;
    case SDLK_DOWN:
      y_vel_ += BALL_VEL;
      break;
    case SDLK_LEFT:
      x_vel_ -= BALL_VEL;
      break;
    case SDLK_RIGHT:
      x_vel_ += BALL_VEL;
      break;
    }
  } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
    //If a key was released
    //Adjust the velocity
    switch (e.key.keysym.sym) {
    case SDLK_UP:
      y_vel_ += BALL_VEL;
      break;
    case SDLK_DOWN:
      y_vel_ -= BALL_VEL;
      break;
    case SDLK_LEFT:
      x_vel_ += BALL_VEL;
      break;
    case SDLK_RIGHT:
      x_vel_ -= BALL_VEL;
      break;
    }
  }
}

void Ball::Move(double delta_time, std::vector<SDL_Rect>& colliders)
{
  //Move the dot left or right
  // Perfect delta is 16.6666...
  int delta_vel_x = double(x_vel_ / 16.667) * delta_time;
  x_pos_ += delta_vel_x;
  collider_.x = x_pos_;

  // TODO: score on going to the ends of the X screen

  //If the dot collided or went too far to the left or right
  if ((x_pos_ < 0) || (x_pos_ + BALL_WIDTH > constants::SCREEN_WIDTH)) {
    //Move back
    x_pos_ -= delta_vel_x;
    collider_.x = x_pos_;
  }

  //Move the dot up or down
  int delta_vel_y = double(y_vel_ / 16.667) * delta_time;
  y_pos_ += delta_vel_y;
  collider_.y = y_pos_;

  //If the dot collided or went too far up or down
  if ((y_pos_ < 0) || (y_pos_ + BALL_HEIGHT > constants::SCREEN_HEIGHT)) {
    //Move back
    y_pos_ -= delta_vel_y;
    collider_.y = y_pos_;
  }

  for (auto& outside_collider : colliders) {
    std::pair<int, int> fixed_points = CheckCollisionWithPoints(collider_, outside_collider, delta_vel_x, delta_vel_y);
    x_pos_ = fixed_points.first;
    y_pos_ = fixed_points.second;
    collider_.x = x_pos_;
    collider_.y = y_pos_;
    printf("Moved ball to x: %d, y: %d\n", x_pos_, y_pos_); 
  }

  printf("x: %d, y: %d, \ncollider x: %d, collider y: %d", x_pos_, y_pos_, collider_.x, collider_.y);
}

void Ball::Render(Texture* texture) {
  //Show the dot
  texture->Render(x_pos_, y_pos_);
}