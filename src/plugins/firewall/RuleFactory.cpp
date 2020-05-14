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

#include "RuleFactory.h"
#include "Rule.h"

using namespace service::plugins::firewall;
using namespace service::plugins::logger;

struct RuleFactory::Internal {
    const ILogger& logger;
    const utils::command::IExecutor& executor;

    explicit Internal(const ILogger& providedLogger,
                      const utils::command::IExecutor& providedExecutor)
        : logger(providedLogger),
          executor(providedExecutor)
    {}
};

RuleFactory::RuleFactory(const ILogger& logger,
                         const utils::command::IExecutor& executor)
    : m_internal(std::make_unique<Internal>(logger, executor))
{}

RuleFactory::~RuleFactory() = default;

std::unique_ptr<IRule>
    RuleFactory::createRule(const std::string& name,
                            const std::vector<std::string>& commands) const
{
    m_internal->logger.debug("Create rule: " + name);
    return std::make_unique<Rule>(
        m_internal->logger, name, commands, m_internal->executor);
}
