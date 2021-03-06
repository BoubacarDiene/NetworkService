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

#include "utils/file/reader/Reader.h"

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
using namespace utils::file;

// See https://github.com/nlohmann/json#conversion-from-stl-containers
// to understand a function named from_json has to be defined in this
// namespace
namespace nlohmann {

static void from_json(const json& jsonObject, ConfigData& config)
{
    const auto& network = jsonObject.at(JSON_ALIAS_NETWORK);

    // "interfaceNames" section
    for (const auto& interface : network.at(JSON_ALIAS_INTERFACE_NAMES)) {
        config.network.interfaceNames.emplace_back(interface);
    }

    // "interfaceCommands" section
    for (const auto& interfaceCommand : network.at(JSON_ALIAS_INTERFACE_COMMANDS)) {
        config.network.interfaceCommands.emplace_back(interfaceCommand);
    }

    try {
        // "layerCommands" section
        for (const auto& layerCommand : network.at(JSON_ALIAS_LAYER_COMMANDS)) {
            config.network.layerCommands.emplace_back(
                ConfigData::Network::LayerCommand {
                    layerCommand.at(JSON_ALIAS_PATHNAME),
                    layerCommand.at(JSON_ALIAS_VALUE)});
        }

        // "rules" section
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
    catch (const json::out_of_range& e) {
    }
}

}

struct Config::Internal {
    const IReader& reader;

    explicit Internal(const IReader& providedReader) : reader(providedReader) {}

    [[nodiscard]] std::unique_ptr<ConfigData>
        getConfigDataFrom(const std::string& configFile) const
    {
        std::string result;
        std::ifstream stream(configFile);
        reader.readFromStream(stream, result);

        json jsonObject = json::parse(result);
        return std::make_unique<ConfigData>(jsonObject.get<ConfigData>());
    }
};

Config::Config(const IReader& reader)
    : m_internal(std::make_unique<Internal>(reader))
{}

Config::~Config() = default;

std::unique_ptr<ConfigData> Config::load(const std::string& configFile) const
{
    return m_internal->getConfigDataFrom(configFile);
}
