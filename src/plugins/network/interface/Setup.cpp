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
