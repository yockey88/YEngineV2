#ifndef MAIN_HPP
#define MAIN_HPP

#include "engine.hpp"
#include "app.hpp"

Y::App* CreateApp();

int main(int argc , char** argv) {
    /*
        auto config = RuntimeConfig ConfigEngine(AppConfig configuration || App* app);
            <R -> ||> Depends on if we want to do something with the APP or the APP'S DATA </R>
        <?> AppRuntimeData </?> Initialize(App* appToInit , RuntimeConfig configToInit);
        if (!Run(App* appToRun , AppRuntimeData dataNeededToRunApp))
            return 1;
    */

    if (!Y::Engine::Instance().Run(CreateApp())) {
        return 1;
    }
    return 0;
}

#endif