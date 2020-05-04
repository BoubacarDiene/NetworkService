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

#ifndef __PLUGINS_NETWORK_NETWORK_H__
#define __PLUGINS_NETWORK_NETWORK_H__

#include <memory>

#include "service/plugins/ILogger.h"
#include "service/plugins/INetwork.h"

namespace service::plugins::network {

/**
 * @class Network Network.h "plugins/network/Network.h"
 * @ingroup Implementation
 *
 * @brief Configure the network (enable network interfaces, set IP addresses,
 *        add new network interfaces, ...)
 *
 * This class is the "low level class" that implements @ref INetwork.h
 *
 * @note Copy contructor, copy-assignment operator, move constructor and
 *       move-assignment operator are defined to be compliant with the
 *       "Rule of five"
 *
 * @see https://en.cppreference.com/w/cpp/language/rule_of_three
 *
 * @author Boubacar DIENE <boubacar.diene@gmail.com>
 * @date April 2020
 */
class Network : public INetwork {

public:
    /**
     * Class constructor
     *
     * @param logger  Logger object to print some useful logs
     *
     * @note Instead of allowing this class to have its own copy of the logger
     *       object (shared_ptr), logger is made a non-const reference to a
     *       const object for better performances. The counterpart is that the
     *       logger object must (obviously) be kept valid by Main.cpp where it
     *       is created until this class is no longer used.
     */
    explicit Network(const service::plugins::logger::ILogger& logger);

    /**
     * Class destructor
     *
     * @note The override specifier aims at making the compiler warn if the
     *       base class's destructor is not virtual.
     */
    ~Network() override;

    /** Class copy constructor */
    Network(const Network&) = delete;

    /** Class copy-assignment operator */
    Network& operator=(const Network&) = delete;

    /** Class move constructor */
    Network(Network&&) = delete;

    /** Class move-assignment operator */
    Network& operator=(Network&&) = delete;

    /** Check if the network interface whose name is "interfaceName" exists */
    [[nodiscard]] bool
        hasInterface(const std::string& interfaceName) const override;

    /**
     * @brief Apply "interface commands"
     *
     * @param interfaceCommands Thee list of interface commands to apply
     */
    void applyInterfaceCommands(
        const std::vector<std::string>& interfaceCommands) const override;

    /**
     * @brief Apply "layer commands"
     *
     * @param layerCommands The list of layer commands to apply
     */
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
