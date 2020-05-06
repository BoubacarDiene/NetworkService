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
