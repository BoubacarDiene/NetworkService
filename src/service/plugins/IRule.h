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

#ifndef __SERVICE_PLUGINS_IRULE_H__
#define __SERVICE_PLUGINS_IRULE_H__

#include <string>
#include <vector>

namespace service::plugins::firewall {

/**
 * @interface IRule IRule.h "service/plugins/IRule.h"
 * @ingroup Abstraction
 *
 * @brief Represents a single firewall rule
 *
 * This class is the high level interface that must be implemented in firewall
 * plugin. The core service depends on it and not on its implementation(s) to
 * respect the Dependency Inversion Principle. Firewalling is made possible by
 * a set of rules.
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
class IRule {

public:
    /** Class constructor */
    IRule() = default;

    /** Class destructor made virtual because it is used as base class by
     *  derived classes in firewall plugin */
    virtual ~IRule() = default;

    /** Class copy constructor */
    IRule(const IRule&) = delete;

    /** Class copy-assignment operator */
    IRule& operator=(const IRule&) = delete;

    /** Class move constructor */
    IRule(IRule&&) = delete;

    /** Class move-assignment operator */
    IRule& operator=(IRule&&) = delete;

    /**
     * @brief Apply all commands in this rule
     *
     * It's about iterating the commands which are shell commands and apply
     * them one by one. To do so, one can rely on helper classes that can
     * execute shell command securely.
     */
    virtual void applyCommands() const = 0;
};

}

#endif
