#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <stdlib.h>

#define Y_CONSOLE_LOGGER_NAME "Engine Console Log"
#define Y_ERROR_LOGGER_NAME "Engine Error Log"

#if defined(Y_PLATFORM_WINDOWS)
#define Y_BREAK __debugbreak();
#elif defined(Y_PLATFORM_MAC)
#define Y_BREAK __builtin_debugtrap();
#else
#define Y_BREAK __builtin_trap();
#endif

#define Y_INFO(...) \
    if (spdlog::get(Y_CONSOLE_LOGGER_NAME) != nullptr) { \
        spdlog::get(Y_CONSOLE_LOGGER_NAME)->info(__VA_ARGS__);\
    }

#ifndef Y_CONFIG_RELEASE
#define Y_TRACE(...) \
    if (spdlog::get(Y_CONSOLE_LOGGER_NAME) != nullptr) { \
        spdlog::get(Y_CONSOLE_LOGGER_NAME)->trace(__VA_ARGS__);\
    }
#define Y_DEBUG(...) \
    if (spdlog::get(Y_CONSOLE_LOGGER_NAME) != nullptr) { \
        spdlog::get(Y_CONSOLE_LOGGER_NAME)->debug(__VA_ARGS__);\
    }
#define Y_WARN(...) \
    if (spdlog::get(Y_ERROR_LOGGER_NAME) != nullptr) { \
        spdlog::get(Y_ERROR_LOGGER_NAME)->warn(__VA_ARGS__);\
    }
#define Y_ERROR(...) \
    if (spdlog::get(Y_ERROR_LOGGER_NAME) != nullptr) { \
        spdlog::get(Y_ERROR_LOGGER_NAME)->error(__VA_ARGS__);\
    }
#define Y_FATAL(...) \
    if (spdlog::get(Y_ERROR_LOGGER_NAME) != nullptr) { \
        spdlog::get(Y_ERROR_LOGGER_NAME)->critical(__VA_ARGS__);\
    }
#define Y_ASSERT(x , msg) \
    if ((x)) {} \
    else { Y_FATAL("|!|ASSERT|!| -> {}|\n\t\t|{}|\n\t\t| in file: {}|\n\t\t| in line: {}|" , x , msg , __FILE__ , __LINE__); Y_BREAK }
#else
#define Y_TRACE(...) (void)0
#define Y_TRACE(...) (void)0
#define Y_DEBUG(...) (void)0
#define Y_WARN(...) (void)0
#define Y_ERROR(...) (void)0
#define Y_FATAL(...) (void)0
#define Y_ASSERT(x , msg) (void*)0
#endif

#endif
