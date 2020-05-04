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

#ifndef __SERVICE_PLUGINS_CONFIG_DATA_H__
#define __SERVICE_PLUGINS_CONFIG_DATA_H__

#include <string>
#include <vector>

namespace service::plugins::config {

/**
 * @defgroup Data Data structure
 * @ingroup Plugins
 * @{
 */

/**
 * @struct ConfigData ConfigData.h "service/plugins/IConfigData.h"
 *
 * @brief A data structure into which the whole configuration is loaded
 *
 * @author Boubacar DIENE <boubacar.diene@gmail.com>
 * @date April 2020
 */
struct ConfigData {
    /**
     * @struct Network
     *
     * @brief A data structure containing network-related data
     *
     * @note std::map<path, value> is not used to store layerCommands because
     *       the elements are sorted based on the key. As we work with network
     *       commands, it is better to make sure they are applied in the order
     *       the user provided them. Another reason is that LayerCommand is far
     *       more readable than just std::map<std::string, std::string>.
     */
    struct Network {
        /**
         * @struct LayerCommand
         */
        struct LayerCommand {
            /** Absolute path to the file to update */
            std::string pathname;

            /** The new content to write to pathname */
            std::string value;
        };

        /** (Already existing) network interfaces you need to work with
         * (E.g: eth0) */
        std::vector<std::string> interfaceNames;

        /** The list of network commands to apply (E.g: "/sbin/ip addr ...") */
        std::vector<std::string> interfaceCommands;

        /** The list of layer commands to apply */
        std::vector<LayerCommand> layerCommands;
    };

    /**
     * @struct Rule
     *
     * @brief A data structure containing firewall-related data
     */
    struct Rule {
        /** The name of the rule; just for the readability of the config and
         * logs */
        std::string name;

        /** The list of rule commands (E.g: "/sbin/iptables -P INPUT DROP") */
        std::vector<std::string> commands;
    };

    /** Member variable containing network data */
    Network network;

    /** Member variable containing rules data */
    std::vector<Rule> rules;
};

/**@}*/

}

#endif
