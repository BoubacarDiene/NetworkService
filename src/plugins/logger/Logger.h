#ifndef __PLUGINS_LOGGER_LOGGER_H__
#define __PLUGINS_LOGGER_LOGGER_H__

#include <memory>

#include "service/plugins/ILogger.h"

namespace service::plugins::logger {

class Logger : public ILogger {

public:
    explicit Logger();

    /**
     * Not common but makes the compiler warn if the base destructor is not
     * virtual
     */
    ~Logger() override;

    Logger(const Logger&) = delete;

    Logger& operator=(const Logger&) = delete;

    Logger(Logger&&) = delete;

    Logger& operator=(Logger&&) = delete;

    void debug(const std::string& message) const override;

    void info(const std::string& message) const override;

    void warn(const std::string& message) const override;

    void error(const std::string& message) const override;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
