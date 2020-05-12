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

#include "Executor.h"

using namespace service::plugins::logger;
using namespace utils::command;

struct Executor::Internal {
    const ILogger& logger;
    const IOsal& osal;

    explicit Internal(const ILogger& providedLogger, const IOsal& providedOsal)
        : logger(providedLogger),
          osal(providedOsal)
    {}
};

Executor::Executor(const ILogger& logger, const IOsal& osal)
    : m_internal(std::make_unique<Internal>(logger, osal))
{}

Executor::~Executor() = default;

void Executor::executeProgram(const ProgramParams& params, Flags flags) const
{
    m_internal->logger.debug("Create child process");
    IOsal::ProcessId pid = m_internal->osal.createProcess();

    if ((flags & Flags::RESEED_PRNG) != 0) {
        m_internal->logger.debug("Reseed PRNG in both parent and the child");
        m_internal->osal.reseedPRNG();
    }

    if (pid == IOsal::ProcessId::PARENT) {
        if ((flags & Flags::WAIT_COMMAND) != 0) {
            m_internal->osal.waitChildProcess();
        }
        return;
    }

    if ((flags & Flags::SANITIZE_FILES) != 0) {
        m_internal->logger.debug("Child - Sanitize files");
        m_internal->osal.sanitizeFiles();
    }

    if ((flags & Flags::DROP_PRIVILEGES) != 0) {
        m_internal->logger.debug("Child - Drop privileges");
        m_internal->osal.dropPrivileges();
    }

    m_internal->osal.executeProgram(params.pathname, params.argv, params.envp);
}
