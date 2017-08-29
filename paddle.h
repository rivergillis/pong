#ifndef PADDLE_H_
#define PADDLE_H_

#include <SDL2/SDL.h>

class Paddle {
 public:
  // The dimensions of the paddle
  static const int PADDLE_WIDTH = 30;
  static const int PADDLE_HEIGHT = 100;

  // The maximum vertical velocity of the paddle
  static const int PADDLE_VEL = 10;

  Paddle();
  
 private:
};

#endif