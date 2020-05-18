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

/**
 * @file Wrapper.h
 * @ingroup Helper
 *
 * @brief This is a wrapper to "low level calls" used in Linux.cpp. Putting them
 *        in a separate file makes it a bit more easy to test OSAL.
 *
 * @author Boubacar DIENE <boubacar.diene@gmail.com>
 * @date May 2020
 */

#ifndef __UTILS_COMMAND_EXECUTOR_OSAL_WRAPPER_H__
#define __UTILS_COMMAND_EXECUTOR_OSAL_WRAPPER_H__

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <grp.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @fn pid_t osFork()
 *
 * @brief A wrapper to fork()
 *
 * It creates a new process by duplicating the calling process. The new
 * process is referred to as the child process. The calling process is
 * referred to as the parent process.
 *
 * @return On success, the PID of the child process is returned in the parent,
 *         and 0 is returned in the child. On failure, -1 is returned in the
 *         parent, no child process is created, and errno is set appropriately
 */
pid_t osFork();

/**
 * @fn int osExecve(const char* pathname, char* const argv[], char* const envp[])
 *
 * @brief A wrapper to execve()
 *
 * It executes the program referred to by pathname. This causes the program that
 * is currently being run by the calling process to be replaced with a new program,
 * with newly initialized stack, heap, and (initialized and uninitialized) data
 * segments.
 *
 * @param pathname The program to execute
 * @param argv     An array of pointers to strings passed to the new program as
 *                 its command-line arguments
 * @param envp     An array of pointers to strings, conventionally of the form
 *                 key=value, which are passed as the environment of the new program
 *
 * @return On success, it does not return, on error -1 is returned, and errno is
 *         set appropriately
 */
int osExecve(const char* pathname, char* const argv[], char* const envp[]);

/**
 * @fn pid_t osGetpid()
 *
 * @brief A wrapper to getpid()
 *
 * @return The process ID (PID) of the calling process
 */
pid_t osGetpid();

/**
 * @fn int osGetdtablesize()
 *
 * @brief A wrapper to getdtablesize()
 *
 * It returns the maximum number of files a process can have open, one more than
 * the largest possible value for a file descriptor.
 *
 * @return The current limit on the number of open files per process
 */
int osGetdtablesize();

/**
 * @fn int osClose(int fd)
 *
 * @brief A wrapper to close()
 *
 * It closes a file descriptor, so that it no longer refers to any file and may
 * be reused.
 *
 * @param fd The file descriptor to close
 *
 * @return 0 on success. On error, -1 is returned, and errno is set appropriately
 */
int osClose(int fd);

/**
 * @fn gid_t osGetgid()
 *
 * @brief A wrapper to getgid()
 *
 * @return The real group ID of the calling process
 */
gid_t osGetgid();

/**
 * @fn gid_t osGetegid()
 *
 * @brief A wrapper to getegid()
 *
 * @return The effective group ID of the calling process
 */
gid_t osGetegid();

/**
 * @fn uid_t osGetuid()
 *
 * @brief A wrapper to getuid()
 *
 * @return The real user ID of the calling process
 */
uid_t osGetuid();

/**
 * @fn uid_t osGeteuid()
 *
 * @brief A wrapper to geteuid()
 *
 * @return The effective user ID of the calling process
 */
uid_t osGeteuid();

/**
 * @fn int osSetreuid(uid_t ruid, uid_t euid)
 *
 * @brief A wrapper to setreuid()
 *
 * It sets real and effective user IDs of the calling process
 *
 * @param ruid The real user ID
 * @param euid The effective user ID
 *
 * @return On success, 0 is returned. On error, -1 is returned, and errno is set
 *         appropriately
 */
int osSetreuid(uid_t ruid, uid_t euid);

/**
 * @fn int osSetregid(gid_t rgid, gid_t egid)
 *
 * @brief A wrapper to setregid()
 *
 * It sets real and effective group IDs of the calling process
 *
 * @param rgid The real group ID
 * @param egid The effective group ID
 *
 * @return On success, 0 is returned. On error, -1 is returned, and errno is set
 *         appropriately
 */
int osSetregid(gid_t rgid, gid_t egid);

/**
 * @fn FILE* osFreopen(const char* path, const char* mode, FILE* stream)
 *
 * @brief A wrapper to freopen()
 *
 * It opens the file whose name is the string pointed to by path and associates
 * the stream pointed to by stream with it. The original stream (if it exists)
 * is closed
 *
 * @param path   The path to file to reopen
 * @param mode   The "reopen mode"
 * @param stream The associated stream
 *
 * @return On success, a FILE pointer is returned. Otherwise, NULL is returned
 *         and errno is set to indicate the error
 */
FILE* osFreopen(const char* path, const char* mode, FILE* stream);

/**
 * @fn int osFileno(FILE* stream)
 *
 * @brief A wrapper to fileno()
 *
 * It examines the argument stream and returns its integer descriptor
 *
 * @param stream The stream to examine
 *
 * @return The integer descriptor associated to stream
 */
int osFileno(FILE* stream);

/**
 * @fn pid_t osWaitpid(pid_t pid, int* status, int options)
 *
 * @brief A wrapper to waitpid()
 *
 * It waits for state changes in a child of the calling process, and obtain
 * information about the child whose state has changed. A state change is
 * considered to be: the child terminated; the child was stopped by a signal;
 * or the child was resumed by a signal
 *
 * @param pid     The PID to wait for (see manpage for details)
 * @param status  A pointer to an int value representing the status
 * @param options By default, waitpid() waits only for terminated children. The
 *                options argument allows to change this behavior (see manpage
 *                for details)
 *
 * @return On success, return the process ID of the child whose state has changed
 */
pid_t osWaitpid(pid_t pid, int* status, int options);

/**
 * @fn int osClockGettime(clockid_t clk_id, struct timespec* tp)
 *
 * @brief A wrapper to clock_gettime()
 *
 * It retrieves the time of the specified clock clk_id
 *
 * @param clk_id The identifier of the particular clock on which to act
 * @param tp     The time value
 *
 * @return 0 is returned on success or -1 on failure (in which case errno is set
 *         appropriately)
 */
int osClockGettime(clockid_t clk_id, struct timespec* tp);

/**
 * @fn void osSrand(unsigned int seed)
 *
 * @brief A wrapper to srand()
 *
 * It sets its argument as the seed for a new sequence of pseudo-random integers
 * to be returned by rand()
 *
 * @param seed The new seed value
 */
void osSrand(unsigned int seed);

/**
 * @fn int osFstat(int fd, struct stat* buf)
 *
 * @brief A wrapper to fstat()
 *
 * It returns informations about the file pointed to by the given file descriptor
 *
 * @param fd  The file descriptor to retrieve informations from
 * @param buf The buffer in which store retrieved informations
 *
 * @return On success, 0 is returned. On error, -1 is returned, and errno
 *         is set appropriately
 */
int osFstat(int fd, struct stat* buf);

/**
 * @fn int osSetgroups(size_t size, const gid_t* list)
 *
 * @brief A wrapper to setgroups()
 *
 * It sets the supplementary group IDs for the calling process.
 * Appropriate privileges (Linux: the CAP_SETGID capability) are required
 *
 * @param size The number of supplementary group IDs in the buffer pointed
 *             to by list
 * @param list The supplementary group IDs
 *
 * @return 0 on success. On error, -1 is returned, and errno is set appropriately
 */
int osSetgroups(size_t size, const gid_t* list);

#endif
