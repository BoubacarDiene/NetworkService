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

#include <dlfcn.h>

#include "MockOS.h"

#define RETURN_IF_NOT_IN_TESTCASE(retval)                                    \
    if (gMockOS == nullptr) {                                                \
        ADD_FAILURE() << __func__                                            \
                      << " was not expected to be called outside test case"; \
        errno = EINVAL;                                                      \
        return retval;                                                       \
    }

extern utils::command::osal::MockOS* gMockOS;

extern "C" {

pid_t fork()
{
    RETURN_IF_NOT_IN_TESTCASE(-1);
    return gMockOS->fork();
}

int execve(const char* path, char* const argv[], char* const envp[])
{
    RETURN_IF_NOT_IN_TESTCASE(-1);
    return gMockOS->execve(path, argv, envp);
}

pid_t getpid()
{
    if (gMockOS != nullptr) {
        return gMockOS->getpid();
    }

    using RealGetpid_t     = int (*)();
    static auto realGetpid = (RealGetpid_t)dlsym(RTLD_NEXT, "getpid");
    if (realGetpid == nullptr) {
        ADD_FAILURE() << __func__ << " symbol not found";
        errno = ELIBACC;
        return -1;
    }

    return realGetpid();
}

int getdtablesize()
{
    RETURN_IF_NOT_IN_TESTCASE(-1);
    return gMockOS->getdtablesize();
}

int close(int fd)
{
    RETURN_IF_NOT_IN_TESTCASE(-1);
    return gMockOS->close(fd);
}

gid_t getgid()
{
    RETURN_IF_NOT_IN_TESTCASE((gid_t)-1);
    return gMockOS->getgid();
}

gid_t getegid()
{
    RETURN_IF_NOT_IN_TESTCASE((gid_t)-1);
    return gMockOS->getegid();
}

uid_t getuid()
{
    RETURN_IF_NOT_IN_TESTCASE((uid_t)-1);
    return gMockOS->getuid();
}

uid_t geteuid()
{
    RETURN_IF_NOT_IN_TESTCASE((uid_t)-1);
    return gMockOS->geteuid();
}

int setreuid(uid_t ruid, uid_t euid)
{
    RETURN_IF_NOT_IN_TESTCASE(-1);
    return gMockOS->setreuid(ruid, euid);
}

int setregid(gid_t rgid, gid_t egid)
{
    RETURN_IF_NOT_IN_TESTCASE(-1);
    return gMockOS->setregid(rgid, egid);
}

FILE* freopen(const char* __restrict filename, const char* modes, FILE* stream)
{
    RETURN_IF_NOT_IN_TESTCASE(nullptr);
    return gMockOS->freopen(filename, modes, stream);
}

int fileno(FILE* stream)
{
    if (gMockOS != nullptr) {
        return gMockOS->fileno(stream);
    }

    using RealFileno_t     = int (*)(FILE*);
    static auto realFileno = (RealFileno_t)dlsym(RTLD_NEXT, "fileno");
    if (realFileno == nullptr) {
        ADD_FAILURE() << __func__ << " symbol not found";
        errno = ELIBACC;
        return -1;
    }

    return realFileno(stream);
}

pid_t waitpid(pid_t pid, int* stat_loc, int options)
{
    RETURN_IF_NOT_IN_TESTCASE(-1);
    return gMockOS->waitpid(pid, stat_loc, options);
}

int clock_gettime(clockid_t clock_id, struct timespec* tp)
{
    RETURN_IF_NOT_IN_TESTCASE(-1);
    return gMockOS->clock_gettime(clock_id, tp);
}

void srand(unsigned int seed)
{
    RETURN_IF_NOT_IN_TESTCASE();
    gMockOS->srand(seed);
}

int fstat(int fd, struct stat* buf)
{
    RETURN_IF_NOT_IN_TESTCASE(-1);
    return gMockOS->fstat(fd, buf);
}

int setgroups(size_t n, const gid_t* groups)
{
    RETURN_IF_NOT_IN_TESTCASE(-1);
    return gMockOS->setgroups(n, groups);
}
}
