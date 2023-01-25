#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <ctime>
#include <cmath>

namespace Y {
namespace core {

    class Timer {
        std::chrono::time_point<std::chrono::system_clock> m_StartTime , m_EndTime;
        std::chrono::time_point<std::chrono::system_clock> m_LastTick , m_Now;
        std::chrono::duration<float> m_DeltaTime;
        bool m_Running;
        public:
            Timer() : m_Running(false) {}
            ~Timer() {}

            float Tick();
            void Start();
            void Stop();

            float MilliSinceStart();
            float SecondsSinceStart();
    };

}
}

#endif
