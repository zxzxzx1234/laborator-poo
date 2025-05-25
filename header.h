#ifndef HEADER_H
#define HEADER_H

#include <SFML/Graphics.hpp>
using namespace std;

class Header
{
private:
    sf::RectangleShape m_header;  // Background rectangle
    sf::Text m_text;              // Text displayed on header

public:
    // Default constructor
    Header();

    // Custom constructor with parameters
    Header(std::string header_text, sf::Vector2f header_size, sf::Vector2f header_pos,
        int char_size, sf::Color bg_color, sf::Color text_color);

    // Destructor
    ~Header();

    // Returns the current header text
    string GetHeader() { return m_text.getString(); }

    // Sets the header text
    void SetHeader(string text);

    // Sets the font for the header text
    void SetFont(sf::Font& font);

    // Draws the header (rectangle + text) to the window
    void DrawTo(sf::RenderWindow& window);
    // Overload
    void DrawTo(sf::RenderWindow& window, sf::Color color);

};

#endif
