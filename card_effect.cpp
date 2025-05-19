#include "card_effect.h"

void BurnEffect::Apply(Card& card)
{
    card.SetColor(sf::Color(255, 100, 100));  // light red tint
}
