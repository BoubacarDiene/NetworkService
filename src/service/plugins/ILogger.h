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

#ifndef __SERVICE_PLUGINS_ILOGGER_H__
#define __SERVICE_PLUGINS_ILOGGER_H__

#include <string>

namespace service::plugins::logger {

/**
 * @interface ILogger ILogger.h "service/plugins/ILogger.h"
 * @ingroup Abstraction
 *
 * @brief Print logs to help understanding what the service is doing
 *
 * This class is the high level interface that must be implemented by logger
 * plugin. The core service depends on it and not on its implementation(s) to
 * respect the Dependency Inversion Principle. The logger plugin is thus free
 * to output logs wherever it wants:
 *
 * - Standard output
 * - A text file in the filesystem
 * - A remote server listening to a socket
 * - A local database
 * - etc.
 *
 * @note
 * Copy contructor, copy-assignment operator, move constructor and move
 * assignment operator are defined to be compliant with the "Rule of five".
 *
 * @note
 * One purpose in marking its member functions as const is that a const pointer
 * or reference to ILogger can be used to call them.
 * Thus, one can get "const ILogger*" or "const ILogger&" as input if neither a
 * reset of the logger object, nor becoming an owner of it is necessary. Without
 * this const, one would be forced to use "ILogger*" or "ILogger&" in that case
 * thus have possibility to alter the logger object which is not what is
 * expected.
 *
 * @see https://en.cppreference.com/w/cpp/language/rule_of_three
 *
 * @author Boubacar DIENE <boubacar.diene@gmail.com>
 * @date April 2020
 */
class ILogger {

public:
    /** Class constructor */
    ILogger() = default;

    /** Class destructor made virtual because it is used as base class by
     *  derived classes in logger plugin */
    virtual ~ILogger() = default;

    /** Class copy constructor */
    ILogger(const ILogger&) = delete;

    /** Class copy-assignment operator */
    ILogger& operator=(const ILogger&) = delete;

    /** Class move constructor */
    ILogger(ILogger&&) = delete;

    /** Class move-assignment operator */
    ILogger& operator=(ILogger&&) = delete;

    /**
     * @brief Print debug-level logs.
     *
     * Debug logs are for debugging purposes; reserved to developer.
     * It means that something normal and insignificant happened. Many
     * problems can usually be resolved using a debugger but developers are
     * sometimes stuck with these logs. It can be used to have some more
     * details (compared to INFO) about what the application is doing and
     * better isolate issues especially during the development phase.
     *
     * General usage (not necessarily related to this project but can ease
     *                understanding):
     * - Enter/Exit to/from a function
     *
     * @param message The log message to print
     *
     * @note debug-level logs can be enabled locally on the developer's
     *       computer or in an debug/engineering version.
     */
    virtual void debug(const std::string& message) const = 0;

    /**
     * @brief Print info-level logs.
     *
     * Informational logs the developer would like to see when analyzing an
     * issue. It means that something normal but significant happened. To use
     * this log level effectively, just ask yourself which kind of informations
     * would be useful for diagnosing your application and to quite easily
     * understand what it is doing.
     *
     * General usage (not necessarily related to this project but can ease
     *                understanding):
     * - Version of software in use to be sure it’s the expected one
     * - System life cycle events (started, stopped, ...)
     * - Session life cycle events (logged in, logged out, ...)
     * - Usage information (what are users of currently doing?, ...)
     *
     * @param message The log message to print
     *
     * @note info-level logs can be enabled in a release/production version.
     */
    virtual void info(const std::string& message) const = 0;

    /**
     * @brief Print warning-level logs.
     *
     * Warning logs are for problems that are not necessarily important. They
     * indicate that something unexpected occurred. The application faces a
     * potential problem that does not affect the user experience and also
     * does not prevent it from keeping working. Warning logs are sometimes
     * a sign of an incoming failure.
     *
     * General usage (not necessarily related to this project but can ease
     *                understanding):
     * - Degraded service quality due to a weak Internet connection
     * - More attempts as usual to access resources
     * - File not found but default is used instead
     *
     * @param message The log message to print
     *
     * @note warning-level logs can be enabled in a release/production version.
     */
    virtual void warn(const std::string& message) const = 0;

    /**
     * @brief Print error-level logs.
     *
     * Error logs require a particular attention from the developer. They
     * indicate that something unexpected occurred. The application faces
     * a significant problem that can make it stop working and affect, in
     * some way, the user experience. A fix might be expected.
     *
     * General usage (not necessarily related to this project but can ease
     *                understanding):
     * - An important component is not reachable while it should
     * - Saving/restoring user preferences failed
     * - Views not properly populated due to database connection failure
     *
     * @param message The log message to print
     *
     * @note error-level logs should be enabled in a release/production
     *       version.
     */
    virtual void error(const std::string& message) const = 0;
};

}

#endif
