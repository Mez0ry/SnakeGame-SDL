#ifndef SnakeGame_SOUND_MANAGER_HPP
#define SnakeGame_SOUND_MANAGER_HPP
#include "SDL2/SDL_audio.h"
#include "SDL2/SDL_mixer.h"
#include <iostream>

enum class SoundType
{
    MUSIC,
    SOUND_EFFECT
};

class Sound
{
private:
    SoundType m_SoundType;
    int m_RepeatAmount;
public:
    Sound() : m_SoundType(SoundType::SOUND_EFFECT), m_RepeatAmount(0), m_IsAvailable(true) {}
    Sound(const char *path, SoundType type = SoundType::SOUND_EFFECT) noexcept;
    ~Sound() noexcept;

    void LoadSound(const char *path);
    void DestroySound();
    void set_Type(SoundType type);
    void set_RepeatAmount(int repeat_amount);
    int get_RepeatAmount() const noexcept { return m_RepeatAmount; }
    
    void set_Availability(bool status){m_IsAvailable = status;}
    bool isAvailable() const {return m_IsAvailable;}
public:
    bool PlaySound();
private:
    bool m_IsAvailable;
    Mix_Music *m_pMusic;
    Mix_Chunk *m_pSoundEffect;
};
#endif //! SnakeGame_SOUND_MANAGER_HPP