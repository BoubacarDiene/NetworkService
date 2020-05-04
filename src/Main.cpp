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

#include <CLI11.hpp>
#include <cstdlib>

#include "plugins/config/Config.h"
#include "plugins/firewall/RuleFactory.h"
#include "plugins/logger/Logger.h"
#include "plugins/network/Network.h"

#include "service/NetworkService.h"

using namespace service;
using namespace service::plugins::config;
using namespace service::plugins::firewall;
using namespace service::plugins::logger;
using namespace service::plugins::network;

struct CommandLine {
    Config::Source dataSource;
    std::string configFile;
};

static CommandLine parseCommandLine(int argc, char** argv)
{
    CLI::App app(" ");

    constexpr unsigned int columnWidth = 68;
    app.get_formatter()->column_width(columnWidth);
    app.get_formatter()->label("REQUIRED", "(REQUIRED)");

    std::map<std::string, Config::Source> text2source {
        {"JSON", Config::Source::JSON},
        {"MOCK", Config::Source::MOCK},
        {"YAML", Config::Source::YAML}};

    CommandLine commandLine;

    app.add_option("-s", commandLine.dataSource, "Source of network commands")
        ->required()
        ->transform(CLI::CheckedTransformer(text2source, CLI::ignore_case));

    app.add_option("-c", commandLine.configFile, "Path to configuration file")
        ->required()
        ->check(CLI::ExistingFile);

    try {
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError& e) {
        app.exit(e);
        std::exit(EXIT_FAILURE);
    }

    return commandLine;
}

int main(int argc, char** argv)
{
    CommandLine commandLine    = parseCommandLine(argc, argv);
    Config::Source& dataSource = commandLine.dataSource;
    std::string& configFile    = commandLine.configFile;

    /* Initialize and inject dependencies */
    std::shared_ptr<ILogger> logger = std::make_shared<Logger>();
    std::unique_ptr<IConfig> config
        = std::make_unique<Config>(*logger, dataSource);
    std::unique_ptr<INetwork> network = std::make_unique<Network>(*logger);
    std::unique_ptr<IRuleFactory> ruleFactory
        = std::make_unique<RuleFactory>(*logger);

    NetworkService networkService(
        logger, std::move(config), std::move(network), std::move(ruleFactory));

    /* Apply config */
    return networkService.applyConfig(configFile);
}
