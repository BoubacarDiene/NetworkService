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
