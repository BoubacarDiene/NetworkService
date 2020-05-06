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

#include "Config.h"

using namespace service::plugins::config;
using namespace service::plugins::logger;

struct Config::Internal {
    const ILogger& logger;

    explicit Internal(const ILogger& providedLogger) : logger(providedLogger) {}

    static void fillInConfigData(const std::string& configFile,
                                 std::unique_ptr<ConfigData>& configData)
    {
        /* Instead of "forwarding" configFile, a real config reader could, for
         * example, open it to obtain a valid stream to retrieve data from.
         *
         * Besides, unlike to other config generators, configFile is a fake
         * config file i.e no config is loaded from there. Nevertheless, the
         * file exists in the filesystem so it is used here to store output of
         * some commands */
        fillInNetworkData(configFile, &configData->network);
        fillInRulesData(configFile, &configData->rules);
    }

private:
    static inline void fillInNetworkData(const std::string& configFile,
                                         ConfigData::Network* network)
    {
        network->interfaceNames.emplace_back("lo");

        network->interfaceCommands.emplace_back(
            "/bin/echo \"[MOCK] Interface command 1\n\" >> " + configFile);
        network->interfaceCommands.emplace_back(
            "/bin/echo \"[MOCK] Interface command 2\n\" >> " + configFile);

        network->layerCommands.emplace_back(
            ConfigData::Network::LayerCommand {configFile, "[MOCK] Layer: value\n"});
    }

    static inline void fillInRulesData(const std::string& configFile,
                                       std::vector<ConfigData::Rule>* rules)
    {
        std::vector<std::string> rule1Commands
            = {"/bin/echo \"[MOCK] Rule 1: command 1\n\" >> " + configFile,
               "/bin/echo \"[MOCK] Rule 1: command 2\n\" >> " + configFile};
        rules->emplace_back(ConfigData::Rule({"Rule 1", rule1Commands}));

        std::vector<std::string> rule2Commands
            = {"/bin/echo \"[MOCK] Rule 2: command 1\n\" >> " + configFile};
        rules->emplace_back(ConfigData::Rule({"Rule 2", rule2Commands}));
    }
};

Config::Config(const ILogger& logger)
    : m_internal(std::make_unique<Internal>(logger))
{}

Config::~Config() = default;

std::unique_ptr<ConfigData> Config::load(const std::string& configFile) const
{
    std::unique_ptr<ConfigData> configData = std::make_unique<ConfigData>();

    m_internal->logger.debug("Fill in config data");
    Internal::fillInConfigData(configFile, configData);

    return configData;
}
