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

#ifndef __UTILS_COMMAND_EXECUTOR_LINUX_OSAL_H__
#define __UTILS_COMMAND_EXECUTOR_LINUX_OSAL_H__

#include <memory>

#include "service/plugins/ILogger.h"
#include "utils/command/executor/IOsal.h"

namespace utils::command::osal {

/**
 * @class Linux Linux.h "utils/command/executor/osal/Linux.h"
 * @ingroup Helper
 *
 * @brief This class is the "low level class" that implements @ref IOsal.h
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
class Linux : public IOsal {

public:
    /**
     * Class constructor
     *
     * @param logger Logger object to print some useful logs
     */
    explicit Linux(const service::plugins::logger::ILogger& logger);

    /** Class destructor */
    ~Linux() override;

    /** Class copy constructor */
    Linux(const Linux&) = delete;

    /** Class copy-assignment operator */
    Linux& operator=(const Linux&) = delete;

    /** Class move constructor */
    Linux(Linux&&) = delete;

    /** Class move-assignment operator */
    Linux& operator=(Linux&&) = delete;

    /**
     * @brief creates a new process by duplicating the calling process. It
     *        can basically be a wrapper to fork() call.
     *
     * @return An id of type @ref ProcessId
     */
    [[nodiscard]] ProcessId createProcess() const override;

    /**
     * @brief Wait for any child process whose process group ID is equal to
     *        that of the calling process.
     */
    void waitChildProcess() const override;

    /**
     * @brief Execute the program referred to by pathname
     *
     * @param pathname Either a binary executable, or a script starting with a
     *                 line of the form: "#! interpreter [optional-arg]"
     * @param argv     An array of argument strings passed to the new program.
     *                 By convention, the first of these strings should contain
     *                 the filename associated with the file being executed.
     * @param envp     An array of strings of the form key=value, which are
     *                 passed as environment to the new program.
     */
    void executeProgram(const char* pathname,
                        char* const argv[],
                        char* const envp[]) const override;

    /**
     * @brief Initialize the Random Number Generator for a new sequence of
     *        pseudo-random integers to be returned by rand()
     */
    void reseedPRNG() const override;

    /**
     * @brief Close all opened file descriptors except those related to the
     *        standard streams (stdin, stdout, stderr). These are only reopened
     *        to /dev/null if not already opened.
     */
    void sanitizeFiles() const override;

    /**
     * @brief Permanently drop the privileges of the process
     */
    void dropPrivileges() const override;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
