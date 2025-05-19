#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include <sstream>
#include <SFML/Graphics.hpp>
#include <iostream>

// Key code definitions
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class InputBox {
public:
    // Default constructor
    InputBox();

    // Constructor with parameters
    InputBox(int font_size, sf::Vector2f box_size, sf::Vector2f position,
        sf::Color text_color, sf::Color box_color, bool selected);

    // Set font used in the input box
    void SetFont(sf::Font& font);

    // Set the position of the input box
    void SetPosition(sf::Vector2f point);

    // Enable or disable character limit
    void SetLimit(bool enabled);

    // Enable character limit and set the limit value
    void SetLimit(bool enabled, int limit);

    // Set the input box selected state (focused or not)
    void SetSelected(bool selected);

    // Get the current string value from the input
    std::string GetText();

    // Returns the text object (for external use if needed)
    sf::Text& GetTextBox() { return m_textbox; }

    // Draws the input box to the render window
    void DrawTo(sf::RenderWindow& window);

    // Handles key typing events
    void TypedOn(sf::Event& input);

    // Optional update routine
    void UpdateInputBox();

private:
    sf::Text m_textbox;              // Visual text display
    std::ostringstream m_text;       // Underlying text buffer
    bool m_is_selected;              // Is input box selected
    bool m_has_limit;                // Limit character input
    int m_limit;                     // Max number of characters
    sf::RectangleShape m_rect;       // Background rectangle

    // Deletes last typed character
    void DeleteLastChar();

    // Handles logic for key input
    void InputLogic(int char_typed);
};

#endif
