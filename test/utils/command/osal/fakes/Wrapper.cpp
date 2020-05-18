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

#include "MockWrapper.h"

extern utils::command::osal::MockWrapper* gMockWrapper;

pid_t osFork()
{
    return gMockWrapper->osFork();
}

int osExecve(const char* pathname, char* const argv[], char* const envp[])
{
    return gMockWrapper->osExecve(pathname, argv, envp);
}

pid_t osGetpid()
{
    return gMockWrapper->osGetpid();
}

int osGetdtablesize()
{
    return gMockWrapper->osGetdtablesize();
}

int osClose(int fd)
{
    return gMockWrapper->osClose(fd);
}

gid_t osGetgid()
{
    return gMockWrapper->osGetgid();
}

gid_t osGetegid()
{
    return gMockWrapper->osGetegid();
}

uid_t osGetuid()
{
    return gMockWrapper->osGetuid();
}

uid_t osGeteuid()
{
    return gMockWrapper->osGeteuid();
}

int osSetreuid(uid_t ruid, uid_t euid)
{
    return gMockWrapper->osSetreuid(ruid, euid);
}

int osSetregid(gid_t rgid, gid_t egid)
{
    return gMockWrapper->osSetregid(rgid, egid);
}

FILE* osFreopen(const char* path, const char* mode, FILE* stream)
{
    return gMockWrapper->osFreopen(path, mode, stream);
}

int osFileno(FILE* stream)
{
    return gMockWrapper->osFileno(stream);
}

pid_t osWaitpid(pid_t pid, int* status, int options)
{
    return gMockWrapper->osWaitpid(pid, status, options);
}

int osClockGettime(clockid_t clk_id, struct timespec* tp)
{
    return gMockWrapper->osClockGettime(clk_id, tp);
}

void osSrand(unsigned int seed)
{
    gMockWrapper->osSrand(seed);
}

int osFstat(int fd, struct stat* buf)
{
    return gMockWrapper->osFstat(fd, buf);
}

int osSetgroups(size_t size, const gid_t* list)
{
    return gMockWrapper->osSetgroups(size, list);
}
