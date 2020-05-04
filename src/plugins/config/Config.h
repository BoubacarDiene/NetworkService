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

#ifndef __PLUGINS_CONFIG_CONFIG_H__
#define __PLUGINS_CONFIG_CONFIG_H__

#include <memory>

#include "service/plugins/IConfig.h"
#include "service/plugins/ILogger.h"

namespace service::plugins::config {

/**
 * @class Config Config.h "plugins/config/Config.h"
 * @ingroup Implementation
 *
 * @brief Load the provided configuration file
 *
 * This class is the "low level class" that implements @ref IConfig.h
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
class Config : public IConfig {

public:
    /**
     * Class constructor
     *
     * @param logger Logger object to print some useful logs while loading
     *        the configuration file
     *
     * @note Instead of allowing this class to have its own copy of the logger
     *       object (shared_ptr), logger is made a non-const reference to a
     *       const object for better performances. The counterpart is that the
     *       logger object must (obviously) be kept valid by Main.cpp where it
     *       is created until this class is no longer used.
     */
    explicit Config(const service::plugins::logger::ILogger& logger);

    /**
     * Class destructor
     *
     * @note The override specifier aims at making the compiler warn if the
     *       base class's destructor is not virtual.
     */
    ~Config() override;

    /** Class copy constructor */
    Config(const Config&) = delete;

    /** Class copy-assignment operator */
    Config& operator=(const Config&) = delete;

    /** Class move constructor */
    Config(Config&&) = delete;

    /** Class move-assignment operator */
    Config& operator=(Config&&) = delete;

    /**
     * @brief Load the configuration file into @ref @ConfigData
     *
     * @param configFile Configuration file to load
     *
     * @return A data structure containing all the informations retrieved
     *         from the configuration file
     *
     * @see ConfigData
     */
    [[nodiscard]] std::unique_ptr<ConfigData>
        load(const std::string& configFile) const override;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
