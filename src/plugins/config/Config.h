#ifndef __PLUGINS_CONFIG_CONFIG_H__
#define __PLUGINS_CONFIG_CONFIG_H__

#include <memory>

#include "service/plugins/IConfig.h"
#include "service/plugins/ILogger.h"

namespace service::plugins::config {

class Config : public IConfig {

public:
    enum class Source { JSON, MOCK, YAML };

    /**
     * logger made a const reference for better performances instead of
     * allowing this class to have its own copy of the logger (shared_ptr).
     * The counterpart is that the logger object must remain valid until
     * this class is no longer used.
     *
     * For example, the following code in "upper layer" where this class
     * is instantiated would make the service crash:
     *
     * // Declare config here
     * {
     *     // Initialize logger
     *     <type> logger = ...
     *     // Initialize Config
     *     config = Config(logger, ...)
     * }
     * // Using config here (out of scope) => crash because logger is not
     *    valid anymore.
     *
     * Passing std::shared_ptr by copy would solve that problem but it's
     * fine doing things this way because, by design, the plugins are part
     * of the lower-level details so the "upper layer" which instantiates
     * this class has to know how to properly use it
     */
    explicit Config(const service::plugins::logger::ILogger& logger,
                    const Source& dataSource);

    /**
     * Not common but makes the compiler warn if the base destructor is not
     * virtual
     */
    ~Config() override;

    Config(const Config&) = delete;

    Config& operator=(const Config&) = delete;

    Config(Config&&) = delete;

    Config& operator=(Config&&) = delete;

    [[nodiscard]] std::unique_ptr<ConfigData>
        load(const std::string& configFile) const override;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
