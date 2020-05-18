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

#include "Wrapper.h"

pid_t osFork()
{
    return fork();
}

int osExecve(const char* pathname, char* const argv[], char* const envp[])
{
    return execve(pathname, argv, envp);
}

pid_t osGetpid()
{
    return getpid();
}

int osGetdtablesize()
{
    return getdtablesize();
}

int osClose(int fd)
{
    return close(fd);
}

gid_t osGetgid()
{
    return getgid();
}

gid_t osGetegid()
{
    return getegid();
}

uid_t osGetuid()
{
    return getuid();
}

uid_t osGeteuid()
{
    return geteuid();
}

int osSetreuid(uid_t ruid, uid_t euid)
{
    return setreuid(ruid, euid);
}

int osSetregid(gid_t rgid, gid_t egid)
{
    return setregid(rgid, egid);
}

FILE* osFreopen(const char* path, const char* mode, FILE* stream)
{
    return freopen(path, mode, stream);
}

int osFileno(FILE* stream)
{
    return fileno(stream);
}

pid_t osWaitpid(pid_t pid, int* status, int options)
{
    return waitpid(pid, status, options);
}

int osClockGettime(clockid_t clk_id, struct timespec* tp)
{
    return clock_gettime(clk_id, tp);
}

void osSrand(unsigned int seed)
{
    srand(seed);
}

int osFstat(int fd, struct stat* buf)
{
    return fstat(fd, buf);
}

int osSetgroups(size_t size, const gid_t* list)
{
    return setgroups(size, list);
}
