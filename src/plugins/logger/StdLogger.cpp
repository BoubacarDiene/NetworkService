#include <iostream>

#include "Logger.h"

#define BLUE   "\033[0;34m"
#define YELLOW "\033[1;33m"
#define RED    "\033[5;31m"
#define GREEN  "\033[0;32m"

#define END "\033[0m"

using namespace service::plugins::logger;

struct Logger::Internal {
    static void debug(const std::string& message,
                      const char* const color = BLUE)
    {
        std::cout << color << message << END << std::endl;
    }

    static void error(const std::string& message, const char* const color = RED)
    {
        std::cerr << color << message << END << std::endl;
    }
};

Logger::Logger() : m_internal(std::make_unique<Internal>()) {}

Logger::~Logger() = default;

void Logger::debug(const std::string& message) const
{
    Internal::debug(message);
}

void Logger::info(const std::string& message) const
{
    Internal::debug(message, GREEN);
}

void Logger::warn(const std::string& message) const
{
    Internal::debug(message, YELLOW);
}

void Logger::error(const std::string& message) const
{
    Internal::error(message);
}
