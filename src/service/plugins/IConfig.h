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

#ifndef __SERVICE_PLUGINS_ICONFIG_H__
#define __SERVICE_PLUGINS_ICONFIG_H__

#include <memory>

#include "IConfigData.h"

namespace service::plugins::config {

/**
 * @interface IConfig IConfig.h "service/plugins/IConfig.h"
 * @ingroup Abstraction
 *
 * @brief Load the configuration used by the service to set up the network
 *
 * This class is the high level interface that must be implemented by config
 * plugin. The core service depends on it and not on its implementation(s) to
 * respect the Dependency Inversion Principle. It is possible to retrieve the
 * network configuration in various means that just need to be implemented if
 * required:
 *
 * - From a JSON file (.json)
 * - From a YAML file (.yaml)
 * - From a XML file (.xml)
 * - From a Text file (.txt)
 * - From a database (sqlite, ...)
 * - etc.
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
class IConfig {

public:
    /** Class constructor */
    IConfig() = default;

    /** Class destructor made virtual because it is used as base class by
     *  derived classes in config plugin */
    virtual ~IConfig() = default;

    /** Class copy constructor */
    IConfig(const IConfig&) = delete;

    /** Class copy-assignment operator */
    IConfig& operator=(const IConfig&) = delete;

    /** Class move constructor */
    IConfig(IConfig&&) = delete;

    /** Class move-assignment operator */
    IConfig& operator=(IConfig&&) = delete;

    /**
     * @brief Load the the provided configuration file into memory
     *
     * @param configFile Configuration file to load
     *
     * @return A data structure containing all the informations retrieved
     *         from the configuration file
     *
     * @see ConfigData
     */
    [[nodiscard]] virtual std::unique_ptr<ConfigData>
        load(const std::string& configFile) const = 0;
};

}

#endif
