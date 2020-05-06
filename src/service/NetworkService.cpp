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

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <utility>

#include "NetworkService.h"

using namespace service;
using namespace service::plugins::config;
using namespace service::plugins::firewall;
using namespace service::plugins::logger;
using namespace service::plugins::network;

// std::move is used on logger for performances's sake. Indeed, logger is
// passed by copy => +1 on reference counter.
// Without std::move, +1 again on reference counter so it is better to use
// std::move here to move the ownership of NetworkService's copy of logger
// object to its internal member object (m_logger).
//
// For others (unique_ptr), std::move is required because the constructor
// does not just use provided objects. It also keeps copies.
NetworkService::NetworkService(std::shared_ptr<ILogger> logger,
                               std::unique_ptr<IConfig> config,
                               std::unique_ptr<INetwork> network,
                               std::unique_ptr<IRuleFactory> ruleFactory)
    : m_logger(std::move(logger)),
      m_config(std::move(config)),
      m_network(std::move(network)),
      m_ruleFactory(std::move(ruleFactory))
{}

int NetworkService::applyConfig(const std::string& configFile) const
{
    try {
        m_logger->debug("Load config: " + configFile);
        const std::unique_ptr<ConfigData>& configData
            = m_config->load(configFile);

        m_logger->debug("Make sure specified interfaces are valid");
        const ConfigData::Network& networkData         = configData->network;
        const std::vector<ConfigData::Rule>& rulesData = configData->rules;

        for (const std::string& interfaceName : networkData.interfaceNames) {
            if (!m_network->hasInterface(interfaceName)) {
                throw std::invalid_argument("No valid interface found for: "
                                            + interfaceName);
            }
        }

        m_logger->debug("Apply network interface commands");
        m_network->applyInterfaceCommands(networkData.interfaceCommands);

        m_logger->debug("Apply network layer commands");
        m_network->applyLayerCommands(networkData.layerCommands);

        m_logger->debug("Create and apply rules");
        for (const ConfigData::Rule& ruleData : rulesData) {
            const std::unique_ptr<IRule>& rule
                = m_ruleFactory->createRule(ruleData.name, ruleData.commands);
            rule->applyCommands();
        }
    }
    catch (const std::exception& e) {
        // All exceptions are caught because the service is expected to ignore
        // how lower -level components are implemented (which specific exception
        // is raised, ...)
        m_logger->error(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
