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
