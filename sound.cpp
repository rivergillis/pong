#include "sound.h"

Sound::Sound() {
  sound_chunk_ = nullptr;
}

Sound::~Sound() {
  Free();
}

void Sound::Free() {
  Mix_FreeChunk(sound_chunk_);
  sound_chunk_ = nullptr;
}