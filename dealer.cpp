#include "dealer.h"

// Constructor
Dealer::Dealer() {}

// Destructor
Dealer::~Dealer() {}

// AI logic for dealer to draw cards while under or equal to 17 points
int Dealer::DrawCardAI(vector<Card>& cards, CardDeck card_deck)
{
    int dealer_points = this->CalculatePoints(cards);

    while (dealer_points <= 17)
    {
        Card card = card_deck.DrawCard();
        cards.push_back(card);
        dealer_points = this->CalculatePoints(cards);
    }

    return dealer_points;
}

// Calculates dealer's points using the inherited method from User
int Dealer::CalculatePoints(vector<Card>& cards)
{
    return User::CalculatePoints(cards);
}
