#ifndef SOUND_PLAYER_H_
#define SOUND_PLAYER_H_

#include "sound.h"

#include <vector>
#include <SDL2/SDL_mixer.h>

enum class SoundName {
  BALL_HIT = 0,
  BALL_SCORE,
  TOTAL_NUM_SOUNDS
};

class SoundPlayer {
 public:
  SoundPlayer();
  ~SoundPlayer();

  void FreeAll();

  void LoadAllSounds();

  void PlaySound(SoundName name, int channel = -1, int loops = 0);
 private:
  std::vector<Sound> sounds_;
};

#endif