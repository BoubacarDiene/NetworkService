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

#include "utils/command/executor/IExecutor.h"
#include "utils/command/parser/Parser.h"

#include "Rule.h"

using namespace service::plugins::firewall;
using namespace utils::command;

struct Rule::Internal {
    const IExecutor& executor;

    const std::string& name;
    const std::vector<std::string>& commands;

    explicit Internal(const IExecutor& providedExecutor,
                      const std::string& providedName,
                      const std::vector<std::string>& providedCommands)
        : executor(providedExecutor),
          name(providedName),
          commands(providedCommands)
    {}
};

Rule::Rule(const std::string& name,
           const std::vector<std::string>& commands,
           const IExecutor& executor)
    : m_internal(std::make_unique<Internal>(executor, name, commands))
{}

Rule::~Rule() = default;

void Rule::applyCommands() const
{
    for (const std::string& command : m_internal->commands) {
        const std::unique_ptr<Parser::Command, Parser::CommandDeleter>& parsedCommand
            = Parser::parse(command);

        const IExecutor::ProgramParams params
            = {parsedCommand->pathname, parsedCommand->argv, nullptr};
        m_internal->executor.executeProgram(params);
    }
}
