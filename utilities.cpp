#include "utilities.h"

bool ColorsEqual(SDL_Color a, SDL_Color b) {
  if (a.r != b.r) {
    return false;
  } else if (a.g != b.g) {
    return false;
  } else if (a.b != b.b) {
    return false;
  } else if (a.a != b.a) {
    return false;
  } else {
    return true;
  }
}