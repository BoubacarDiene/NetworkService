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

namespace utils::command {

/**
 * @class Parser Parser.h "utils/command/parser/Parser.h"
 * @ingroup Helper
 *
 * @brief A helper class to parse a string representing a command so
 *        as to create a real command that can be passed to @ref IExecutor.
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
     * @see IExecutor
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
     * @brief Parse the given string to create a command
     *
     * @param commandToParse The shell command to parse
     * @param delimiter      The delimiter that shows how to split the input
     *                       string into substrings
     *
     * @return A command that can be provided to @ref IExecutor
     *
     * @see Command
     */
    [[nodiscard]] static std::unique_ptr<Command, CommandDeleter>
        parse(const std::string& commandToParse, char delimiter = ' ');
};

}

#endif
