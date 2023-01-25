#include "Core/timer.hpp"

namespace Y {
namespace core {

    float Timer::Tick() {
        return 0.f;
    }

    void Timer::Start() {
        m_StartTime = std::chrono::system_clock::now();
        m_Running = true;
    }

    void Timer::Stop() {
        m_EndTime = std::chrono::system_clock::now();
        m_Running = false;
    }
    
    float Timer::MilliSinceStart() {
        return 0.f;
    }

    float Timer::SecondsSinceStart() {
        return 0.f;
    }


}
}