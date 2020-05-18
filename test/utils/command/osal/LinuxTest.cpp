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

#include "gtest/gtest.h"

#include "fakes/MockWrapper.h"
#include "mocks/MockLogger.h"

#include "utils/command/executor/osal/Linux.h"

using ::testing::AnyNumber;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::SetErrnoAndReturn;

using namespace service::plugins::logger;
using namespace utils::command;
using namespace utils::command::osal;

MockWrapper* gMockWrapper = nullptr;

namespace {

class LinuxTestFixture : public ::testing::Test {

protected:
    LinuxTestFixture() : m_linux(m_mockLogger)
    {
        // Logger methods are not always called
        EXPECT_CALL(m_mockLogger, debug).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, info).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, warn).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, error).Times(AtLeast(0));
    }

    void SetUp() override
    {
        gMockWrapper = &m_mockWrapper;
    }

    void TearDown() override
    {
        gMockWrapper = nullptr;
    }

    MockLogger m_mockLogger;
    Linux m_linux;

    MockWrapper m_mockWrapper;
};

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(LinuxTestFixture, createProcessShouldThrowAnExceptionIfForkFails)
{
    EXPECT_CALL(m_mockWrapper, osFork).WillOnce(Return(-1));
    try {
        (void)m_linux.createProcess();
        FAIL() << "Should fail because fork() has failed";
    }
    catch (const std::runtime_error& e) {
        // Expected!
    }
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(LinuxTestFixture, createProcessShouldReturnParentIfForkReturnsPositiveValue)
{
    EXPECT_CALL(m_mockWrapper, osFork).WillOnce(Return(1));
    ASSERT_EQ(m_linux.createProcess(), IOsal::ProcessId::PARENT);
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(LinuxTestFixture, createProcessShouldReturnParentIfForkReturnsZero)
{
    EXPECT_CALL(m_mockWrapper, osFork).WillOnce(Return(0));
    ASSERT_EQ(m_linux.createProcess(), IOsal::ProcessId::CHILD);
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(LinuxTestFixture, waitChildShouldBeCalledSeveralTimesIfInterrupted)
{
    int gSavedErrno = errno;
    EXPECT_CALL(m_mockWrapper, osWaitpid)
        .WillOnce(SetErrnoAndReturn(EINTR, -1))
        .WillOnce(SetErrnoAndReturn(gSavedErrno, 0));

    m_linux.waitChildProcess();
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(LinuxTestFixture, shouldExitIfExecuteProgramFails)
{
    // FIXME: executeProgram is not considered tested in code coverage.
    //        Need to study how to make it work when using Death test
    //        (ASSERT_DEATH, EXPECT_EXIT, ...) and exit() call together
    EXPECT_CALL(m_mockWrapper, osExecve).Times(AnyNumber());

    // Fixes:
    //   - warning: avoid using 'goto' for flow control [hicpp-avoid-goto]
    //   - warning: do not call c-style vararg functions [hicpp-vararg]
    // NOLINTNEXTLINE(hicpp-avoid-goto, hicpp-vararg)
    ASSERT_DEATH(m_linux.executeProgram(nullptr, nullptr, nullptr), "");
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(LinuxTestFixture, reseedPRNGShouldWorkWithoutError)
{
    EXPECT_CALL(m_mockWrapper, osClockGettime);
    EXPECT_CALL(m_mockWrapper, osGetpid);
    EXPECT_CALL(m_mockWrapper, osSrand);

    m_linux.reseedPRNG();
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(LinuxTestFixture, sanitizeFilesShouldCloseNonStandardDescriptors)
{
    EXPECT_CALL(m_mockWrapper, osGetdtablesize).WillOnce(Return(4));
    EXPECT_CALL(m_mockWrapper, osClose)
        .WillOnce([](int fd) {
            EXPECT_EQ(fd, 3);
            return 0;
        })
        .WillOnce([](int fd) {
            EXPECT_EQ(fd, 4);
            return 0;
        });

    EXPECT_CALL(m_mockWrapper, osFstat).Times(3).WillRepeatedly(Return(0));

    m_linux.sanitizeFiles();
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(LinuxTestFixture,
       sanitizeFilesShouldNotReopenStandardDescriptorsIfAlreadyOpened)
{
    EXPECT_CALL(m_mockWrapper, osFstat).WillRepeatedly(Return(0));
    EXPECT_CALL(m_mockWrapper, osFreopen).Times(0);

    EXPECT_CALL(m_mockWrapper, osGetdtablesize).WillOnce(Return(2));

    m_linux.sanitizeFiles();
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(LinuxTestFixture, sanitizeFilesShouldReopenStandardDescriptorsOnDevNull)
{
    EXPECT_CALL(m_mockWrapper, osFstat)
        .Times(3)
        .WillRepeatedly(SetErrnoAndReturn(EBADF, -1));

    EXPECT_CALL(m_mockWrapper, osFreopen)
        .Times(3)
        .WillRepeatedly(
            [](const char* path, [[maybe_unused]] const char* mode, FILE* stream) {
                EXPECT_STREQ(path, "/dev/null");
                return stream;
            });

    EXPECT_CALL(m_mockWrapper, osFileno).Times(3).WillRepeatedly([](FILE* stream) {
        if (stream == stdin) {
            return 0;
        }
        if (stream == stdout) {
            return 1;
        }
        if (stream == stderr) {
            return 2;
        }
        return -1;
    });

    EXPECT_CALL(m_mockWrapper, osGetdtablesize).WillOnce(Return(2));

    m_linux.sanitizeFiles();
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(
    LinuxTestFixture,
    sanitizeFilesShouldRaiseAnExceptionIfReopeningStandardDescriptorsOnDevNullFailed)
{
    EXPECT_CALL(m_mockWrapper, osFstat).WillOnce(SetErrnoAndReturn(EBADF, -1));

    EXPECT_CALL(m_mockWrapper, osFreopen)
        .WillOnce([](const char* path,
                     [[maybe_unused]] const char* mode,
                     [[maybe_unused]] FILE* stream) {
            EXPECT_STREQ(path, "/dev/null");
            return nullptr;
        });

    EXPECT_CALL(m_mockWrapper, osGetdtablesize).WillOnce(Return(2));

    try {
        m_linux.sanitizeFiles();
        FAIL() << "Should fail because freopen() has failed";
    }
    catch (const std::runtime_error& e) {
        // Expected!
    }
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(LinuxTestFixture, dropPrivilegesShouldCallSetgroupsIfEffectiveUidIsZero)
{
    EXPECT_CALL(m_mockWrapper, osGetgid).WillOnce(Return(1));
    EXPECT_CALL(m_mockWrapper, osGetegid).WillOnce(Return(1));
    EXPECT_CALL(m_mockWrapper, osGetuid)
        .WillOnce(Return(0)); // Same as euid to avoid other calls
    EXPECT_CALL(m_mockWrapper, osGeteuid).WillOnce(Return(0));

    EXPECT_CALL(m_mockWrapper, osSetgroups).Times(1);

    m_linux.dropPrivileges();
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(LinuxTestFixture, dropPrivilegesShouldRaiseAnExceptionIfSetgroupsFailed)
{
    EXPECT_CALL(m_mockWrapper, osGetgid).WillOnce(Return(1));
    EXPECT_CALL(m_mockWrapper, osGetegid).WillOnce(Return(1));
    EXPECT_CALL(m_mockWrapper, osGetuid)
        .WillOnce(Return(0)); // Same as euid to avoid other calls
    EXPECT_CALL(m_mockWrapper, osGeteuid).WillOnce(Return(0));

    EXPECT_CALL(m_mockWrapper, osSetgroups).WillOnce(Return(-1));

    try {
        m_linux.dropPrivileges();
        FAIL() << "Should fail because setgroups() has failed";
    }
    catch (const std::exception& e) {
        // Excepted!
    }
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(LinuxTestFixture,
       dropPrivilegesShouldCallSetregidIfRealAndEffectiveGidAreDifferent)
{
    EXPECT_CALL(m_mockWrapper, osGetgid).WillOnce(Return(2));
    EXPECT_CALL(m_mockWrapper, osGetegid).WillOnce(Return(1));
    EXPECT_CALL(m_mockWrapper, osGetuid).WillOnce(Return(-1));
    EXPECT_CALL(m_mockWrapper, osGeteuid).WillOnce(Return(-1));

    EXPECT_CALL(m_mockWrapper, osSetregid).WillOnce([](gid_t rgid, gid_t egid) {
        EXPECT_EQ(rgid, 2);
        EXPECT_EQ(rgid, egid);
        return 0;
    });

    m_linux.dropPrivileges();
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(LinuxTestFixture, dropPrivilegesShouldRaiseAnExceptionIfSetregidFailed)
{
    EXPECT_CALL(m_mockWrapper, osGetgid).WillOnce(Return(2));
    EXPECT_CALL(m_mockWrapper, osGetegid).WillOnce(Return(1));
    EXPECT_CALL(m_mockWrapper, osGetuid).WillOnce(Return(-1));
    EXPECT_CALL(m_mockWrapper, osGeteuid).WillOnce(Return(-1));

    EXPECT_CALL(m_mockWrapper, osSetregid).WillOnce([](gid_t rgid, gid_t egid) {
        EXPECT_EQ(rgid, 2);
        EXPECT_EQ(rgid, egid);
        return -1;
    });

    try {
        m_linux.dropPrivileges();
        FAIL() << "Should fail because setregid() has failed";
    }
    catch (const std::exception& e) {
        // Excepted!
    }
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(LinuxTestFixture,
       dropPrivilegesShouldCallSetreuidIfRealAndEffectiveUidAreDifferent)
{
    EXPECT_CALL(m_mockWrapper, osGetgid).WillOnce(Return(-1));
    EXPECT_CALL(m_mockWrapper, osGetegid).WillOnce(Return(-1));
    EXPECT_CALL(m_mockWrapper, osGetuid).WillOnce(Return(2));
    EXPECT_CALL(m_mockWrapper, osGeteuid).WillOnce(Return(1));

    EXPECT_CALL(m_mockWrapper, osSetreuid).WillOnce([](uid_t ruid, uid_t euid) {
        EXPECT_EQ(ruid, 2);
        EXPECT_EQ(ruid, euid);
        return 0;
    });

    m_linux.dropPrivileges();
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(LinuxTestFixture, dropPrivilegesShouldRaiseAnExceptionIfSetreuidFailed)
{
    EXPECT_CALL(m_mockWrapper, osGetgid).WillOnce(Return(-1));
    EXPECT_CALL(m_mockWrapper, osGetegid).WillOnce(Return(-1));
    EXPECT_CALL(m_mockWrapper, osGetuid).WillOnce(Return(2));
    EXPECT_CALL(m_mockWrapper, osGeteuid).WillOnce(Return(1));

    EXPECT_CALL(m_mockWrapper, osSetreuid).WillOnce([](uid_t ruid, uid_t euid) {
        EXPECT_EQ(ruid, 2);
        EXPECT_EQ(ruid, euid);
        return -1;
    });

    try {
        m_linux.dropPrivileges();
        FAIL() << "Should fail because setreuid() has failed";
    }
    catch (const std::exception& e) {
        // Excepted!
    }
}

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
