//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
//                                                                          //
//  Copyright © 2020 Boubacar DIENE                                         //
//                                                                          //
//  This file is part of NetworkService project.                            //
//                                                                          //
//  NetworkService is free software: you can redistribute it and/or modify  //
//  it under the terms of the GNU General Public License as published by    //
//  the Free Software Foundation, either version 2 of the License, or       //
//  (at your option) any later version.                                     //
//                                                                          //
//  NetworkService is distributed in the hope that it will be useful,       //
//  but WITHOUT ANY WARRANTY; without even the implied warranty of          //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           //
//  GNU General Public License for more details.                            //
//                                                                          //
//  You should have received a copy of the GNU General Public License       //
//  along with NetworkService. If not, see <http://www.gnu.org/licenses/>   //
//  or write to the Free Software Foundation, Inc., 51 Franklin Street,     //
//  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.           //
//                                                                          //
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//

#include <cerrno>
#include <ifaddrs.h>
#include <stdexcept>
#include <sys/socket.h>
#include <utility>

#include "utils/helper/Errno.h"

#include "interface/Setup.h"
#include "layer/Setup.h"

#include "Network.h"

using namespace service::plugins::config;
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
    const std::vector<ConfigData::Network::LayerCommand>& layerCommands) const
{
    for (const auto& layerCommand : layerCommands) {
        m_internal->logger.debug("Apply layer command to: "
                                 + layerCommand.pathname);
        m_internal->layer->applyCommand(layerCommand.pathname,
                                        layerCommand.value);
    }
}
