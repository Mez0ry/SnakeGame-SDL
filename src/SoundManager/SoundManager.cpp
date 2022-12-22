#include "SoundManager.hpp"

SoundManager::SoundManager(const char *path, SoundType type /*= SoundType::SOUND_EFFECT*/) noexcept : m_RepeatAmount(1), m_pMusic(nullptr), m_pSoundEffect(nullptr) {
  set_Type(type);
  LoadSound(path);
}

SoundManager::~SoundManager() noexcept {
  if (m_pMusic != nullptr) {
    Mix_FreeMusic(m_pMusic);
  }
  if (m_pSoundEffect != nullptr) {
    Mix_FreeChunk(m_pSoundEffect);
  }
}

void SoundManager::LoadSound(const char *path) {
  switch (m_SoundType) {
    case SoundType::MUSIC: {
      m_pMusic = Mix_LoadMUS(path);
      break;
    }

    case SoundType::SOUND_EFFECT: {
      m_pSoundEffect = Mix_LoadWAV(path);
      break;
    }
  }  //! switch
}
void SoundManager::set_Type(SoundType type) { 
    this->m_SoundType = type; 
}
void SoundManager::set_RepeatAmount(int repeat_amount) {
  this->m_RepeatAmount = repeat_amount;
}

bool SoundManager::PlaySound() {
  switch (m_SoundType) {
    case SoundType::MUSIC: {
      if (Mix_PlayMusic(m_pMusic, m_RepeatAmount) == 0) {
        if (Mix_PlayMusic(m_pMusic, m_RepeatAmount) == -1) {
          return 1;
        }
      }
      break;
    }

    case SoundType::SOUND_EFFECT: {
      Mix_PlayChannel(-1, m_pSoundEffect, m_RepeatAmount);
      return 1;
      break;
    }
  }  //! switch
  return 0;
}