#ifndef APP_HPP
#define APP_HPP

#include "engine.hpp"
#include "Core/window.hpp"

#include "entt.hpp"

#include <iostream>
#include <string>

namespace Y {

    class App {
        public:
            virtual ~App() {}

            virtual core::WindowProperties GetWindowProperties() { return core::WindowProperties(); }
            
            virtual void Initialize() {}
            virtual void Shutdown() {}

            virtual void Update(const float& dt) {}
            virtual void Render() {}
            virtual void ImGuiRender() {}
    };
    
}

#endif 