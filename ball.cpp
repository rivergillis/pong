#include "ball.h"

#include "constants.h"
#include "collision.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <random>

Ball::Ball() : rng_((std::random_device())()) {
  ResetBall();
}

void Ball::ResetBall() {
  //Initialize the offsets
  x_pos_ = (constants::SCREEN_WIDTH - BALL_WIDTH) / 2;
  y_pos_ = (constants::SCREEN_HEIGHT - BALL_HEIGHT) / 2;;

  //Set collision box dimension
  collider_.w = BALL_WIDTH;
  collider_.h = BALL_HEIGHT;

  // up to 30% of ball's initial velocity can be vertical
  std::uniform_int_distribution<int> uni(1, BALL_VEL / 3);
  y_vel_ = uni(rng_);

  // rest goes to horizontal velocity
  x_vel_ = BALL_VEL - y_vel_;

  // determine what side to send the ball towards
  std::uniform_int_distribution<int> coin_flipper(0,1);
  auto coin_side = coin_flipper(rng_);

  if (coin_side == 0) {
    x_vel_ *= -1;
  }

  coin_side = coin_flipper(rng_);

  if (coin_side == 0) {
    y_vel_ *= -1;
  }

  printf("Reset ball with xvel: %d, yvel: %d\n", x_vel_, y_vel_);  
}

void Ball::Score(bool player_scored, int* player_score, int* ai_score) {
  if (player_scored) {
    *player_score += 1;
  } else {
    *ai_score += 1;
  }
  ResetBall();
} 


void Ball::Move(double delta_time, std::vector<SDL_Rect*>& colliders, int* player_score, int* ai_score) {
  //Move the dot left or right
  int delta_vel_x = double(x_vel_ / (1000.0 / 60)) * delta_time;
  x_pos_ += delta_vel_x;
  collider_.x = x_pos_;

  // TODO: score on going to the ends of the X screen

  //If the ball went too far to the left, score for the AI
  if (x_pos_ < 0) {
    Score(false, player_score, ai_score);
    return;
  } else if (x_pos_ + BALL_WIDTH > constants::SCREEN_WIDTH) {
    // If the ball went too far to the right, score for the Player
    Score(true, player_score, ai_score);
    return;
  }

  //Move the dot up or down
  int delta_vel_y = double(y_vel_ / (1000.0 / 60)) * delta_time;
  y_pos_ += delta_vel_y;
  collider_.y = y_pos_;

  //If the dot collided or went too far up or down
  if ((y_pos_ < 0) || (y_pos_ + BALL_HEIGHT > constants::SCREEN_HEIGHT)) {
    //Move back
    y_pos_ -= delta_vel_y;
    collider_.y = y_pos_;
    y_vel_ *= -1;
  }

  for (auto& outside_collider : colliders) {
    std::pair<int, int> fixed_points = CheckCollisionWithPoints(collider_, *outside_collider, delta_vel_x, delta_vel_y);
    // no collision
    if (x_pos_ == fixed_points.first && y_pos_ == fixed_points.second) {
      continue;
    }

    if (fixed_points.first != x_pos_) {
      x_vel_ *= -1;
    } else {
      y_vel_ *= -1;
    }

    x_pos_ = fixed_points.first;
    y_pos_ = fixed_points.second;
    collider_.x = x_pos_;
    collider_.y = y_pos_;
    printf("Moved ball to x: %d, y: %d\n", x_pos_, y_pos_); 
  }

  // printf("x: %d, y: %d, \ncollider x: %d, collider y: %d", x_pos_, y_pos_, collider_.x, collider_.y);
}

void Ball::Render(Texture* texture) {
  //Show the dot
  texture->Render(x_pos_, y_pos_);
}