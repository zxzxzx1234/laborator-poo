#ifndef GAME_LOGGER_H
#define GAME_LOGGER_H

#include <string>
#include <iostream>

class GameLogger {
private:
    std::string m_context;
    static int s_action_count;

    std::string _FormatMessage(const std::string& msg) const;

public:
    GameLogger(const std::string& context = "General");

    void Log(const std::string& message);
    static int GetActionCount();

    // operator <<
    friend std::ostream& operator<<(std::ostream& os, const GameLogger& logger);
};

#endif
