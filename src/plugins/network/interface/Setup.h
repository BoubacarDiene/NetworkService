#ifndef __PLUGINS_NETWORK_INTERFACE_SETUP_H__
#define __PLUGINS_NETWORK_INTERFACE_SETUP_H__

#include <memory>
#include <string>

#include "service/plugins/ILogger.h"

namespace service::plugins::network::interface {

class Interface {

public:
    explicit Interface(const service::plugins::logger::ILogger& logger);

    ~Interface();

    Interface(const Interface&) = delete;

    Interface& operator=(const Interface&) = delete;

    Interface(Interface&&) = delete;

    Interface& operator=(Interface&&) = delete;

    void applyCommand(const std::string& command) const;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
