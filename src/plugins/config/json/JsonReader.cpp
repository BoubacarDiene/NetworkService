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

#include <fstream>
#include <json.hpp>

#include "JsonReader.h"

using json = nlohmann::json;

using namespace service::plugins::config;
using namespace service::plugins::config::reader;
using namespace service::plugins::logger;

// See https://github.com/nlohmann/json#conversion-from-stl-containers
// to understand a function named from_json has to be defined in this
// namespace
namespace nlohmann {

static void from_json(const json& jsonObject, ConfigData& config)
{
    // Fill in network
    const auto& network = jsonObject.at("network");

    for (const auto& interface : network.at("interfaceNames")) {
        config.network.interfaceNames.emplace_back(interface);
    }

    for (const auto& interfaceCommand : network.at("interfaceCommands")) {
        config.network.interfaceCommands.emplace_back(interfaceCommand);
    }

    for (const auto& layerCommand : network.at("layerCommands")) {
        config.network.layerCommands.emplace_back(
            ConfigData::Network::LayerCommand {layerCommand.at("pathname"),
                                               layerCommand.at("value")});
    }

    // Fill in rules
    const auto& rules = jsonObject.at("rules");

    for (const auto& rule : rules) {
        ConfigData::Rule tempRule;
        for (const auto& command : rule.at("commands")) {
            tempRule.commands.emplace_back(command);
        }
        rule.at("name").get_to(tempRule.name);
        config.rules.emplace_back(tempRule);
    }
}

}

struct JsonReader::Internal {
    const ILogger& logger;

    explicit Internal(const ILogger& providedLogger) : logger(providedLogger) {}

    static std::unique_ptr<ConfigData>
        getConfigDataFrom(const std::string& configFile)
    {
        json jsonObject;
        std::ifstream(configFile) >> jsonObject;

        return std::make_unique<ConfigData>(jsonObject.get<ConfigData>());
    }

private:
};

JsonReader::JsonReader(const ILogger& logger)
    : m_internal(std::make_unique<Internal>(logger))
{}

JsonReader::~JsonReader() = default;

std::unique_ptr<ConfigData>
    JsonReader::readFrom(const std::string& configFile) const
{
    m_internal->logger.debug("Read config from: " + configFile);
    return Internal::getConfigDataFrom(configFile);
}
