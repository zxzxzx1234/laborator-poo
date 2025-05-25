#include "volume_slider.h"
#include <iostream>
#include <algorithm>
VolumeSlider::VolumeSlider()
{
    m_volume = 100.0f;
    m_dragging = false;

    m_bar.setSize({ 120.f, 8.f });
    m_bar.setPosition(20.f, 620.f);
    m_bar.setFillColor(sf::Color::White);

    m_knob.setRadius(10.f);
    m_knob.setFillColor(sf::Color::Yellow);
    m_knob.setOrigin(0.f, 0.f);
    float bar_x = m_bar.getPosition().x;
    float bar_width = m_bar.getSize().x;
    float knob_x = bar_x + (m_volume / 100.f) * bar_width;
    float knob_y = m_bar.getPosition().y - m_knob.getRadius() + m_bar.getSize().y / 2.f;

    m_knob.setPosition(knob_x, knob_y);


    m_font.loadFromFile("assets/arial.ttf");
    m_label.setFont(m_font);
    m_label.setCharacterSize(16);
    m_label.setFillColor(sf::Color::White);
    m_label.setPosition(20.f, 600.f);
    m_label.setString("Volume: 100");
}

void VolumeSlider::HandleEvent(sf::RenderWindow& window, sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouse = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });


        float dx = mouse.x - m_knob.getPosition().x - m_knob.getRadius();
        float dy = mouse.y - m_knob.getPosition().y - m_knob.getRadius();
        float dist_squared = dx * dx + dy * dy;
        float radius = m_knob.getRadius();

        if (dist_squared <= radius * radius) {
            m_dragging = true;
        }

        else if (m_bar.getGlobalBounds().contains(mouse)) {
            m_dragging = true;

            float x = mouse.x;
            float left = m_bar.getPosition().x;
            float right = left + m_bar.getSize().x;

            if (x < left) x = left;
            if (x > right) x = right;

            m_volume = ((x - left) / m_bar.getSize().x) * 100.f;
            float knob_y = m_bar.getPosition().y - m_knob.getRadius() + m_bar.getSize().y / 2.f;
            m_knob.setPosition(x, knob_y);

            m_label.setString("Volume: " + std::to_string(static_cast<int>(m_volume)));
        }
    }


    if (event.type == sf::Event::MouseButtonReleased) {
        m_dragging = false;
    }

    if (event.type == sf::Event::MouseMoved && m_dragging) {
        float x = static_cast<float>(event.mouseMove.x);
        float left = m_bar.getPosition().x;
        float right = left + m_bar.getSize().x;

        if (x < left) x = left;
        if (x > right) x = right;
        m_volume = ((x - left) / m_bar.getSize().x) * 100.f;
        m_knob.setPosition(x, m_bar.getPosition().y - 6.f);

        m_label.setString("Volume: " + std::to_string(static_cast<int>(m_volume)));
    }
}

void VolumeSlider::DrawTo(sf::RenderWindow& window)
{
    window.draw(m_bar);
    window.draw(m_knob);
    window.draw(m_label);
}

float VolumeSlider::GetVolume() const
{
    return m_volume;
}

void VolumeSlider::SetVolume(float vol)
{
    if (vol < 0.f) vol = 0.f;
    if (vol > 100.f) vol = 100.f;
    m_volume = vol;

    float x = m_bar.getPosition().x + (vol / 100.f) * m_bar.getSize().x;
    float knob_y = m_bar.getPosition().y - m_knob.getRadius() + m_bar.getSize().y / 2.f;
    m_knob.setPosition(x, knob_y);

    m_label.setString("Volume: " + std::to_string(static_cast<int>(m_volume)));
}

