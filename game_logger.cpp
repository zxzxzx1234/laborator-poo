#include "game_logger.h"

int GameLogger::s_action_count = 0;

GameLogger::GameLogger(const std::string& context) {
    m_context = context;
}

void GameLogger::Log(const std::string& message) {
    s_action_count++;
    std::cout << _FormatMessage(message) << std::endl;
}

int GameLogger::GetActionCount() {
    return s_action_count;
}

std::string GameLogger::_FormatMessage(const std::string& msg) const {
    return "[" + m_context + "] " + msg;
}

std::ostream& operator<<(std::ostream& os, const GameLogger& logger) {
    os << "Logger (" << logger.m_context << ") - Actions Logged: " << GameLogger::GetActionCount();
    return os;
}
