#ifndef SOUND_H_
#define SOUND_H_

#include <SDL2/SDL_mixer.h>

class Sound {
 public:
  Sound();
  ~Sound();

  void Free();

  void SetSound(Mix_Chunk* sound) {
    sound_chunk_ = sound;
  }

  Mix_Chunk* GetSound() { return sound_chunk_; }
 private:
  Mix_Chunk* sound_chunk_;
};

#endif