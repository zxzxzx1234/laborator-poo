#include "player.h"

// Constructor - sets initial bet
Player::Player()
{
    m_bet = 2500;
}

// Destructor
Player::~Player() {}

// Update bet: subtract if lost, add if won
void Player::SetBet(int amount, bool did_lose)
{
    if (did_lose) {
        m_bet -= amount;
    }
    else {
        m_bet += amount;
    }
}

// Resets player's bet to zero
void Player::Reset()
{
    m_bet = 0;
}

// Calculates player's points using base class method
int Player::CalculatePoints(vector<Card>& cards)
{
    return User::CalculatePoints(cards);
}

// Returns current player bet
int Player::GetBet()
{
    return m_bet;
}
