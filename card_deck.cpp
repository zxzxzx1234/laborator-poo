#include "card_deck.h"

// creates all the cards and inserts them into a dictionary
void CardDeck::_InitCards()
{
    for (int i = 1; i <= 13; ++i)
    {
        Card spade_card("s", i);
        this->m_cards["s" + to_string(i)] = spade_card;

        Card heart_card("h", i);
        this->m_cards["h" + to_string(i)] = heart_card;

        Card diamond_card("d", i);
        this->m_cards["d" + to_string(i)] = diamond_card;

        Card club_card("c", i);
        this->m_cards["c" + to_string(i)] = club_card;
    }
}

// contructor - initializing the deck
CardDeck::CardDeck()
{
    this->_InitCards();
}

// destructor
CardDeck::~CardDeck() {}

// chooses a random suit and rank
string CardDeck::_RandCard()
{
    int rand_suit = rand() % 4;      
    int rand_rank = rand() % 13 + 1;  

    string card = "";
    switch (rand_suit)
    {
    case 0:
        card += "s";
        break;
    case 1:
        card += "c";
        break;
    case 2:
        card += "d";
        break;
    case 3:
        card += "h";
        break;
    default:
        break;
    }

    card += to_string(rand_rank);
    return card;
}

// returns the Card object
Card CardDeck::DrawCard()
{
    string card_hash = this->_RandCard();
    return this->m_cards[card_hash];
}
