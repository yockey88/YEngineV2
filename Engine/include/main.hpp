#ifndef MAIN_HPP
#define MAIN_HPP

#include "engine.hpp"
#include "app.hpp"

Y::App* CreateApp();

int main() {
    if (!EngineY.Run(CreateApp())) {
        return 1;
    }
    return 0;
}

#endif