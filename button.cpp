#include "button.h"

Button::Button() {}

Button::Button(std::string text, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor) {
    m_button.setSize(size);
    m_button.setFillColor(bgColor);

    m_btn_width = size.x;
    m_btn_height = size.y;

    m_text.setString(text);
    m_text.setCharacterSize(charSize);
    m_text.setFillColor(textColor);
}

void Button::SetText(std::string text) {
    m_text.setString(text);
}

void Button::SetSize(sf::Vector2f size) {
    m_button.setSize(size);
}

void Button::SetCharSize(int size) {
    m_text.setCharacterSize(size);
}

void Button::SetFont(sf::Font& font) {
    m_text.setFont(font);
}

void Button::SetBackColor(sf::Color color) {
    m_button.setFillColor(color);
}

void Button::SetTextColor(sf::Color color) {
    m_text.setFillColor(color);
}

void Button::SetPosition(sf::Vector2f position) {
    m_button.setPosition(position);

    float div = 2.0 + m_btn_height / m_btn_width;
    float xPos = (position.x + m_btn_width / div) - (m_text.getLocalBounds().width / 2);
    float yPos = (position.y + m_btn_height / div) - (m_text.getLocalBounds().height / 2);

    m_text.setPosition(xPos, yPos);
}

void Button::DrawTo(sf::RenderWindow& window) {
    window.draw(m_button);
    window.draw(m_text);
}

bool Button::IsMouseOver(sf::RenderWindow& window) {
    sf::Vector2i mouseCoords({ sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y });
    sf::Vector2f realCoords = window.mapPixelToCoords(mouseCoords);

    float mouseX = realCoords.x;
    float mouseY = realCoords.y;

    float btnX = m_button.getPosition().x;
    float btnY = m_button.getPosition().y;
    float btnWidth = m_button.getGlobalBounds().width;
    float btnHeight = m_button.getGlobalBounds().height;

    if (mouseX < btnX + btnWidth && mouseX > btnX &&
        mouseY < btnY + btnHeight && mouseY > btnY) {
        return true;
    }
    return false;
}
