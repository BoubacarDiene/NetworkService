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

#ifndef __PLUGINS_LOGGER_LOGGER_H__
#define __PLUGINS_LOGGER_LOGGER_H__

#include <memory>

#include "service/plugins/ILogger.h"

namespace service::plugins::logger {

/**
 * @class Logger Logger.h "plugins/logger/Logger.h"
 * @ingroup Implementation
 *
 * @brief Print logs to help understanding what the service is doing
 *
 * This class is the "low level class" that implements @ref ILogger.h
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
class Logger : public ILogger {

public:
    /** Class constructor */
    explicit Logger();

    /**
     * Class destructor
     *
     * @note The override specifier aims at making the compiler warn if the
     *       base class's destructor is not virtual.
     */
    ~Logger() override;

    /** Class copy constructor */
    Logger(const Logger&) = delete;

    /** Class copy-assignment operator */
    Logger& operator=(const Logger&) = delete;

    /** Class move constructor */
    Logger(Logger&&) = delete;

    /** Class move-assignment operator */
    Logger& operator=(Logger&&) = delete;

    /**
     * @brief Print debug-level logs
     *
     * @param message The log message to print
     */
    void debug(const std::string& message) const override;

    /**
     * @brief Print info-level logs
     *
     * @param message The log message to print
     */
    void info(const std::string& message) const override;

    /**
     * @brief Print warning-level logs
     *
     * @param message The log message to print
     */
    void warn(const std::string& message) const override;

    /**
     * @brief Print error-level logs
     *
     * @param message The log message to print
     */
    void error(const std::string& message) const override;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
