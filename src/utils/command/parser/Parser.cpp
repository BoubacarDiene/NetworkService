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

#include <cstring>
#include <sstream>
#include <vector>

#include "Parser.h"

using namespace utils::command;

namespace {

/* Provided "delimiter", return an array of strings resulting from the
 * splitting of "stringToSplit" into substrings */
std::vector<std::string> splitString(const std::string& stringToSplit,
                                     char delimiter = ' ')
{
    std::vector<std::string> results;
    std::string substring;

    std::istringstream iss(stringToSplit);
    while (std::getline(iss, substring, delimiter)) {
        results.push_back(substring);
    }

    return results;
}

}

void Parser::CommandDeleter::operator()(Command* command)
{
    delete[] command->pathname;

    for (int index = 0; index < command->argc; ++index) {
        delete[] command->argv[index];
    }

    delete[] command->argv;
    delete command;
}

std::unique_ptr<Parser::Command, Parser::CommandDeleter>
    Parser::parse(const std::string& commandToParse, char delimiter)
{
    /* Split command into substrings */
    std::vector<std::string> results = splitString(commandToParse, delimiter);

    std::size_t nbResults     = results.size();
    std::size_t oneResultSize = 0llu;

    /* Generate parsed command */
    std::unique_ptr<Parser::Command, Parser::CommandDeleter> command(
        new Command, CommandDeleter());

    /* pathname is the absolute path to command to execute
     * It is always saved as the first element of the array */
    oneResultSize = results[0].size();

    command->pathname = new char[oneResultSize + 1]();
    strncpy(command->pathname, results[0].c_str(), oneResultSize);

    /* argv contains program name (i.e pathname) + arguments */
    command->argc = static_cast<int>(nbResults);
    command->argv = new char*[static_cast<std::size_t>(command->argc)
                              + 1lu](); // +1 because NULL-terminated

    for (std::size_t index = 0; index < nbResults; ++index) {
        oneResultSize = results[index].size();

        command->argv[index] = new char[oneResultSize + 1]();
        strncpy(command->argv[index], results[index].c_str(), oneResultSize);
    }

    return command;
}
