#ifndef CARD_H
#define CARD_H
#include <SFML/Graphics.hpp>

using namespace std;
// class for a single card
class Card
{
private:
    string m_suit; //suit for the card
    int m_rank; // rank for the card
    string _GetCardHash();
    sf::Sprite m_card;

public:
    Card();
    Card(string suit, int rank);
    ~Card();
    int GetCardRank() { return this->m_rank; }
    void DrawTo(sf::RenderWindow& window);
    void SetCardPosition(sf::Vector2f pos);
};

#endif
