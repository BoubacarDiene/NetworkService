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

#ifndef __SERVICE_PLUGINS_INETWORK_H__
#define __SERVICE_PLUGINS_INETWORK_H__

#include <string>
#include <vector>

#include "IConfigData.h"

namespace service::plugins::network {

/**
 * @interface INetwork INetwork.h "service/plugins/INetwork.h"
 * @ingroup Abstraction
 *
 * @brief Configure the network (enable network interfaces, set IP addresses,
 *        add new network interfaces, ...)
 *
 * This class is the high level interface that must be implemented by network
 * plugin. The core service depends on it and not on its implementation(s) to
 * respect the Dependency Inversion Principle. The network plugin must be
 * capable of applying network commands (based on "ip" tool for example) and
 * configuring the network layer (understand update some network-related files
 * in the filesystem with new values).
 *
 * @note
 * Copy contructor, copy-assignment operator, move constructor and move
 * assignment operator are defined to be compliant with the "Rule of five".
 *
 * @see https://en.cppreference.com/w/cpp/language/rule_of_three
 *
 * @author Boubacar DIENE <boubacar.diene@gmail.com>
 * @date April 2020
 */
class INetwork {

public:
    /** Class constructor */
    INetwork() = default;

    /** Class destructor made virtual because it is used as base class by
     *  derived classes in network plugin */
    virtual ~INetwork() = default;

    /** Class copy constructor */
    INetwork(const INetwork&) = delete;

    /** Class copy-assignment operator */
    INetwork& operator=(const INetwork&) = delete;

    /** Class move constructor */
    INetwork(INetwork&&) = delete;

    /** Class move-assignment operator */
    INetwork& operator=(INetwork&&) = delete;

    /**
     * @brief Check if the network interface whose name is "interfaceName"
     *        exists.
     *
     * @param interfaceName The network interface to check
     *
     * @return true if the interface exists, false otherwise
     */
    [[nodiscard]] virtual bool
        hasInterface(const std::string& interfaceName) const = 0;

    /**
     * @brief Apply "interface commands" i.e network commands more or less
     *        related to setting up a network interface (Add a new interface
     *        using "ip tuntap" or label for example, set IP addresses, set
     *        interfaces up, add an interface to a network bridge, ...).
     *
     * @param interfaceCommands Thee list of interface commands to apply
     *
     * @see ConfigData
     */
    virtual void applyInterfaceCommands(
        const std::vector<std::string>& interfaceCommands) const = 0;

    /**
     * @brief Apply "layer commands" i.e commands that simply consist in
     *        writing a given value to a specific network-related file (IP
     *        forwarding: /proc/sys/net/ipv4/ip_forward is a common example)
     *
     * @param layerCommands The list of layer commands to apply
     *
     * @see ConfigData
     */
    virtual void applyLayerCommands(
        const std::vector<
            service::plugins::config::ConfigData::Network::LayerCommand>&
            layerCommands) const = 0;
};

}

#endif
