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

    static void fillInConfigData(std::unique_ptr<ConfigData>& configData)
    {
        fillInNetworkData(&configData->network);
        fillInRulesData(&configData->rules);
    }

private:
    static inline void fillInNetworkData(ConfigData::Network* network)
    {
        network->interfaceNames.emplace_back("lo");

        network->interfaceCommands.emplace_back(
            "/bin/echo \"[FAKE] Interface command 1\n\" >> /dev/null");
        network->interfaceCommands.emplace_back(
            "/bin/echo \"[FAKE] Interface command 2\n\" >> /dev/null");

        network->layerCommands.emplace_back(ConfigData::Network::LayerCommand {
            "/dev/null", "[FAKE] Layer: value\n"});
    }

    static inline void fillInRulesData(std::vector<ConfigData::Rule>* rules)
    {
        std::vector<std::string> rule1Commands
            = {"/bin/echo \"[FAKE] Rule 1: command 1\n\" >> /dev/null",
               "/bin/echo \"[FAKE] Rule 1: command 2\n\" >> /dev/null"};
        rules->emplace_back(ConfigData::Rule({"Rule 1", rule1Commands}));

        std::vector<std::string> rule2Commands
            = {"/bin/echo \"[FAKE] Rule 2: command 1\n\" >> /dev/null"};
        rules->emplace_back(ConfigData::Rule({"Rule 2", rule2Commands}));
    }
};

Config::Config(const ILogger& logger,
               [[maybe_unused]] const utils::file::IReader& reader)
    : m_internal(std::make_unique<Internal>(logger))
{}

Config::~Config() = default;

std::unique_ptr<ConfigData> Config::load([
    [maybe_unused]] const std::string& configFile) const
{
    std::unique_ptr<ConfigData> configData = std::make_unique<ConfigData>();

    m_internal->logger.debug("Fill in config data");
    Internal::fillInConfigData(configData);

    return configData;
}
