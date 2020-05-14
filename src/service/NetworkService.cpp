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

#include "NetworkService.h"

using namespace service;
using namespace service::plugins::config;
using namespace service::plugins::firewall;

NetworkService::NetworkService(const NetworkServiceParams& params) : m_params(params)
{}

int NetworkService::applyConfig(const std::string& configFile) const
{
    try {
        m_params.logger.info("Load config: " + configFile);
        const std::unique_ptr<ConfigData>& configData
            = m_params.config.load(configFile);

        m_params.logger.debug("Make sure specified interfaces are valid");
        const ConfigData::Network& networkData         = configData->network;
        const std::vector<ConfigData::Rule>& rulesData = configData->rules;

        for (const std::string& interfaceName : networkData.interfaceNames) {
            if (!m_params.network.hasInterface(interfaceName)) {
                throw std::invalid_argument("No valid interface found for: "
                                            + interfaceName);
            }
        }

        m_params.logger.debug("Apply network interface commands");
        m_params.network.applyInterfaceCommands(networkData.interfaceCommands);

        m_params.logger.debug("Apply network layer commands");
        m_params.network.applyLayerCommands(networkData.layerCommands);

        m_params.logger.debug("Create and apply rules");
        for (const ConfigData::Rule& ruleData : rulesData) {
            const std::unique_ptr<IRule>& rule
                = m_params.ruleFactory.createRule(ruleData.name, ruleData.commands);

            if (!rule) {
                throw std::runtime_error("createRule() returned an invalid object");
            }

            rule->applyCommands();
        }
    }
    catch (const std::exception& e) {
        // All exceptions are caught because the service is expected to ignore
        // how lower -level components are implemented (which specific exception
        // is raised, ...)
        m_params.logger.error(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
