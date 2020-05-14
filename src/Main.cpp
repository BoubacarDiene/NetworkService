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

#include <CLI11.hpp>
#include <cstdlib>

#include "plugins/config/Config.h"
#include "plugins/firewall/RuleFactory.h"
#include "plugins/logger/Logger.h"
#include "plugins/network/Network.h"

#include "service/NetworkService.h"

#include "utils/command/executor/Executor.h"
#include "utils/command/executor/osal/Linux.h"

#include "utils/file/reader/Reader.h"
#include "utils/file/writer/Writer.h"

using namespace service;
using namespace service::plugins::config;
using namespace service::plugins::firewall;
using namespace service::plugins::logger;
using namespace service::plugins::network;

using namespace utils::command;
using namespace utils::command::osal;
using namespace utils::file;

static inline std::string parseCommandLine(int argc, char** argv)
{
    CLI::App app(" ");

    constexpr unsigned int columnWidth = 68u;
    app.get_formatter()->column_width(columnWidth);
    app.get_formatter()->label("REQUIRED", "(REQUIRED)");

    std::string configFile;

    app.add_option("-c", configFile, "Path to configuration file")
        ->required()
        ->check(CLI::ExistingFile);

    try {
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError& e) {
        app.exit(e);
        std::exit(EXIT_FAILURE);
    }

    return configFile;
}

int main(int argc, char** argv)
{
    std::string configFile = parseCommandLine(argc, argv);

    /* Initialize and inject dependencies */
    Logger logger           = Logger();
    Linux osal              = Linux(logger);
    Executor executor       = Executor(logger, osal);
    Writer writer           = Writer(logger);
    Reader reader           = Reader(logger);
    Network network         = Network(logger, executor, writer);
    RuleFactory ruleFactory = RuleFactory(logger, executor);
    Config config           = Config(logger, reader);

    NetworkService::NetworkServiceParams networkServiceParams(
        {logger, config, network, ruleFactory});
    NetworkService networkService(networkServiceParams);

    /* Set up the network and firewall based on provided file */
    return networkService.applyConfig(configFile);
}
