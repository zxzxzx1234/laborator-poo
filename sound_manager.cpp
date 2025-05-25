#include "sound_manager.h"
#include <iostream>

SoundManager::SoundManager() {
    if (!m_hit_buffer.loadFromFile("assets/hit.wav")) {
        std::cerr << "Failed to load hit.wav\n";
    }
    if (!m_stand_buffer.loadFromFile("assets/stand.wav")) {
        std::cerr << "Failed to load stand.wav\n";
    }
    if (!m_win_buffer.loadFromFile("assets/win.wav")) {
        std::cerr << "Failed to load win.wav\n";
    }
    if (!m_lose_buffer.loadFromFile("assets/lose.wav")) {
        std::cerr << "Failed to load lose.wav\n";
    }

    m_hit_sound.setBuffer(m_hit_buffer);
    m_stand_sound.setBuffer(m_stand_buffer);
    m_win_sound.setBuffer(m_win_buffer);
    m_lose_sound.setBuffer(m_lose_buffer);

    if (!m_background_music.openFromFile("assets/background.ogg")) {
        std::cerr << "Failed to load background.ogg\n";
    }
    else {
        m_background_music.setLoop(true);
        m_background_music.setVolume(40);
    }
}

SoundManager::~SoundManager() {
    StopBackground();
}

void SoundManager::PlayHit() {
    m_hit_sound.play();
}

void SoundManager::PlayStand() {
    m_stand_sound.play();
}

void SoundManager::PlayWin() {
    m_win_sound.play();
}

void SoundManager::PlayLose() {
    m_lose_sound.play();
}

void SoundManager::PlayBackground() {
    m_background_music.play();
}

void SoundManager::StopBackground() {
    m_background_music.stop();
}
void SoundManager::SetVolume(float volume)
{
    m_hit_sound.setVolume(volume);
    m_stand_sound.setVolume(volume);
    m_win_sound.setVolume(volume);
    m_lose_sound.setVolume(volume);
    m_background_music.setVolume(volume);
}
