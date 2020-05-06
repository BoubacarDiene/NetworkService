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
