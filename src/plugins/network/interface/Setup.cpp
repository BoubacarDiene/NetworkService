#include "utils/command/Executor.h"
#include "utils/command/Parser.h"

#include "Setup.h"

using namespace service::plugins::logger;
using namespace service::plugins::network::interface;
using namespace utils::command;

struct Interface::Internal {
    const ILogger& logger;

    /* const to make these objects non-copyable, non-movable and
     * non-resettable */
    const std::unique_ptr<Executor> executor;
    const std::unique_ptr<Parser> parser;

    explicit Internal(const ILogger& providedLogger)
        : logger(providedLogger),
          executor(std::make_unique<Executor>(providedLogger)),
          parser(std::make_unique<Parser>(providedLogger))
    {}
};

Interface::Interface(const ILogger& logger)
    : m_internal(std::make_unique<Internal>(logger))
{}

Interface::~Interface() = default;

void Interface::applyCommand(const std::string& command) const
{
    const auto& parsedCommand = m_internal->parser->parse(command);

    m_internal->logger.debug("Apply command: " + command);
    m_internal->executor->exec(
        parsedCommand->pathname, parsedCommand->argv, nullptr);
}
