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

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <grp.h>
#include <stdexcept>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utils/helper/Errno.h"

#include "Executor.h"

using namespace service::plugins::logger;
using namespace utils::command;
using namespace utils::helper;

struct Executor::Internal {
    const ILogger& logger;

    explicit Internal(const ILogger& providedLogger) : logger(providedLogger) {}

    /* Initialize the Random Number Generator for a new sequence of
     * pseudo-random integers to be returned by rand() */
    static void reseedPRNG()
    {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);

        auto intermediateResult = static_cast<unsigned>(ts.tv_sec ^ ts.tv_nsec
                                                        ^ (ts.tv_nsec >> 31u));
        unsigned seed
            = intermediateResult ^ ((static_cast<unsigned>(getpid())) << 16u);

        srand(seed);
    }

    /* Close all opened file descriptors except those related to the standard
     * streams (stdin, stdout, stderr) which are only reopened to /dev/null if
     * not already opened. */
    static void sanitizeFiles()
    {
        /* Close all opened descriptors other than the standard ones
         *
         * Note: getdtablesize() is implemented as a libc library function. The
         * glibc version calls getrlimit(2) and returns the current
         * RLIMIT_NOFILE limit, or OPEN_MAX when that fails */
        int fds = getdtablesize();
        for (int fd = 3; fd <= fds; ++fd) {
            close(fd);
        }

        /* Make sure the standard descriptors are opened */
        struct stat buffer;
        for (int fd = 0; fd < 3; ++fd) {
            if ((fstat(fd, &buffer) != -1) || (errno != EBADF)) {
                break;
            }

            /* Redirect the standard descriptor to /dev/null */
            if (!redirectStandardStream(fd, "/dev/null")) {
                throw std::runtime_error(
                    "Failed to reopen standard descriptor: "
                    + std::to_string(fd));
            }
        }
    }

    /* Permanently drop the privileges of the process */
    static void dropPrivileges()
    {
        /* - realGid : The group id of the user that has launched this program
         * - effectiveGid: The group id used by the kernel to determines
         * privileges granted to the process
         * - realUid : The user id of the user that has launched this program
         * - effectiveGid: The user id used by the kernel to determines
         * privileges granted to the process
         *
         * Note: The real uid can differ from the effective one when for example
         *       root changes the owner of the program to itself and set
         * "Set-UID" bit (chmod u+s). Thus, the effective uid with be equal to
         * 0. */
        gid_t realGid      = getgid();
        gid_t effectiveGid = getegid();
        uid_t realUid      = getuid();
        uid_t effectiveUid = geteuid();

        /* Limit the groups to 1 i.e to caller's group id */
        if (effectiveUid == 0) {
            if (setgroups(1, &realGid) == -1) {
                throw std::runtime_error(Errno::toString("setgroups()", errno));
            }
        }

        /* Replace the effective gid with the real one if they are not the same
         * and make changes permanent (the real gid also set) */
        if ((realGid != effectiveGid) && (setregid(realGid, realGid) == -1)) {
            throw std::runtime_error(Errno::toString("setregid()", errno));
        }

        /* Replace the effective uid with the real one if they are not the same
         * and make changes permanent (the real uid also set) */
        if ((realUid != effectiveUid) && (setreuid(realUid, realUid) == -1)) {
            throw std::runtime_error(Errno::toString("setreuid()", errno));
        }
    }

private:
    /* Reopen the standard stream (stdin, stdout or stderr) and redirect it
     * to the the provided destination file */
    static inline bool redirectStandardStream(int fd,
                                              const char* const destPathname)
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

Executor::Executor(const ILogger& logger)
    : m_internal(std::make_unique<Internal>(logger))
{}

Executor::~Executor() = default;

void Executor::exec(const char* const pathname,
                    char* const argv[],
                    char* const envp[],
                    Flags flags) const
{
    pid_t childPid;

    m_internal->logger.debug("Create child process");
    if ((childPid = fork()) == -1) {
        throw std::runtime_error(Errno::toString("fork()", errno));
    }

    if ((flags & Flags::RESEED_PRNG) != 0) {
        m_internal->logger.debug("Reseed PRNG in both parent and the child");
        Internal::reseedPRNG();
    }

    if (childPid != 0) {
        if ((flags & Flags::WAIT_COMMAND) != 0) {
            pid_t pid;
            int status;

            m_internal->logger.debug("Parent - Wait for child: "
                                     + std::to_string(childPid));
            do {
                pid = waitpid(childPid, &status, 0);
            } while ((pid == -1) && (errno == EINTR));
            m_internal->logger.debug("Parent - waitpid() status: "
                                     + std::to_string(status));
        }
        return;
    }

    if ((flags & Flags::SANITIZE_FILES) != 0) {
        m_internal->logger.debug("Child - Sanitize files");
        Internal::sanitizeFiles();
    }

    if ((flags & Flags::DROP_PRIVILEGES) != 0) {
        m_internal->logger.debug("Child - Drop privileges");
        Internal::dropPrivileges();
    }

    // Note that execve() must not return unless when it fails
    execve(pathname, argv, envp);
    m_internal->logger.error(Errno::toString("execve()", errno));

    std::_Exit(EXIT_FAILURE);
}
