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
