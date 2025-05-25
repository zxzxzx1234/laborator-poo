#include "card.h"
#include "config.h"

// constructor without parameters
Card::Card() {}

// constructor with rank and suit parameters
Card::Card(string suit, int rank)
{
    this->m_rank = rank;
    this->m_suit = suit;
    this->m_card = sf::Sprite();  // initializing sprite
}

Card::~Card() {}

// returns a unique hash for a card
string Card::_GetCardHash()
{
    string hash = this->m_suit + to_string(this->m_rank);
    return hash;
}

// sets the position of the card sprite
void Card::SetCardPosition(sf::Vector2f pos)
{
    this->m_card.setPosition(pos);
}

// uses the texture from the configuration file
void Card::DrawTo(sf::RenderWindow& window)
{
    string hash = this->_GetCardHash();                         // gets the hash
    this->m_card.setTexture(config.GetTexture(hash));          // sets the texture
    window.draw(this->m_card);                                  // draws the sprite
}
void Card::SetColor(sf::Color color)
{
    m_card.setColor(color);
}
void Card::AnimateTo(sf::Vector2f target_pos)
{
    m_start_pos = m_card.getPosition();
    m_target_pos = target_pos;
    m_animation_progress = 0.f;
    m_animating = true;
}

bool Card::IsAnimating() const
{
    return m_animating;
}

void Card::UpdateAnimation()
{
    if (!m_animating) return;

    m_animation_progress += 0.05f; // viteza animatiei

    if (m_animation_progress >= 1.f)
    {
        m_card.setPosition(m_target_pos);
        m_animating = false;
    }
    else
    {
        sf::Vector2f current_pos = m_start_pos + (m_target_pos - m_start_pos) * m_animation_progress;
        m_card.setPosition(current_pos);
    }
}
void Card::StartFlip()
{
    m_flipping = true;
    m_flip_progress = 0.f;
    m_flip_finished = false;
}

bool Card::IsFlipping() const
{
    return m_flipping;
}

void Card::UpdateFlip()
{
    if (!m_flipping) return;

    m_flip_progress += 0.1f;

    if (m_flip_progress < 0.5f)
    {
        float scale = 1.f - 2.f * m_flip_progress;
        m_card.setScale(scale, 1.f);
    }
    else if (m_flip_progress < 1.f)
    {
        float scale = -1.f + 2.f * (m_flip_progress - 0.5f);
        m_card.setScale(scale, 1.f);
    }
    else
    {
        m_card.setScale(1.f, 1.f);
        m_flipping = false;
        m_flip_finished = true;
    }
}
