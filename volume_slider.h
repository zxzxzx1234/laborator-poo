#ifndef VOLUME_SLIDER_H
#define VOLUME_SLIDER_H

#include <SFML/Graphics.hpp>

class VolumeSlider {
private:
    sf::RectangleShape m_bar;
    sf::CircleShape m_knob;
    sf::Font m_font;
    sf::Text m_label;

    float m_volume; // 0.0f to 100.0f
    bool m_dragging;

public:
    VolumeSlider();
    void HandleEvent(sf::RenderWindow& window, sf::Event& event);
    void DrawTo(sf::RenderWindow& window);
    float GetVolume() const;
    void SetVolume(float vol); // optional din cod
};

#endif
