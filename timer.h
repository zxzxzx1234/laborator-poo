#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer {
private:
    std::chrono::time_point<std::chrono::steady_clock> m_start;

public:
    Timer(); // Declaration of the constructor

    int ElapsedMilliseconds(); // Declaration of the method
};

#endif
