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

#include "gtest/gtest.h"

#include "mocks/MockLogger.h"
#include "mocks/MockOsal.h"

#include "utils/command/executor/Executor.h"

using ::testing::AtLeast;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::Sequence;

using namespace service::plugins::logger;
using namespace utils::command;
using namespace utils::command::osal;

namespace {

class ExecutorTestFixture : public ::testing::Test {

protected:
    ExecutorTestFixture()
    {
        // Logger methods are not always called
        EXPECT_CALL(m_mockLogger, debug).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, info).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, warn).Times(AtLeast(0));
        EXPECT_CALL(m_mockLogger, error).Times(AtLeast(0));

        // Each test will configure the number of expected
        // calls for these methods
        EXPECT_CALL(m_mockOsal, createProcess).Times(0);
        EXPECT_CALL(m_mockOsal, waitChildProcess).Times(0);
        EXPECT_CALL(m_mockOsal, executeProgram).Times(0);
        EXPECT_CALL(m_mockOsal, reseedPRNG).Times(0);
        EXPECT_CALL(m_mockOsal, sanitizeFiles).Times(0);
        EXPECT_CALL(m_mockOsal, dropPrivileges).Times(0);
    }

    MockOsal m_mockOsal;
    MockLogger m_mockLogger;
};

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(ExecutorTestFixture, waitCommandInFlags)
{
    Executor::Flags flags                = Executor::Flags::WAIT_COMMAND;
    const Executor::ProgramParams params = {nullptr, nullptr, nullptr};

    /* Instantiate an executor */
    Executor executor(m_mockLogger, m_mockOsal, flags);

    /* In parent process
     * - createProcess() must return ProcessId::PARENT
     * - waitChildProcess() must be called
     * - None of other functions must be called */
    {
        InSequence seq;

        EXPECT_CALL(m_mockOsal, createProcess)
            .WillOnce(Return(IOsal::ProcessId::PARENT));
        EXPECT_CALL(m_mockOsal, waitChildProcess).Times(1);
    }

    executor.executeProgram(params);

    /* In child process
     * - createProcess() must return ProcessId::CHILD
     * - executeProgram() must be called to replace the child process
     *   with given program
     * - None of other functions must be called */
    {
        InSequence seq;

        EXPECT_CALL(m_mockOsal, createProcess)
            .WillOnce(Return(IOsal::ProcessId::CHILD));
        EXPECT_CALL(m_mockOsal, executeProgram).Times(1);
    }

    executor.executeProgram(params);
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(ExecutorTestFixture, reseedPrngInFlags)
{
    Executor::Flags flags                = Executor::Flags::RESEED_PRNG;
    const Executor::ProgramParams params = {nullptr, nullptr, nullptr};

    /* Instantiate an executor */
    Executor executor(m_mockLogger, m_mockOsal, flags);

    /* In parent process
     * - createProcess() must return ProcessId::PARENT
     * - reseedPRNG() must be called
     * - None of other functions must be called */
    {
        InSequence seq;

        EXPECT_CALL(m_mockOsal, createProcess)
            .WillOnce(Return(IOsal::ProcessId::PARENT));
        EXPECT_CALL(m_mockOsal, reseedPRNG).Times(1);
    }

    executor.executeProgram(params);

    /* In child process
     * - createProcess() must return ProcessId::CHILD
     * - reseedPRNG() must also be called
     * - executeProgram() must be called to replace the child process
     *   with given program
     * - None of other functions must be called */
    {
        InSequence seq;

        EXPECT_CALL(m_mockOsal, createProcess)
            .WillOnce(Return(IOsal::ProcessId::CHILD));
        EXPECT_CALL(m_mockOsal, reseedPRNG).Times(1);
        EXPECT_CALL(m_mockOsal, executeProgram).Times(1);
    }

    executor.executeProgram(params);
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(ExecutorTestFixture, sanitizeFilesInFlags)
{
    Executor::Flags flags                = Executor::Flags::SANITIZE_FILES;
    const Executor::ProgramParams params = {nullptr, nullptr, nullptr};

    /* Instantiate an executor */
    Executor executor(m_mockLogger, m_mockOsal, flags);

    /* In parent process
     * - createProcess() must return ProcessId::PARENT
     * - None of other functions must be called */
    EXPECT_CALL(m_mockOsal, createProcess)
        .WillOnce(Return(IOsal::ProcessId::PARENT));

    executor.executeProgram(params);

    /* In child process
     * - createProcess() must return ProcessId::CHILD
     * - sanitizeFiles() must also be called
     * - executeProgram() must be called to replace the child process
     *   with given program
     * - None of other functions must be called */
    {
        InSequence seq;

        EXPECT_CALL(m_mockOsal, createProcess)
            .WillOnce(Return(IOsal::ProcessId::CHILD));
        EXPECT_CALL(m_mockOsal, sanitizeFiles).Times(1);
        EXPECT_CALL(m_mockOsal, executeProgram).Times(1);
    }

    executor.executeProgram(params);
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(ExecutorTestFixture, dropPrivilegesInFlags)
{
    Executor::Flags flags                = Executor::Flags::DROP_PRIVILEGES;
    const Executor::ProgramParams params = {nullptr, nullptr, nullptr};

    /* Instantiate an executor */
    Executor executor(m_mockLogger, m_mockOsal, flags);

    /* In parent process
     * - createProcess() must return ProcessId::PARENT
     * - None of other functions must be called */
    EXPECT_CALL(m_mockOsal, createProcess)
        .WillOnce(Return(IOsal::ProcessId::PARENT));

    executor.executeProgram(params);

    /* In child process
     * - createProcess() must return ProcessId::CHILD
     * - dropPrivileges() must also be called
     * - executeProgram() must be called to replace the child process
     *   with given program
     * - None of other functions must be called */
    {
        InSequence seq;

        EXPECT_CALL(m_mockOsal, createProcess)
            .WillOnce(Return(IOsal::ProcessId::CHILD));
        EXPECT_CALL(m_mockOsal, dropPrivileges).Times(1);
        EXPECT_CALL(m_mockOsal, executeProgram).Times(1);
    }

    executor.executeProgram(params);
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(ExecutorTestFixture, AllInFlags)
{
    Executor::Flags flags                = Executor::Flags::ALL;
    const Executor::ProgramParams params = {nullptr, nullptr, nullptr};

    /* Instantiate an executor */
    Executor executor(m_mockLogger, m_mockOsal, flags);

    /* In parent process
     * - createProcess() must return ProcessId::PARENT
     * - reseedPRNG() must also be called
     * - waitChildProcess() must be called
     * - None of other functions must be called
     *
     * Note: reseedPRNG() and waitChildProcess() can be called in
     *       any order
     */
    {
        Sequence seq1;
        Sequence seq2;

        EXPECT_CALL(m_mockOsal, createProcess)
            .InSequence(seq1, seq2)
            .WillOnce(Return(IOsal::ProcessId::PARENT));
        EXPECT_CALL(m_mockOsal, reseedPRNG).Times(1).InSequence(seq1);
        EXPECT_CALL(m_mockOsal, waitChildProcess).Times(1).InSequence(seq2);
    }

    executor.executeProgram(params);

    /* In child process
     * - createProcess() must return ProcessId::CHILD
     * - reseedPRNG() must also be called
     * - sanitizeFiles() must also be called
     * - dropPrivileges() must also be called
     * - executeProgram() must be called to replace the child process
     *   with given program
     * - None of other functions must be called
     *
     * Note: reseedPRNG(), sanitizeFiles(), dropPrivileges() can be called in
     *       any order
     */
    {
        Sequence seq1;
        Sequence seq2;
        Sequence seq3;

        EXPECT_CALL(m_mockOsal, createProcess)
            .InSequence(seq1, seq2, seq3)
            .WillOnce(Return(IOsal::ProcessId::CHILD));
        EXPECT_CALL(m_mockOsal, reseedPRNG).Times(1).InSequence(seq1);
        EXPECT_CALL(m_mockOsal, sanitizeFiles).Times(1).InSequence(seq2);
        EXPECT_CALL(m_mockOsal, dropPrivileges).Times(1).InSequence(seq3);
        EXPECT_CALL(m_mockOsal, executeProgram)
            .Times(1)
            .InSequence(seq1, seq2, seq3);
    }

    executor.executeProgram(params);
}

// NOLINTNEXTLINE(cert-err58-cpp, hicpp-special-member-functions)
TEST_F(ExecutorTestFixture, defaultIsWaitCommandFlagSet)
{
    const Executor::ProgramParams params = {nullptr, nullptr, nullptr};

    /* Instantiate an executor */
    Executor executor(m_mockLogger, m_mockOsal);

    /* In parent process
     * - createProcess() must return ProcessId::PARENT
     * - waitChildProcess() must be called
     * - None of other functions must be called */
    {
        InSequence seq;

        EXPECT_CALL(m_mockOsal, createProcess)
            .WillOnce(Return(IOsal::ProcessId::PARENT));
        EXPECT_CALL(m_mockOsal, waitChildProcess).Times(1);
    }

    executor.executeProgram(params);

    /* In child process
     * - createProcess() must return ProcessId::CHILD
     * - executeProgram() must be called to replace the child process
     *   with given program
     * - None of other functions must be called */
    {
        InSequence seq;

        EXPECT_CALL(m_mockOsal, createProcess)
            .WillOnce(Return(IOsal::ProcessId::CHILD));
        EXPECT_CALL(m_mockOsal, executeProgram).Times(1);
    }

    executor.executeProgram(params);
}

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
