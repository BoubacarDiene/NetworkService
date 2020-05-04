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

#include <algorithm>
#include <array>
#include <iterator>
#include <stdexcept>
#include <sys/stat.h>

#include "plugins/config/json/JsonReader.h"
#include "plugins/config/mock/MockReader.h"

#include "Config.h"

using namespace service::plugins::logger;
using namespace service::plugins::config;
using namespace service::plugins::config::reader;

struct Config::Internal {
    const ILogger& logger;
    const Source& dataSource;

    explicit Internal(const ILogger& providedLogger,
                      const Source& providedDataSource)
        : logger(providedLogger),
          dataSource(providedDataSource)
    {}
};

Config::Config(const ILogger& logger, const Source& dataSource)
    : m_internal(std::make_unique<Internal>(logger, dataSource))
{}

Config::~Config() = default;

std::unique_ptr<ConfigData> Config::load(const std::string& configFile) const
{
    /* Check if config file exists */
    struct stat buffer;
    if (stat(configFile.c_str(), &buffer) != 0) {
        throw std::invalid_argument("Config file not found: " + configFile);
    }

    /* Check if data source is valid */
    const std::array validSources = {Source::JSON, Source::MOCK, Source::YAML};
    const Source* const checkResult = std::find(std::begin(validSources),
                                                std::end(validSources),
                                                m_internal->dataSource);
    if (checkResult == std::end(validSources)) {
        throw std::invalid_argument("Wrong data source");
    }

    /* Initialize config using the correct handler */
    std::unique_ptr<IReader> reader = nullptr;

    switch (m_internal->dataSource) {
    case Source::JSON:
        reader = std::make_unique<JsonReader>(m_internal->logger);
        break;

    case Source::MOCK:
        reader = std::make_unique<MockReader>(m_internal->logger);
        break;

    case Source::YAML:
        throw std::runtime_error("Data source type not supported yet");
        break;

    default:
        break; // Intentionally left empty
    }

    return reader->readFrom(configFile);
}
