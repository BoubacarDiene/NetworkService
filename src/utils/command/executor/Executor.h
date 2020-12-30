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

#include "IExecutor.h"
#include "IOsal.h"

namespace utils::command {

/**
 * @class Executor Executor.h "utils/command/executor/Executor.h"
 * @ingroup Helper
 *
 * @brief A helper class to execute shell commands securely.
 *
 * This class is the "low level class" that implements @ref IExecutor.h
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
class Executor : public IExecutor {

public:
    /**
     * Class constructor
     *
     * @param logger Logger object to print some useful logs
     * @param osal   OS abstract layer's implementation to use. This is passed
     *               to the constructor to ease unit testing of Executor class.
     * @param flags  A set of masks of type @ref IExecutor::Flags
     */
    explicit Executor(const service::plugins::logger::ILogger& logger,
                      const osal::IOsal& osal,
                      Flags flags = Flags::WAIT_COMMAND);

    /** Class destructor */
    ~Executor() override;

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
     * the random number generator, close file descriptors, ...) depending
     * on @ref Flags. All input parameters have the same meaning as in
     * execve() manpage.
     *
     * @param params An object of type @ref IExecutor::ProgramParams
     *
     * @see http://man7.org/linux/man-pages/man2/execve.2.html
     */
    void executeProgram(const ProgramParams& params) const override;

private:
    struct Internal;
    std::unique_ptr<Internal> m_internal;
};

}

#endif
