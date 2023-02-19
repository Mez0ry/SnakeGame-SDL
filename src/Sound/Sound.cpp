#include "Sound.hpp"

Sound::Sound(const char *path, SoundType type /*= SoundType::SOUND_EFFECT*/) noexcept : m_IsAvailable(true), m_RepeatAmount(1), m_pMusic(nullptr), m_pSoundEffect(nullptr) {
  set_Type(type);
  LoadSound(path);
}

Sound::~Sound() noexcept { DestroySound(); }

void Sound::LoadSound(const char *path) {
  switch (m_SoundType) {
  case SoundType::MUSIC: {
    m_pMusic = Mix_LoadMUS(path);
    break;
  }

  case SoundType::SOUND_EFFECT: {
    m_pSoundEffect = Mix_LoadWAV(path);
    break;
  }
  } //! switch
}

void Sound::DestroySound() {
  if (m_pMusic != nullptr) {
    Mix_FreeMusic(m_pMusic);
  }
  if (m_pSoundEffect != nullptr) {
    Mix_FreeChunk(m_pSoundEffect);
  }
}

void Sound::set_Type(SoundType type) { this->m_SoundType = type; }
void Sound::set_RepeatAmount(int repeat_amount) {
  this->m_RepeatAmount = repeat_amount;
}

bool Sound::PlaySound() {
  switch (m_SoundType) {
  case SoundType::MUSIC: {
    if (Mix_PlayMusic(m_pMusic, m_RepeatAmount) < 0) {
       std::cerr << "Failed to play music" << '\n';
    }
    break;
  }

  case SoundType::SOUND_EFFECT: {
    if(Mix_PlayChannel(-1, m_pSoundEffect, m_RepeatAmount) < 0){
      std::cerr << "Failed to play sound effect" << '\n';
      return false;
    }
    break;
  }
  } //! switch
  return false;
}