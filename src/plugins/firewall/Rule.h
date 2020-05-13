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

#ifndef __PLUGINS_FIREWALL_RULE_H__
#define __PLUGINS_FIREWALL_RULE_H__

#include <memory>

#include "service/plugins/ILogger.h"
#include "utils/command/executor/Executor.h"

#include "service/plugins/IRule.h"

namespace service::plugins::firewall {

/**
 * @class Rule Rule.h "plugins/firewall/Rule.h"
 * @ingroup Implementation
 *
 * @brief Represents a single firewall rule
 *
 * This class is the "low level class" that implements @ref IRule.h
 *
 * @note Copy contructor, copy-assignment operator, move constructor and
 *       move-assignment operator are defined to be compliant with the
 *       "Rule of five"
 *
 * @see https://en.cppreference.com/w/cpp/language/rule_of_three
 *
 * @author Boubacar DIENE <boubacar.diene@gmail.com>
 * @date April 2020
 */
class Rule : public IRule {

public:
    /**
     * Class constructor
     *
     * @param logger   Logger object to print some useful logs
     * @param name     A name for the rule mainly used in logs messages to
     *                 help identifying rules
     * @param commands The list of shell commands that compose the rule
     * @param executor Command executor to use
     *
     * @note Instead of allowing this class to have its own copy of the logger
     *       object (shared_ptr), logger is made a non-const reference to a
     *       const object for better performances. The counterpart is that the
     *       logger object must (obviously) be kept valid by Main.cpp where it
     *       is created until this class is no longer used.
     */
    explicit Rule(const service::plugins::logger::ILogger& logger,
                  const std::string& name,
                  const std::vector<std::string>& commands,
                  const utils::command::Executor& executor);

    /**
     * Class destructor
     *
     * @note The override specifier aims at making the compiler warn if the
     *       base class's destructor is not virtual.
     */
    ~Rule() override;

    /** Class copy constructor */
    Rule(const Rule&) = delete;

    /** Class copy-assignment operator */
    Rule& operator=(const Rule&) = delete;

    /** Class move constructor */
    Rule(Rule&&) = delete;

    /** Class move-assignment operator */
    Rule& operator=(Rule&&) = delete;

    /** Apply all commands in this rule */
    void applyCommands() const override;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
