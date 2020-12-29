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

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <grp.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utils/helper/Errno.h"

#include "Linux.h"

using namespace service::plugins::logger;
using namespace utils::command::osal;
using namespace utils::helper;

struct Linux::Internal {
    const ILogger& logger;

    explicit Internal(const ILogger& providedLogger) : logger(providedLogger) {}

    /* Reopen the standard stream (stdin, stdout or stderr) and redirect it
     * to the the provided destination file */
    static inline bool redirectStandardStream(int fd, const char* const destPathname)
    {
        FILE* file = nullptr;

        switch (fd) {
        case 0:
            file = freopen(destPathname, "rb", stdin);
            break;

        case 1:
            file = freopen(destPathname, "rb", stdout);
            break;

        case 2:
            file = freopen(destPathname, "rb", stderr);
            break;

        default:
            break; // Intentionally left empty
        }

        return ((file != nullptr) && (fileno(file) == fd));
    }
};

Linux::Linux(const ILogger& logger) : m_internal(std::make_unique<Internal>(logger))
{}

Linux::~Linux() = default;

IOsal::ProcessId Linux::createProcess() const
{
    pid_t childPid = fork();
    if (childPid == -1) {
        throw std::runtime_error(Errno::toString("fork()", errno));
    }

    return (childPid != 0 ? IOsal::ProcessId::PARENT : IOsal::ProcessId::CHILD);
}

void Linux::waitChildProcess() const
{
    pid_t pid;
    int status;

    do {
        pid = waitpid(0, &status, 0);
    } while ((pid == -1) && (errno == EINTR));

    if ((pid == -1) || (WIFEXITED(status) && (WEXITSTATUS(status) != 0))) {
        throw std::runtime_error("Parent - waitpid() status: "
                                 + std::to_string(status));
    }
}

void Linux::executeProgram(const char* pathname,
                           char* const argv[],
                           char* const envp[]) const
{
    (void)execve(pathname, argv, envp);

    // Note that execve() must not return unless when it fails
    std::_Exit(EXIT_FAILURE);
}

void Linux::reseedPRNG() const
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    /* Following two variables are necessary to fix static analysis issue about
     * magic numbers: [readability-magic-numbers] */
    constexpr unsigned int shift31 = 31u;
    constexpr unsigned int shift16 = 16u;

    auto intermediateResult
        = static_cast<unsigned>(ts.tv_sec ^ ts.tv_nsec ^ (ts.tv_nsec >> shift31));
    unsigned seed
        = intermediateResult ^ ((static_cast<unsigned>(getpid())) << shift16);

    srand(seed);
}

void Linux::sanitizeFiles() const
{
    /* Close all opened descriptors other than the standard ones */
    int fds = static_cast<int>(sysconf(_SC_OPEN_MAX));
    for (int fd = 3; fd <= fds; ++fd) {
        close(fd);
    }

    /* Make sure the standard descriptors are opened */
    struct stat buffer;
    for (int fd = 0; fd < 3; ++fd) {
        if ((fstat(fd, &buffer) != -1) || (errno != EBADF)) {
            m_internal->logger.debug("Nothing to do with standard fd: "
                                     + std::to_string(fd));
        }
        else {
            m_internal->logger.debug("Reopen standard fd: " + std::to_string(fd));
            if (!Internal::redirectStandardStream(fd, "/dev/null")) {
                throw std::runtime_error("Failed to reopen standard descriptor: "
                                         + std::to_string(fd));
            }
        }
    }
}

void Linux::dropPrivileges() const
{
    /* - realGid:      The group id of the user that has launched this program
     * - effectiveGid: The group id used by the kernel to determine privileges
     *                 granted to the process
     * - realUid:      The user id of the user that has launched this program
     * - effectiveUid: The user id used by the kernel to determine privileges
     *                 granted to the process
     *
     * Note: The real uid can differ from the effective one when for example
     *       root changes the owner of the program to itself and set
     * "Set-UID" bit (chmod u+s). Thus, the effective uid with be equal to 0 */
    gid_t realGid      = getgid();
    gid_t effectiveGid = getegid();
    uid_t realUid      = getuid();
    uid_t effectiveUid = geteuid();

    m_internal->logger.debug("Limit the groups to 1 i.e to caller's group id");
    if (effectiveUid == 0) {
        if (setgroups(1, &realGid) == -1) {
            throw std::runtime_error(Errno::toString("setgroups()", errno));
        }
    }

    /* Replace the effective gid with the real one if they are not the same
     * and make changes permanent (the real gid also set) */
    if (realGid != effectiveGid) {
        m_internal->logger.debug(
            "Permanently replace the effective gid with the real one");
        if (setregid(realGid, realGid) == -1) {
            throw std::runtime_error(Errno::toString("setregid()", errno));
        }
    }

    /* Replace the effective uid with the real one if they are not the same
     * and make changes permanent (the real uid also set) */
    if (realUid != effectiveUid) {
        m_internal->logger.debug(
            "Permanently replace the effective uid with the real one");
        if (setreuid(realUid, realUid) == -1) {
            throw std::runtime_error(Errno::toString("setreuid()", errno));
        }
    }
}
