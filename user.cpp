#include "user.h"

User::User() {}

User::~User() {}

int User::CalculatePoints(vector<Card>& cards)
{
    int ace_count = 0;
    int total = 0;

    // First pass to handle non-ace cards and count aces
    for (int i = 0; i < cards.size(); ++i)
    {
        int rank = cards[i].GetCardRank();

        if (rank == ACE && i <= 1)
        {
            ace_count++;
            continue;
        }

        if (rank >= ACE && rank <= TEN)
        {
            total += rank;
            continue;
        }

        if (rank == JACK || rank == QUEEN || rank == KING)
        {
            total += TEN;
            continue;
        }
    }

    // Handle aces: smartly assign 11 or 1 to avoid bust
    bool busted = (total + 11) > 21;
    if (ace_count == 1 && !busted) total += 11;
    if (ace_count == 1 && busted) total += 1;

    busted = (total + 12) > 21;
    if (ace_count == 2 && !busted) total += 12;
    if (ace_count == 2 && busted) total += 2;

    return total;
}
