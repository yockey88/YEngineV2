#ifndef LOG_MANAGER_HPP
#define LOG_MANAGER_HPP

#include "log.hpp"

#include <memory>

namespace Y {
namespace managers {

    class LogManager {
        std::shared_ptr<spdlog::logger> ConsoleLogger;
        std::shared_ptr<spdlog::logger> ErrorLogger;
        bool open;

        LogManager (const LogManager&) = delete;
        LogManager &operator=(const LogManager&) = delete;

        public:
            LogManager() : open(false) {}
            ~LogManager() { Shutdown(); }

            void Initialize();
            void Shutdown();
    };

}
}

#endif
