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

#ifndef __UTILS_COMMAND_IOS_ABSTRACTION_LAYER_H__
#define __UTILS_COMMAND_IOS_ABSTRACTION_LAYER_H__

namespace utils::command {

/**
 * @interface IOsal IOsal.h "utils/command/executor/IOsal.h"
 * @ingroup Helper
 *
 * @brief This class is a high level interface added to ease testability of
 *        component that use @ref Executor. It decouples Excecutor and syscalls
 *        used to handle requests thus behaving like an OS abstraction layer.
 *
 * @note Copy contructor, copy-assignment operator, move constructor and
 *       move-assignment operator are defined to be compliant with the
 *       "Rule of five"
 *
 * @see https://en.cppreference.com/w/cpp/language/rule_of_three
 *
 * @author Boubacar DIENE <boubacar.diene@gmail.com>
 * @date May 2020
 */
class IOsal {

public:
    /**
     * @enum ProcessId
     *
     * @brief An id to inform caller about the current process type
     *        after a new process has been created
     */
    enum ProcessId : unsigned int {
        CHILD  = (1u << 0u), /**< In child process */
        PARENT = (1u << 1u)  /**< In parent process */
    };

    /** Class constructor */
    IOsal() = default;

    /** Class destructor */
    virtual ~IOsal() = default;

    /** Class copy constructor */
    IOsal(const IOsal&) = delete;

    /** Class copy-assignment operator */
    IOsal& operator=(const IOsal&) = delete;

    /** Class move constructor */
    IOsal(IOsal&&) = delete;

    /** Class move-assignment operator */
    IOsal& operator=(IOsal&&) = delete;

    /**
     * @brief creates a new process by duplicating the calling process.
     *
     * It can basically be a wrapper of fork() call in linux.
     *
     * @return An id of type @ref ProcessId
     */
    [[nodiscard]] virtual ProcessId createProcess() const = 0;

    /**
     * @brief Wait for any child process whose process group ID is equal to
     *        that of the calling process.
     *
     * It can basically be a wrapper of waitpid() call in linux with a pid
     * equal to 0.
     */
    virtual void waitChildProcess() const = 0;

    /**
     * @brief Execute the program referred to by pathname
     *
     * It can basically be a wrapper of a exec()-like function.
     * It is expected it does not return unless an error is encountered.
     *
     * @param pathname Either a binary executable, or a script starting with a
     *                 line of the form: "#! interpreter [optional-arg]"
     * @param argv     An array of argument strings passed to the new program.
     *                 By convention, the first of these strings should contain
     *                 the filename associated with the file being executed.
     * @param envp     An array of strings of the form key=value, which are
     *                 passed as environment to the new program.
     */
    virtual void executeProgram(const char* pathname,
                                char* const argv[],
                                char* const envp[]) const = 0;

    /**
     * @brief Initialize the Random Number Generator for a new sequence of
     *        pseudo-random integers to be returned by rand()
     */
    virtual void reseedPRNG() const = 0;

    /**
     * @brief Close all opened file descriptors except those related to the
     *        standard streams (stdin, stdout, stderr). These are reopened
     *        to /dev/null if not already opened.
     */
    virtual void sanitizeFiles() const = 0;

    /**
     * @brief Permanently drop the privileges of the process
     */
    virtual void dropPrivileges() const = 0;
};

}

#endif
