#include "timer.h"

Timer::Timer() {
    m_start = std::chrono::steady_clock::now(); // Definition of the constructor
}

int Timer::ElapsedMilliseconds() {
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(now - m_start).count();
}
