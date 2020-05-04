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

#include "utils/command/Executor.h"
#include "utils/command/Parser.h"

#include "Rule.h"

using namespace service::plugins::firewall;
using namespace service::plugins::logger;
using namespace utils::command;

struct Rule::Internal {
    const ILogger& logger;

    const std::string& name;
    const std::vector<std::string>& commands;

    /* const to make these objects non-copyable, non-movable and
     * non-resettable */
    const std::unique_ptr<Executor> executor;
    const std::unique_ptr<Parser> parser;

    explicit Internal(const ILogger& providedLogger,
                      const std::string& providedName,
                      const std::vector<std::string>& providedCommands)
        : logger(providedLogger),
          name(providedName),
          commands(providedCommands),
          executor(std::make_unique<Executor>(providedLogger)),
          parser(std::make_unique<Parser>(providedLogger))
    {}
};

Rule::Rule(const ILogger& logger,
           const std::string& name,
           const std::vector<std::string>& commands)
    : m_internal(std::make_unique<Internal>(logger, name, commands))
{}

Rule::~Rule() = default;

void Rule::applyCommands() const
{
    for (const std::string& command : m_internal->commands) {
        const std::unique_ptr<Parser::Command, Parser::CommandDeleter>&
            parsedCommand
            = m_internal->parser->parse(command);

        m_internal->logger.debug(m_internal->name
                                 + " - Apply command: " + command);
        m_internal->executor->exec(
            parsedCommand->pathname, parsedCommand->argv, nullptr);
    }
}
