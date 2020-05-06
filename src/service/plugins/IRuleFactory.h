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

#ifndef __SERVICE_PLUGINS_IRULE_FACTORY_H__
#define __SERVICE_PLUGINS_IRULE_FACTORY_H__

#include <memory>
#include <string>
#include <vector>

#include "IRule.h"

namespace service::plugins::firewall {

/**
 * @interface IRuleFactory IRuleFactory.h "service/plugins/IRuleFactory.h"
 * @ingroup Abstraction
 *
 * @brief A factory class to help creating rules thus hiding low level
 *        details to the core service.
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
class IRuleFactory {

public:
    /** Class constructor */
    IRuleFactory() = default;

    /** Class destructor made virtual because it is used as base class by
     *  derived classes in firewall plugin */
    virtual ~IRuleFactory() = default;

    /** Class copy constructor */
    IRuleFactory(const IRuleFactory&) = delete;

    /** Class copy-assignment operator */
    IRuleFactory& operator=(const IRuleFactory&) = delete;

    /** Class move constructor */
    IRuleFactory(IRuleFactory&&) = delete;

    /** Class move-assignment operator */
    IRuleFactory& operator=(IRuleFactory&&) = delete;

    /**
     * @brief Create a firewalling rule
     *
     * Create a firewall rule based on informations provided by user in the
     * configuration file.
     *
     * @param name     The name of the rule (For internal usage: logging, ...)
     * @param commands The list of shell commands that compose the rule
     *
     * @return The created rule
     */
    [[nodiscard]] virtual std::unique_ptr<IRule>
        createRule(const std::string& name,
                   const std::vector<std::string>& commands) const = 0;
};

}

#endif
