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

#ifndef __TEST_UTILS_COMMAND_OSAL_FAKES_MOCK_WRAPPER_H__
#define __TEST_UTILS_COMMAND_OSAL_FAKES_MOCK_WRAPPER_H__

#include "gmock/gmock.h"

#include "utils/command/executor/osal/Wrapper.h"

namespace utils::command::osal {

class MockWrapper {

public:
    /** Class constructor */
    MockWrapper();

    /** Class destructor */
    ~MockWrapper();

    /** Copy constructor */
    MockWrapper(const MockWrapper&) = delete;

    /** Class copy-assignment operator */
    MockWrapper& operator=(const MockWrapper&) = delete;

    /** Class move constructor */
    MockWrapper(MockWrapper&&) = delete;

    /** Class move-assignment operator */
    MockWrapper& operator=(MockWrapper&&) = delete;

    /** Mocks */
    MOCK_METHOD(pid_t, osFork, (), ());
    MOCK_METHOD(int,
                osExecve,
                (const char* pathname, char* const argv[], char* const envp[]),
                ());
    MOCK_METHOD(pid_t, osGetpid, (), ());
    MOCK_METHOD(int, osGetdtablesize, (), ());
    MOCK_METHOD(int, osClose, (int fd), ());
    MOCK_METHOD(gid_t, osGetgid, (), ());
    MOCK_METHOD(gid_t, osGetegid, (), ());
    MOCK_METHOD(uid_t, osGetuid, (), ());
    MOCK_METHOD(uid_t, osGeteuid, (), ());
    MOCK_METHOD(int, osSetreuid, (uid_t ruid, uid_t euid), ());
    MOCK_METHOD(int, osSetregid, (gid_t rgid, gid_t egid), ());
    MOCK_METHOD(FILE*,
                osFreopen,
                (const char* path, const char* mode, FILE* stream),
                ());
    MOCK_METHOD(int, osFileno, (FILE * stream), ());
    MOCK_METHOD(pid_t, osWaitpid, (pid_t pid, int* status, int options), ());
    MOCK_METHOD(int, osClockGettime, (clockid_t clk_id, struct timespec* tp), ());
    MOCK_METHOD(void, osSrand, (unsigned int seed), ());
    MOCK_METHOD(int, osFstat, (int fd, struct stat* buf), ());
    MOCK_METHOD(int, osSetgroups, (size_t size, const gid_t* list), ());
};

}

#endif
