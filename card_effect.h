#ifndef CARD_EFFECT_H
#define CARD_EFFECT_H

#include "card.h"

class CardEffect {
public:
    virtual void Apply(Card& card) = 0;
    virtual ~CardEffect() {}
};

class BurnEffect : public CardEffect {
public:
    void Apply(Card& card) override;
};

#endif
