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

#ifndef __UTILS_COMMAND_EXECUTOR_H__
#define __UTILS_COMMAND_EXECUTOR_H__

#include <memory>

#include "service/plugins/ILogger.h"

namespace utils::command {

/**
 * @class Executor Executor.h "utils/command/Executor.h"
 * @ingroup Helper
 *
 * @brief A helper class to execute shell commands securely.
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
class Executor {

public:
    /**
     * @enum Flags
     *
     * @brief Bitmasks to give control on how this class is handling
     *        requests
     */
    enum Flags : unsigned int {
        WAIT_COMMAND = (1u << 0u),    /**< Wait until command is completed */
        RESEED_PRNG  = (1u << 1u),    /**< Re-initialize the Random number
                                       * Generator */
        SANITIZE_FILES  = (1u << 2u), /**< Closed file descriptors, ... */
        DROP_PRIVILEGES = (1u << 3u), /**< Drop the process's privileges */
        ALL = (WAIT_COMMAND | RESEED_PRNG | SANITIZE_FILES | DROP_PRIVILEGES)
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
    explicit Executor(const service::plugins::logger::ILogger& logger);

    /** Class destructor */
    ~Executor();

    /** Class copy constructor */
    Executor(const Executor&) = delete;

    /** Class copy-assignment operator */
    Executor& operator=(const Executor&) = delete;

    /** Class move constructor */
    Executor(Executor&&) = delete;

    /** Class move-assignment operator */
    Executor& operator=(Executor&&) = delete;

    /**
     * @brief Execute the program pointed to by pathname
     *
     * This function performs a fork+execve in a secure way (re-initialize
     * the random number generator, close file descriptors, ...). Except
     * "flags", all input parameters have the same meaning as in execve()
     * manpage.
     *
     * @param pathname Either a binary executable, or a script starting with a
     *                 line of the form: "#! interpreter [optional-arg]"
     * @param argv     An array of argument strings passed to the new program.
     *                 By convention, the first of these strings should contain
     *                 the filename associated with the file being executed.
     * @param envp     An array of strings of the form key=value, which are
     *                 passed as environment to the new program.
     * @param flags    A set of masks of type @ref Flags
     *
     * @see http://man7.org/linux/man-pages/man2/execve.2.html
     */
    void executeProgram(const char* pathname,
              char* const argv[],
              char* const envp[],
              Flags flags = Flags::ALL) const;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
