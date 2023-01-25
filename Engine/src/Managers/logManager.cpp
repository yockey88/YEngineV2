#include "Managers/logManager.hpp"

namespace Y {
namespace managers {

    void LogManager::Initialize() {
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto errSink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();

        consoleSink->set_pattern("[ %v ] | [%D %H:%M:%S.%e %Y]");

        std::vector<spdlog::sink_ptr> sinks1{ consoleSink };
        ConsoleLogger = std::make_shared<spdlog::logger>(CONSOLE_LOGGER_NAME , sinks1.begin() , sinks1.end());
        ConsoleLogger->set_level(spdlog::level::trace);
        ConsoleLogger->flush_on(spdlog::level::trace);
        spdlog::register_logger(ConsoleLogger);

        std::vector<spdlog::sink_ptr> sinks2 { errSink };
        ErrorLogger = std::make_shared<spdlog::logger>(ERROR_LOGGER_NAME , sinks2.begin() , sinks2.end());
        ErrorLogger->set_level(spdlog::level::warn);
        ErrorLogger->flush_on(spdlog::level::warn);
        spdlog::register_logger(ErrorLogger);

        open = true;
    }

    void LogManager::Shutdown() {
        spdlog::shutdown();
    }

}
}