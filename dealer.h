#ifndef DEALER_H
#define DEALER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "user.h"
#include "card_deck.h"

using namespace std;

class Dealer : public User
{
public:
    // Default constructor
    Dealer();

    // Destructor
    ~Dealer();

    // Dealer draws cards automatically until score > 17
    int DrawCardAI(vector<Card>& cards, CardDeck card_deck);

    // Calculates dealer's total points (based on User implementation)
    int CalculatePoints(vector<Card>& cards);
};

#endif
