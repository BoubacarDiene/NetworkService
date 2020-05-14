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

#ifndef __PLUGINS_NETWORK_NETWORK_H__
#define __PLUGINS_NETWORK_NETWORK_H__

#include <memory>

#include "service/plugins/ILogger.h"
#include "utils/command/executor/IExecutor.h"
#include "utils/file/writer/IWriter.h"

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
     * @param logger   Logger object to print some useful logs
     * @param executor Command executor to use
     * @param writer   Writer object to write into files
     */
    explicit Network(const service::plugins::logger::ILogger& logger,
                     const utils::command::IExecutor& executor,
                     const utils::file::IWriter& writer);

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
    [[nodiscard]] bool hasInterface(const std::string& interfaceName) const override;

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
