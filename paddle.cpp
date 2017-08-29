#include "paddle.h"

#include "constants.h"

Paddle::Paddle() {
  // Set initial position
  x_pos_ = 0;
  y_pos_ = (constants::SCREEN_HEIGHT - PADDLE_HEIGHT) / 2;

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

void Paddle::Render(Texture* texture) {
  texture->Render(x_pos_, y_pos_);
}