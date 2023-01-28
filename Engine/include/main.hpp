#ifndef MAIN_HPP
#define MAIN_HPP

#include "engine.hpp"
#include "app.hpp"

Y::App* CreateApp();

int main() {
    Y::Engine::Instance().Run(CreateApp());
    return 0;
}

#endif