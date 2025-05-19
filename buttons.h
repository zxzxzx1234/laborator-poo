#ifndef BUTTONS_H
#define BUTTONS_H

#include <vector>
#include "config.h"
#include "button.h"
#include <SFML/Graphics.hpp>

class Buttons
{
private:
    std::vector<Button> m_buttons; // All buttons used in the interface

    // Initialize button list
    void _InitButtons();

public:
    // Constructor
    Buttons();

    // Destructor
    ~Buttons();

    // Update button hover and click logic
    int UpdateButtons(sf::RenderWindow& window, sf::Event& event);

    // Draw all buttons
    void DrawButtons(sf::RenderWindow& window);
};

#endif // BUTTONS_H
