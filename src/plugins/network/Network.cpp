#include <cerrno>
#include <ifaddrs.h>
#include <stdexcept>
#include <sys/socket.h>
#include <utility>

#include "utils/helper/Errno.h"

#include "interface/Setup.h"
#include "layer/Setup.h"

#include "Network.h"

using namespace service::plugins::logger;
using namespace service::plugins::network;
using namespace service::plugins::network::interface;
using namespace service::plugins::network::layer;
using namespace utils::helper;

struct Network::Internal {
    const ILogger& logger;

    /* const to make these objects non-copyable, non-movable and
     * non-resettable.
     *
     * A pointer just to avoid creating them on the stack */
    const std::unique_ptr<Interface> interface;
    const std::unique_ptr<Layer> layer;

    explicit Internal(const ILogger& providedLogger)
        : logger(providedLogger),
          interface(std::make_unique<Interface>(logger)),
          layer(std::make_unique<Layer>(logger))
    {}
};

Network::Network(const ILogger& logger)
    : m_internal(std::make_unique<Internal>(logger))
{}

Network::~Network() = default;

bool Network::hasInterface(const std::string& interfaceName) const
{
    bool exist           = false;
    ifaddrs* ifaddresses = nullptr;

    if (getifaddrs(&ifaddresses) == -1) {
        throw std::runtime_error(Errno::toString("getifaddrs()", errno));
    }

    for (auto* ifa = ifaddresses; ifa != nullptr; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == nullptr) {
            continue;
        }

        if ((ifa->ifa_addr->sa_family == AF_PACKET)
            && (interfaceName == ifa->ifa_name)) {
            m_internal->logger.debug("Interface exists: " + interfaceName);
            exist = true;
            break;
        }
    }

    freeifaddrs(ifaddresses);

    return exist;
}

void Network::applyInterfaceCommands(
    const std::vector<std::string>& interfaceCommands) const
{
    for (const std::string& interfaceCommand : interfaceCommands) {
        m_internal->logger.debug("Apply interface command: "
                                 + interfaceCommand);
        m_internal->interface->applyCommand(interfaceCommand);
    }
}

void Network::applyLayerCommands(
    const std::map<std::string, std::string>& layerCommands) const
{
    for (const auto& [pathname, value] : layerCommands) {
        m_internal->logger.debug("Apply layer command to: " + pathname);
        m_internal->layer->applyCommand(pathname, value);
    }
}
