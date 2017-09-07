#include "sound_player.h"

SoundPlayer::SoundPlayer() {
  sounds_.reserve(static_cast<int>(SoundName::TOTAL_NUM_SOUNDS));
  for (int i = 0; i < static_cast<int>(SoundName::TOTAL_NUM_SOUNDS); ++i) {
    sounds_.emplace_back();
  }
}

SoundPlayer::~SoundPlayer() {
  FreeAll();
}

void SoundPlayer::FreeAll() {
  for (auto& sound : sounds_) {
    sound.Free();
  }
}


void SoundPlayer::LoadAllSounds() {
  for (int i = 0; i < static_cast<int>(SoundName::TOTAL_NUM_SOUNDS); ++i) {
    switch(static_cast<SoundName>(i)) {
      case SoundName::BALL_HIT:
        sounds_[i].SetSound(Mix_LoadWAV("assets/sfx/blip-fs5.wav"));
      break;
      case SoundName::BALL_SCORE:
        sounds_[i].SetSound(Mix_LoadWAV("assets/sfx/blip-fs4.wav"));
      break;
      default: break;
    }
  }
}

void SoundPlayer::PlaySound(SoundName name, int channel, int loops) {
  if (name == SoundName::TOTAL_NUM_SOUNDS) { return; }
  Mix_PlayChannel(channel, sounds_[static_cast<int>(name)].GetSound(), loops);
}