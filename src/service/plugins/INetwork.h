#ifndef __SERVICE_PLUGINS_INETWORK_H__
#define __SERVICE_PLUGINS_INETWORK_H__

#include <string>
#include <vector>

#include "IConfigData.h"

namespace service::plugins::network {

class INetwork {

public:
    INetwork() = default;

    virtual ~INetwork() = default;

    INetwork(const INetwork&) = delete;

    INetwork& operator=(const INetwork&) = delete;

    INetwork(INetwork&&) = delete;

    INetwork& operator=(INetwork&&) = delete;

    [[nodiscard]] virtual bool
        hasInterface(const std::string& interfaceName) const = 0;

    virtual void applyInterfaceCommands(
        const std::vector<std::string>& interfaceCommands) const = 0;

    virtual void applyLayerCommands(
        const std::vector<
            service::plugins::config::ConfigData::Network::LayerCommand>&
            layerCommands) const = 0;
};

}

#endif
