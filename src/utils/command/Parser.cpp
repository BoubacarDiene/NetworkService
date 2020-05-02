#include <cstring>
#include <sstream>
#include <vector>

#include "Parser.h"

using namespace service::plugins::logger;
using namespace utils::command;

struct Parser::Internal {
    const ILogger& logger;

    explicit Internal(const ILogger& providedLogger) : logger(providedLogger) {}

    /* Provided "delimiter", return an array of strings resulting from the
     * splitting of "stringToSplit" into substrings */
    std::vector<std::string> splitString(const std::string& stringToSplit,
                                         char delimiter = ' ')
    {
        std::vector<std::string> results;
        std::string substring;

        std::istringstream iss(stringToSplit);
        while (std::getline(iss, substring, delimiter)) {
            logger.debug("Substring: " + substring);
            results.push_back(substring);
        }

        return results;
    }
};

void Parser::CommandDeleter::operator()(Command* command)
{
    delete[] command->pathname;

    for (int index = 0; index < command->argc; ++index) {
        delete[] command->argv[index];
    }

    delete[] command->argv;
    delete command;
}

Parser::Parser(const ILogger& logger)
    : m_internal(std::make_unique<Internal>(logger))
{}

Parser::~Parser() = default;

std::unique_ptr<Parser::Command, Parser::CommandDeleter>
    Parser::parse(const std::string& commandToParse, char delimiter) const
{
    m_internal->logger.debug("Split command into substrings");
    std::vector<std::string> results
        = m_internal->splitString(commandToParse, delimiter);

    std::size_t nbResults     = results.size();
    std::size_t oneResultSize = 0llu;

    m_internal->logger.debug("Generate parsed command");
    std::unique_ptr<Parser::Command, Parser::CommandDeleter> command(
        new Command, CommandDeleter());

    /* pathname is the absolute path to command to execute
     * It is always saved as the first element of the array */
    oneResultSize = results[0].size();

    command->pathname = new char[oneResultSize + 1]();
    strncpy(command->pathname, results[0].c_str(), oneResultSize);

    m_internal->logger.debug("Pathname: " + std::string(command->pathname));

    /* argv contains program name (i.e pathname) + arguments */
    command->argc = static_cast<int>(nbResults);
    command->argv = new char*[static_cast<std::size_t>(command->argc)
                              + 1lu](); // +1 because NULL-terminated

    for (std::size_t index = 0; index < nbResults; ++index) {
        oneResultSize = results[index].size();

        command->argv[index] = new char[oneResultSize + 1]();
        strncpy(command->argv[index], results[index].c_str(), oneResultSize);

        m_internal->logger.debug(std::string("argv[") + std::to_string(index)
                                 + "]: " + command->argv[index]);
    }

    return command;
}
