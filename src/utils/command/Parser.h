#ifndef __UTILS_COMMAND_PARSER_H__
#define __UTILS_COMMAND_PARSER_H__

#include <memory>

#include "service/plugins/ILogger.h"

namespace utils::command {

class Parser {

public:
    struct Command {
        char* pathname;
        int argc;
        char** argv;
    };

    struct CommandDeleter {
        void operator()(Command* command);
    };

    explicit Parser(const service::plugins::logger::ILogger& logger);

    ~Parser();

    Parser(const Parser&) = delete;

    Parser& operator=(const Parser&) = delete;

    Parser(Parser&&) = delete;

    Parser& operator=(Parser&&) = delete;

    [[nodiscard]] std::unique_ptr<Command, CommandDeleter>
        parse(const std::string& commandToParse, char delimiter = ' ') const;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
