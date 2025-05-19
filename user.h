#ifndef USER_H
#define USER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "card.h"
#include "config.h"

using namespace std;

// Private helper function for raw point calculation (not used externally)
int _CalculatePoints(vector<Card>& cards);

class User
{
public:
    // Constructor
    User();

    // Destructor
    ~User();

    // Calculates the total score from a list of cards (handling aces properly)
    int CalculatePoints(vector<Card>& cards);
};

#endif
