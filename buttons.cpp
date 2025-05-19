#include "buttons.h"

Buttons::Buttons() {
    m_buttons = std::vector<Button>();
    _InitButtons();
}

Buttons::~Buttons() {}

void Buttons::_InitButtons() {
    Button hitBtn("HIT", { 150, 50 }, 25, sf::Color::White, sf::Color::Red);
    hitBtn.SetFont(config.GetFont(ARIAL));
    hitBtn.SetPosition({ 700, 300 });
    m_buttons.push_back(hitBtn);

    Button standBtn("STAND", { 150, 50 }, 25, sf::Color::White, sf::Color::Red);
    standBtn.SetFont(config.GetFont(ARIAL));
    standBtn.SetPosition({ 900, 300 });
    m_buttons.push_back(standBtn);

    Button anotherGameBtn("Another Game", { 200, 50 }, 25, sf::Color::White, sf::Color::Red);
    anotherGameBtn.SetFont(config.GetFont(ARIAL));
    anotherGameBtn.SetPosition({ 450, 300 });
    m_buttons.push_back(anotherGameBtn);
}

int Buttons::UpdateButtons(sf::RenderWindow& window, sf::Event& event) {
    for (int i = 0; i < m_buttons.size(); ++i) {
        if (m_buttons[i].IsMouseOver(window)) {
            m_buttons[i].SetBackColor(sf::Color::Yellow);
        }
        else {
            m_buttons[i].SetBackColor(sf::Color::White);
        }
    }

    for (int i = 0; i < m_buttons.size(); ++i) {
        bool clicked = m_buttons[i].IsMouseOver(window) && event.type == sf::Event::MouseButtonPressed;
        if (clicked && i == HIT) return HIT;
        if (clicked && i == STAND) return STAND;
        if (clicked && i == ANOTHER_GAME) return ANOTHER_GAME;
    }

    return INVALID;
}

void Buttons::DrawButtons(sf::RenderWindow& window) {
    for (int i = 0; i < m_buttons.size(); ++i) {
        m_buttons[i].SetFont(config.GetFont(ARIAL));
        m_buttons[i].DrawTo(window);
    }
}
