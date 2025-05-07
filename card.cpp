#include "card.h"

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

// uses the texture from the configuration file (not finished)
void Card::DrawTo(sf::RenderWindow& window)
{
    string hash = this->_GetCardHash();                         // gets the hash
    this->m_card.setTexture(config.get_texture(hash));          // sets the texture
    window.draw(this->m_card);                                  // draws the sprite
}
