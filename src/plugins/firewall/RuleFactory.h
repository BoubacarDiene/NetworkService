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

#ifndef __PLUGINS_FIREWALL_RULE_FACTORY_H__
#define __PLUGINS_FIREWALL_RULE_FACTORY_H__

#include <memory>

#include "service/plugins/ILogger.h"
#include "service/plugins/IRuleFactory.h"

namespace service::plugins::firewall {

/**
 * @class RuleFactory RuleFactory.h "plugins/firewall/RuleFactory.h"
 * @ingroup Implementation
 *
 * @brief A factory class to help creating firewalling rules
 *
 * This class is the "low level class" that implements @ref IRuleFactory.h
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
class RuleFactory : public IRuleFactory {

public:
    /**
     * Class constructor
     *
     * @param logger Logger object to print some useful logs
     *
     * @note Instead of allowing this class to have its own copy of the logger
     *       object (shared_ptr), logger is made a non-const reference to a
     *       const object for better performances. The counterpart is that the
     *       logger object must (obviously) be kept valid by Main.cpp where it
     *       is created until this class is no longer used.
     */
    explicit RuleFactory(const service::plugins::logger::ILogger& logger);

    /**
     * Class destructor
     *
     * @note The override specifier aims at making the compiler warn if the
     *       base class's destructor is not virtual.
     */
    ~RuleFactory() override;

    /** Class copy constructor */
    RuleFactory(const RuleFactory&) = delete;

    /** Class copy-assignment operator */
    RuleFactory& operator=(const RuleFactory&) = delete;

    /** Class move constructor */
    RuleFactory(RuleFactory&&) = delete;

    /** Class move-assignment operator */
    RuleFactory& operator=(RuleFactory&&) = delete;

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
    [[nodiscard]] std::unique_ptr<IRule>
        createRule(const std::string& name,
                   const std::vector<std::string>& commands) const override;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
