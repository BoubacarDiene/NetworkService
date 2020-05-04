#ifndef __PLUGINS_NETWORK_NETWORK_H__
#define __PLUGINS_NETWORK_NETWORK_H__

#include <memory>

#include "service/plugins/ILogger.h"
#include "service/plugins/INetwork.h"

namespace service::plugins::network {

class Network : public INetwork {

public:
    explicit Network(const service::plugins::logger::ILogger& logger);

    /**
     * Not common but makes the compiler warn if the base destructor is not
     * virtual
     */
    ~Network() override;

    Network(const Network&) = delete;

    Network& operator=(const Network&) = delete;

    Network(Network&&) = delete;

    Network& operator=(Network&&) = delete;

    [[nodiscard]] bool
        hasInterface(const std::string& interfaceName) const override;

    void applyInterfaceCommands(
        const std::vector<std::string>& interfaceCommands) const override;

    void applyLayerCommands(
        const std::vector<
            service::plugins::config::ConfigData::Network::LayerCommand>&
            layerCommands) const override;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
