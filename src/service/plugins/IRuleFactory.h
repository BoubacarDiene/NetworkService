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
