
#include "Managers/logManager.hpp"

namespace Y {
namespace managers {

    void LogManager::Initialize() {
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto errSink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();

        consoleSink->set_pattern("[ %v ] | [%D %H:%M:%S.%e %Y]");

        std::vector<spdlog::sink_ptr> sinks1{ consoleSink };
        m_ConsoleLogger = std::make_shared<spdlog::logger>(Y_CONSOLE_LOGGER_NAME , sinks1.begin() , sinks1.end());
        m_ConsoleLogger->set_level(spdlog::level::trace);
        m_ConsoleLogger->flush_on(spdlog::level::trace);
        spdlog::register_logger(m_ConsoleLogger);

        std::vector<spdlog::sink_ptr> sinks2 { errSink };
        m_ErrorLogger = std::make_shared<spdlog::logger>(Y_ERROR_LOGGER_NAME , sinks2.begin() , sinks2.end());
        m_ErrorLogger->set_level(spdlog::level::warn);
        m_ErrorLogger->flush_on(spdlog::level::warn);
        spdlog::register_logger(m_ErrorLogger);

        m_Open = true;
    }

    void LogManager::Shutdown() {
        spdlog::shutdown();
    }

}
}