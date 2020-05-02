#ifndef __SERVICE_PLUGINS_ILOGGER_H__
#define __SERVICE_PLUGINS_ILOGGER_H__

#include <string>

namespace service::plugins::logger {

class ILogger {

public:
    ILogger() = default;

    virtual ~ILogger() = default;

    ILogger(const ILogger&) = delete;

    ILogger& operator=(const ILogger&) = delete;

    ILogger(ILogger&&) = delete;

    ILogger& operator=(ILogger&&) = delete;

    /**
     * One purpose in marking these member functions as const is that
     * a const pointer or reference to ILogger can be used to call them.
     * Thus, one can get "const ILogger*" or "const ILogger&" as input
     * if neighter a reset of the logger object, nor becoming an owner
     * of it is necessary.
     *
     * Without this const, one would be forced to use "ILogger*" or
     * "ILogger&" in that case thus have possibility to alter the
     * logger object which is not what is expected.
     */
    virtual void debug(const std::string& message) const = 0;

    virtual void info(const std::string& message) const = 0;

    virtual void warn(const std::string& message) const = 0;

    virtual void error(const std::string& message) const = 0;
};

}

#endif
