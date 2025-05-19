#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
public:
    Button();
    Button(std::string text, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor);

    // Set the button text
    void SetText(std::string text);

    // Set button size
    void SetSize(sf::Vector2f size);

    // Set text character size
    void SetCharSize(int size);

    // Set font for the text
    void SetFont(sf::Font& font);

    // Set background color
    void SetBackColor(sf::Color color);

    // Set text color
    void SetTextColor(sf::Color color);

    // Set button position and center the text
    void SetPosition(sf::Vector2f position);

    // Draw the button to the window
    void DrawTo(sf::RenderWindow& window);

    // Check if mouse is over the button
    bool IsMouseOver(sf::RenderWindow& window);

private:
    sf::RectangleShape m_button;  // Button shape
    sf::Text m_text;              // Button label

    float m_btn_width;            // Button width
    float m_btn_height;           // Button height
};

#endif // BUTTON_H
