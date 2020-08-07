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

#ifndef __TEST_UTILS_COMMAND_OSAL_FAKES_MOCK_OS_H__
#define __TEST_UTILS_COMMAND_OSAL_FAKES_MOCK_OS_H__

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <grp.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "gmock/gmock.h"

namespace utils::command::osal {

class MockOS {

public:
    /** Class constructor */
    MockOS();

    /** Class destructor */
    ~MockOS();

    /** Copy constructor */
    MockOS(const MockOS&) = delete;

    /** Class copy-assignment operator */
    MockOS& operator=(const MockOS&) = delete;

    /** Class move constructor */
    MockOS(MockOS&&) = delete;

    /** Class move-assignment operator */
    MockOS& operator=(MockOS&&) = delete;

    /** Mocks */
    MOCK_METHOD(pid_t, fork, (), ());
    MOCK_METHOD(int,
                execve,
                (const char* pathname, char* const argv[], char* const envp[]),
                ());
    MOCK_METHOD(pid_t, getpid, (), ());
    MOCK_METHOD(int, getdtablesize, (), ());
    MOCK_METHOD(int, close, (int fd), ());
    MOCK_METHOD(gid_t, getgid, (), ());
    MOCK_METHOD(gid_t, getegid, (), ());
    MOCK_METHOD(uid_t, getuid, (), ());
    MOCK_METHOD(uid_t, geteuid, (), ());
    MOCK_METHOD(int, setreuid, (uid_t ruid, uid_t euid), ());
    MOCK_METHOD(int, setregid, (gid_t rgid, gid_t egid), ());
    MOCK_METHOD(FILE*,
                freopen,
                (const char* path, const char* mode, FILE* stream),
                ());
    MOCK_METHOD(int, fileno, (FILE * stream), ());
    MOCK_METHOD(pid_t, waitpid, (pid_t pid, int* status, int options), ());
    MOCK_METHOD(int, clock_gettime, (clockid_t clk_id, struct timespec* tp), ());
    MOCK_METHOD(void, srand, (unsigned int seed), ());
    MOCK_METHOD(int, fstat, (int fd, struct stat* buf), ());
    MOCK_METHOD(int, setgroups, (size_t size, const gid_t* list), ());
};

}

#endif
