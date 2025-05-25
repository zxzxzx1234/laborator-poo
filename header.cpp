#include "header.h"

// Default constructor
Header::Header() {}

// Parameterized constructor
Header::Header(std::string header_text, sf::Vector2f header_size, sf::Vector2f header_pos,
    int char_size, sf::Color bg_color, sf::Color text_color)
{
    m_header.setSize(header_size);
    m_header.setFillColor(bg_color);
    m_header.setPosition(header_pos);

    m_text.setPosition(header_pos);
    m_text.setString(header_text);
    m_text.setCharacterSize(char_size);
    m_text.setFillColor(text_color);
}

// Destructor
Header::~Header() {}

// Set the font used for the text
void Header::SetFont(sf::Font& font)
{
    m_text.setFont(font);
}

// Draw header background and text
void Header::DrawTo(sf::RenderWindow& window)
{
    
    window.draw(m_text);
}

void Header::DrawTo(sf::RenderWindow& window, sf::Color color)
{
    sf::Text temp = m_text;
    temp.setFillColor(color);
    window.draw(temp);
}

// Update the header's text string
void Header::SetHeader(string text)
{
    m_text.setString(text);
}
