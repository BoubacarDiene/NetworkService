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

#ifndef __UTILS_COMMAND_PARSER_H__
#define __UTILS_COMMAND_PARSER_H__

#include <memory>

#include "service/plugins/ILogger.h"

namespace utils::command {

/**
 * @class Parser Parser.h "utils/command/Parser.h"
 * @ingroup Helper
 *
 * @brief A helper class to parse a string representing a command so
 *        as to create a real command that can be passed to @ref Executor.
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
class Parser {

public:
    /**
     * @struct Command
     *
     * @brief Represents a shell command to execute
     *
     * @see Executor
     */
    struct Command {
        char* pathname; /**< Absolute path to the program */
        int argc;       /**< The number of elements in argv */
        char** argv;    /**< Arguments to pass to the program */
    };

    /**
     * @struct CommandDeleter
     *
     * @brief Custom deleter associated to the created command
     */
    struct CommandDeleter {
        void operator()(Command* command);
    };

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
    explicit Parser(const service::plugins::logger::ILogger& logger);

    /** Class destructor */
    ~Parser();

    /** Class copy constructor */
    Parser(const Parser&) = delete;

    /** Class copy-assignment operator */
    Parser& operator=(const Parser&) = delete;

    /** Class move constructor */
    Parser(Parser&&) = delete;

    /** Class move-assignment operator */
    Parser& operator=(Parser&&) = delete;

    /**
     * @brief Parse the given string to create a command
     *
     * @param commandToParse The shell command to parse
     * @param delimiter      The delimiter that shows how to split the input
     *                       string into substrings
     *
     * @return A command that can be provided to @Executor
     *
     * @see Command
     */
    [[nodiscard]] std::unique_ptr<Command, CommandDeleter>
        parse(const std::string& commandToParse, char delimiter = ' ') const;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
