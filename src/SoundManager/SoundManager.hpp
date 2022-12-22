#ifndef SnakeGame_SOUND_MANAGER_HPP
#define SnakeGame_SOUND_MANAGER_HPP
#include "SDL2/SDL_audio.h"
#include "SDL2/SDL_mixer.h"

enum class SoundType
{
    MUSIC,
    SOUND_EFFECT
};

class SoundManager
{
private:
    SoundType m_SoundType;
    int m_RepeatAmount;

public:
    SoundManager() : m_SoundType(SoundType::SOUND_EFFECT), m_RepeatAmount(1) {}
    SoundManager(const char *path, SoundType type = SoundType::SOUND_EFFECT) noexcept;
    ~SoundManager() noexcept;

    void LoadSound(const char *path);
    void set_Type(SoundType type);
    void set_RepeatAmount(int repeat_amount);
    int get_RepeatAmount() const noexcept { return m_RepeatAmount; }

public:
    bool PlaySound();

private:
    Mix_Music *m_pMusic;
    Mix_Chunk *m_pSoundEffect;
};
#endif //! SnakeGame_SOUND_MANAGER_HPP