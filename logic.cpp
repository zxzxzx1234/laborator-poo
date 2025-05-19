#include "logic.h"

// Constructor
Logic::Logic() {}

// Destructor
Logic::~Logic() {}

// Compares points and determines win condition
int Logic::CheckUserWin(int player_points, int dealer_points)
{
    bool win_by_score = (player_points <= 21 && dealer_points <= 21 && player_points > dealer_points);
    bool win_by_bust = (player_points <= 21 && dealer_points > 21);
    bool tie = (player_points <= 21 && dealer_points <= 21 && player_points == dealer_points);

    if (win_by_score || win_by_bust) return WIN;
    if (tie) return TIE;
    return LOSE;
}
