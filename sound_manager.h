#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SFML/Audio.hpp>
#include <string>

class SoundManager {
private:
    sf::SoundBuffer m_hit_buffer;
    sf::SoundBuffer m_stand_buffer;
    sf::SoundBuffer m_win_buffer;
    sf::SoundBuffer m_lose_buffer;

    sf::Sound m_hit_sound;
    sf::Sound m_stand_sound;
    sf::Sound m_win_sound;
    sf::Sound m_lose_sound;

    sf::Music m_background_music;

public:
    SoundManager();
    ~SoundManager();

    void PlayHit();
    void PlayStand();
    void PlayWin();
    void PlayLose();
    void PlayBackground();
    void StopBackground();
    void SetVolume(float volume);

};

#endif
