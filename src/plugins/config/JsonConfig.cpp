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

#include <fstream>
#include <json.hpp>

#include "Config.h"

#define JSON_ALIAS_NETWORK            "network"
#define JSON_ALIAS_INTERFACE_NAMES    "interfaceNames"
#define JSON_ALIAS_INTERFACE_COMMANDS "interfaceCommands"
#define JSON_ALIAS_LAYER_COMMANDS     "layerCommands"
#define JSON_ALIAS_PATHNAME           "pathname"
#define JSON_ALIAS_VALUE              "value"
#define JSON_ALIAS_COMMANDS           "commands"
#define JSON_ALIAS_RULES              "rules"
#define JSON_ALIAS_NAME               "name"

using json = nlohmann::json;

using namespace service::plugins::config;
using namespace service::plugins::logger;

// See https://github.com/nlohmann/json#conversion-from-stl-containers
// to understand a function named from_json has to be defined in this
// namespace
namespace nlohmann {

static void from_json(const json& jsonObject, ConfigData& config)
{
    // Fill in network
    const auto& network = jsonObject.at(JSON_ALIAS_NETWORK);

    for (const auto& interface : network.at(JSON_ALIAS_INTERFACE_NAMES)) {
        config.network.interfaceNames.emplace_back(interface);
    }

    for (const auto& interfaceCommand : network.at(JSON_ALIAS_INTERFACE_COMMANDS)) {
        config.network.interfaceCommands.emplace_back(interfaceCommand);
    }

    for (const auto& layerCommand : network.at(JSON_ALIAS_LAYER_COMMANDS)) {
        config.network.layerCommands.emplace_back(
            ConfigData::Network::LayerCommand {layerCommand.at(JSON_ALIAS_PATHNAME),
                                               layerCommand.at(JSON_ALIAS_VALUE)});
    }

    // Fill in rules
    const auto& rules = jsonObject.at(JSON_ALIAS_RULES);

    for (const auto& rule : rules) {
        ConfigData::Rule tempRule;
        for (const auto& command : rule.at(JSON_ALIAS_COMMANDS)) {
            tempRule.commands.emplace_back(command);
        }
        rule.at(JSON_ALIAS_NAME).get_to(tempRule.name);
        config.rules.emplace_back(tempRule);
    }
}

}

struct Config::Internal {
    const ILogger& logger;

    explicit Internal(const ILogger& providedLogger) : logger(providedLogger) {}

    static std::unique_ptr<ConfigData>
        getConfigDataFrom(const std::string& configFile)
    {
        json jsonObject;
        std::ifstream(configFile) >> jsonObject;

        return std::make_unique<ConfigData>(jsonObject.get<ConfigData>());
    }
};

Config::Config(const ILogger& logger)
    : m_internal(std::make_unique<Internal>(logger))
{}

Config::~Config() = default;

std::unique_ptr<ConfigData> Config::load(const std::string& configFile) const
{
    m_internal->logger.debug("Read config from: " + configFile);
    return Internal::getConfigDataFrom(configFile);
}
