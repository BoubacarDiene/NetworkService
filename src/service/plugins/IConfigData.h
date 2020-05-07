//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
//                                                                                //
// MIT License                                                                    //
//                                                                                //
// Copyright (c) 2020 Boubacar DIENE                                              //
//                                                                                //
// This file is part of NetworkService project                                    //
//                                                                                //
// Permission is hereby granted, free of charge, to any person obtaining a copy   //
// of this software and associated documentation files (the "Software"), to deal  //
// in the Software without restriction, including without limitation the rights   //
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      //
// copies of the Software, and to permit persons to whom the Software is          //
// furnished to do so, subject to the following conditions:                       //
//                                                                                //
// The above copyright notice and this permission notice shall be included in all //
// copies or substantial portions of the Software.                                //
//                                                                                //
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     //
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       //
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    //
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         //
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  //
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  //
// SOFTWARE.                                                                      //
//                                                                                //
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//

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
 * @struct ConfigData IConfigData.h "service/plugins/IConfigData.h"
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
