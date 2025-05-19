#ifndef GAME_STATS_H
#define GAME_STATS_H

#include <iostream>

struct GameStats {
    int wins = 0;
    int losses = 0;
    int ties = 0;

    GameStats() = default;
    GameStats(int w, int l, int t) : wins(w), losses(l), ties(t) {}

    GameStats operator+(const GameStats& other) const {
        return {
            wins + other.wins,
            losses + other.losses,
            ties + other.ties
        };
    }

    friend std::ostream& operator<<(std::ostream& os, const GameStats& stats) {
        os << "[Stats] Wins: " << stats.wins
            << " | Losses: " << stats.losses
            << " | Ties: " << stats.ties;
        return os;
    }
};

#endif
