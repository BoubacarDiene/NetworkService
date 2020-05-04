//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
//                                                                          //
//  Copyright © 2020 Boubacar DIENE                                         //
//                                                                          //
//  This file is part of NetworkService project.                            //
//                                                                          //
//  NetworkService is free software: you can redistribute it and/or modify  //
//  it under the terms of the GNU General Public License as published by    //
//  the Free Software Foundation, either version 2 of the License, or       //
//  (at your option) any later version.                                     //
//                                                                          //
//  NetworkService is distributed in the hope that it will be useful,       //
//  but WITHOUT ANY WARRANTY; without even the implied warranty of          //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           //
//  GNU General Public License for more details.                            //
//                                                                          //
//  You should have received a copy of the GNU General Public License       //
//  along with NetworkService. If not, see <http://www.gnu.org/licenses/>   //
//  or write to the Free Software Foundation, Inc., 51 Franklin Street,     //
//  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.           //
//                                                                          //
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//

#ifndef __PLUGINS_FIREWALL_RULE_H__
#define __PLUGINS_FIREWALL_RULE_H__

#include <memory>

#include "service/plugins/ILogger.h"
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
     * @param logger  Logger object to print some useful logs
     * @param name    A name for the rule mainly used in logs messages to
     *                help identifying rules
     * @param commands The list of shell commands that compose the rule
     *
     * @note Instead of allowing this class to have its own copy of the logger
     *       object (shared_ptr), logger is made a non-const reference to a
     *       const object for better performances. The counterpart is that the
     *       logger object must (obviously) be kept valid by Main.cpp where it
     *       is created until this class is no longer used.
     */
    explicit Rule(const service::plugins::logger::ILogger& logger,
                  const std::string& name,
                  const std::vector<std::string>& commands);

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
