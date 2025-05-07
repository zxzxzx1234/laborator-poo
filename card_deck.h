#ifndef CARD_DECK_H
#define CARD_DECK_H
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "card.h"

using namespace std;

class CardDeck
{
private:
    unordered_map<string, Card> m_cards;  //dictionary with all the cards in the deck
    void _InitCards(); //initializing the cards
    string _RandCard(); //generating a random hash

public:
    CardDeck(); //constructor
    ~CardDeck(); //destructor
    Card DrawCard(); //returns a random card
};

#endif
