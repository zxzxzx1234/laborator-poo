#include "input_box.h"

// Default constructor
InputBox::InputBox() {}

// Constructor with parameters
InputBox::InputBox(int font_size, sf::Vector2f box_size, sf::Vector2f position,
    sf::Color text_color, sf::Color box_color, bool selected)
{
    m_is_selected = false;
    m_has_limit = false;
    m_limit = 0;

    m_rect.setSize(box_size);
    m_rect.setFillColor(box_color);
    m_rect.setPosition(position);

    m_textbox.setCharacterSize(font_size);
    m_textbox.setFillColor(text_color);
    m_textbox.setPosition(position);

    m_is_selected = selected;
    m_textbox.setString(selected ? "|" : "");
}

// Set the font for the text
void InputBox::SetFont(sf::Font& font) {
    m_textbox.setFont(font);
}

// Set the position of the textbox
void InputBox::SetPosition(sf::Vector2f point) {
    m_textbox.setPosition(point);
    m_rect.setPosition(point);
}

// Enable or disable character limit
void InputBox::SetLimit(bool enabled) {
    m_has_limit = enabled;
}

// Set character limit and enable it
void InputBox::SetLimit(bool enabled, int limit) {
    m_has_limit = enabled;
    m_limit = limit - 1;
}

// Select or deselect the input box
void InputBox::SetSelected(bool selected) {
    m_is_selected = selected;

    if (!selected) {
        m_textbox.setString(m_text.str());
    }
}

// Get current user input text
std::string InputBox::GetText() {
    return m_text.str();
}

// Draw input box (rectangle and text)
void InputBox::DrawTo(sf::RenderWindow& window) {
    window.draw(m_rect);
    window.draw(m_textbox);
}

// Handle typed characters (called from event loop)
void InputBox::TypedOn(sf::Event& input) {
    if (m_is_selected) {
        int char_typed = input.text.unicode;

        if (char_typed < 128) {
            if (m_has_limit) {
                if (m_text.str().length() <= m_limit) {
                    InputLogic(char_typed);
                }
                else if (m_text.str().length() > m_limit && char_typed == DELETE_KEY) {
                    DeleteLastChar();
                }
            }
            else {
                InputLogic(char_typed);
            }
        }
    }
}

// Delete the last character from the buffer
void InputBox::DeleteLastChar() {
    std::string current = m_text.str();
    std::string new_text = current.substr(0, current.length() - 1);
    m_text.str("");
    m_text << new_text;
    m_textbox.setString(m_text.str() + "|");
}

// Process a typed character
void InputBox::InputLogic(int char_typed) {
    if (char_typed != DELETE_KEY && char_typed != ENTER_KEY && char_typed != ESCAPE_KEY) {
        m_text << static_cast<char>(char_typed);
    }
    else if (char_typed == DELETE_KEY && m_text.str().length() > 0) {
        DeleteLastChar();
    }

    m_textbox.setString(m_text.str() + "|");
}

// Update method for selecting/deselecting input box
void InputBox::UpdateInputBox()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
        SetSelected(true);
        return;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        SetSelected(false);
        return;
    }
}
