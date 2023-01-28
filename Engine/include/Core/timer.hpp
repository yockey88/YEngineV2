#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

namespace Y {
namespace core {

    class Timer {
        std::chrono::time_point<std::chrono::steady_clock> startTime , now , lastTime;
        int fps;
        float deltaTime;
        float msBuildup;


        public:
            Timer() : deltaTime(0.f) , fps(60) {}

            void start();

            void step();

            inline void setFPS(const int& fps) { this->fps = fps; }
            inline float getDelta() const { return deltaTime; }
            inline float getBuildup() const { return msBuildup; }
    };

}
}

#endif