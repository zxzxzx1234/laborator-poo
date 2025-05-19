#ifndef LOGIC_H
#define LOGIC_H

#include "config.h"
#include <SFML/Graphics.hpp>
using namespace std;

// Utility structure to safely convert string to int
struct StrToIntParser
{
private:
    string m_str;

    // Check if the string represents a valid integer number
    bool IsDigit()
    {
        for (int i = 0; i < m_str.length(); ++i)
        {
            if (i == 0 && m_str[i] == '0') return false;
            if (!(m_str[i] >= '0' && m_str[i] <= '9')) return false;
        }
        return true;
    }

public:
    // Constructor
    StrToIntParser(string str) { m_str = str; }

    // Convert to integer or return -1 if invalid
    int ToInt()
    {
        if (m_str.empty()) return -1;
        if (!IsDigit()) return -1;
        return stoi(m_str);
    }
};

class Logic
{
public:
    // Constructor
    Logic();

    // Destructor
    ~Logic();

    // Check win condition: return WIN / LOSE / TIE
    int CheckUserWin(int player_points, int dealer_points);
};

#endif
