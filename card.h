#ifndef CARD_H
#define CARD_H
#include <SFML/Graphics.hpp>
#include "igame_object.h"

using namespace std;

// Class for a single card
class Card : public IGameObject // Inherit from IGameObject
{
private:
    string m_suit; // Suit for the card
    int m_rank;    // Rank for the card
    string _GetCardHash();
    sf::Sprite m_card;
    bool m_animating = false;
    sf::Vector2f m_start_pos;
    sf::Vector2f m_target_pos;
    float m_animation_progress = 0.f;
    bool m_flipping = false;
    float m_flip_progress = 0.f;
    bool m_flip_finished = true;

public:
    Card();
    Card(string suit, int rank);
    ~Card();
    int GetCardRank() { return this->m_rank; }
    void DrawTo(sf::RenderWindow& window) override; // Implement the IGameObject method
    void SetCardPosition(sf::Vector2f pos);
    void SetColor(sf::Color color);
    void AnimateTo(sf::Vector2f target_pos);
    bool IsAnimating() const;
    void UpdateAnimation();
    void StartFlip();
    void UpdateFlip();
    bool IsFlipping() const;

};

#endif