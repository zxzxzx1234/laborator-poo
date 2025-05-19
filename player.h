#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "user.h"

using namespace std;

class Player : public User
{
private:
    // int _bet;
    int m_bet;
    // Current player balance

public:
    // Constructor
    Player();

    // Destructor
    ~Player();

    // Calculates the player's total points (inherited from User)
    int CalculatePoints(vector<Card>& cards);

    // Adjust the player's bet (add or subtract depending on result)
    void SetBet(int amount, bool did_lose = false);

    // Return current bet amount
    int GetBet();

    // Reset player's balance to zero
    void Reset();
};

#endif
