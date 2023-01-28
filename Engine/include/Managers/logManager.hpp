#ifndef LOG_MANAGER_HPP
#define LOG_MANAGER_HPP

#include "log.hpp"

#include <queue>
#include <string>
#include <fstream>
#include <memory>

namespace Y {

namespace managers {

    class LogManager {
        std::shared_ptr<spdlog::logger> m_ConsoleLogger;
        std::shared_ptr<spdlog::logger> m_ErrorLogger;
        bool m_Open;

        // Delete Copy Constructors
        LogManager (const LogManager&) = delete;
        LogManager &operator=(const LogManager&) = delete;
        public:
            LogManager() {}
            ~LogManager() { Shutdown(); }

            void Initialize();

            void Shutdown();

            inline bool isOpen() { return m_Open; }
    };

} // End of Managers

} // End of Y

#endif /* logManager.hpp */