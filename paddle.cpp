#include "paddle.h"

#include "constants.h"

Paddle::Paddle(bool player) {
  // Set initial position
  if (player) {
    x_pos_ = 0;    
  } else {
    x_pos_ = constants::SCREEN_WIDTH - PADDLE_WIDTH;
  }

  y_pos_ = (constants::SCREEN_HEIGHT - PADDLE_HEIGHT) / 2;

  collider_.x = x_pos_;
  collider_.y = y_pos_;
  collider_.w = PADDLE_WIDTH;
  collider_.h = PADDLE_HEIGHT;

  y_vel_ = 0;
}

void Paddle::HandleEvent(SDL_Event& e) {
  // key pressed
  if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    switch(e.key.keysym.sym) {
      case SDLK_UP: y_vel_ -= PADDLE_VEL; break;
      case SDLK_DOWN: y_vel_ += PADDLE_VEL; break;
    }
    // key released
  } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
    switch(e.key.keysym.sym) {
      case SDLK_UP: y_vel_ += PADDLE_VEL; break;
      case SDLK_DOWN: y_vel_ -= PADDLE_VEL; break;
    }
  }
}

void Paddle::Move(double delta_time) {
  int delta_vel_y = double(y_vel_ / (1000.0 / 60)) * delta_time;
  y_pos_ += delta_vel_y;

  if (y_pos_ < 0) {
    y_pos_ = 0;
  } else if (y_pos_ + PADDLE_HEIGHT > constants::SCREEN_HEIGHT) {
    y_pos_ = constants::SCREEN_HEIGHT - PADDLE_HEIGHT;
  }

  collider_.y = y_pos_;  
}

void Paddle::Autopilot(SDL_Rect* ball) {
  // move towards the ball
  if (ball->y > y_pos_) {
    y_vel_ = PADDLE_VEL * 0.35;
  } else if (ball->y < y_pos_) {
    y_vel_ = PADDLE_VEL * -0.35;
  } else {
    y_vel_ = 0;
  }
}

void Paddle::ResetVel() {
  y_vel_ = 0;
}

void Paddle::Render(Texture* texture) {
  texture->Render(x_pos_, y_pos_);
}